#include "file_readwrite.h"
#include "utils.h"
#include "settings.h"
#include "host.h"
#include "simulator.h"

#include <vector>
#include <iostream>

int main(){

	//initialize hosts
	std::vector<Host> host_population(NUM_HOSTS);

	//read in drug-clone fitness values
	double clone_drug_fitness[NUM_UNIQUE_CLONES][NUM_DRUGS]{};
	read_csv_to_2d_array_drug("../data/fitness_values_full.csv", clone_drug_fitness);

	//find avg fitness
	double clone_drug_avg_fitness[NUM_DRUGS]{};
	for(int i=0; i<NUM_DRUGS; i++){
		double sum = 0.0;
		for(int j=0; j<NUM_UNIQUE_CLONES; j++){
			sum += clone_drug_fitness[j][i];
		}
		clone_drug_avg_fitness[i] = sum/NUM_UNIQUE_CLONES;
	}

	//global clone data collection
	double generational_poisson_mean[NUM_GENERATIONS]{};
	double generational_g_freqs[NUM_GENERATIONS][NUM_UNIQUE_CLONES]{};
	double generational_mean_fitness[NUM_GENERATIONS]{};
	std::set<uint8_t> g_clones{};

	//SETTING: initial conditions
	generational_poisson_mean[0] = STARTING_POISSON_MEAN;
	g_clones.insert(0);
	g_clones.insert(2);
	g_clones.insert(6);
	generational_g_freqs[0][0] = 1.0/3;
	generational_g_freqs[0][2] = 1.0/3;
	generational_g_freqs[0][6] = 1.0/3;
	int gen = 0;
	int num_infected = 0;

	//sim start
	while(gen<NUM_GENERATIONS-1){

		//transmission, drug distribution, selection, recombination//
		poisson_generator.reset();
		poisson_generator.param(std::poisson_distribution<>::param_type(generational_poisson_mean[gen]));
		num_infected = 0;
		for(Host& host : host_population){
			host.reset();

			host.moi = poisson_generator(rng);

			if(host.moi){
				num_infected++;
			}

			host.choose_clones(generational_g_freqs[gen]);

			host.choose_drugs(gen, clone_drug_avg_fitness, generational_mean_fitness);

			host.naturally_select(clone_drug_fitness);

			host.recombine();

			// host.validate_i_freq();
		}

		//census//
		g_clones.clear();
		gen++; //store data into next gen.

		double total_fitness = 0.0;
		for(const Host& host : host_population){
			if(!host.moi){
				continue;
			}
			for (const uint8_t& c: host.i_clones) {
				g_clones.insert(c);
			    generational_g_freqs[gen][c] += host.i_freqs[c] * host.mean_fitness;
			}
			total_fitness += host.mean_fitness;
		}
		//normalize g_freqs
		for(const uint8_t& c : g_clones){
			generational_g_freqs[gen][c] /= total_fitness;
		}

		//record mean fitness
		generational_mean_fitness[gen] = total_fitness/NUM_HOSTS;

		//mutation//
		std::set<uint8_t> to_be_mutants{};
		for(const uint8_t& c : g_clones){
			int num_mutants = (NUM_LOCI-std::popcount(c));
			for(int l=0; l<NUM_LOCI; l++){
				int current_bit = 1 << l;
				if(!(current_bit&c)){
					generational_g_freqs[gen][c+current_bit] += generational_g_freqs[gen][c] * MUTATION_RATE;
					to_be_mutants.insert(c+current_bit);
				}
			}
			generational_g_freqs[gen][c] -= (generational_g_freqs[gen][c] * MUTATION_RATE * num_mutants);
		}
		for(const uint8_t& c : to_be_mutants){
			g_clones.insert(c);
		}

		//find new poisson mean
		generational_poisson_mean[gen] = R_NAUGHT * generational_mean_fitness[gen] * (1-(num_infected/NUM_HOSTS));

		#ifdef TERMINATE_WHEN_ENDEMIC_OR_ELIMINATED
		if(generational_poisson_mean[gen] == 0.0 || generational_poisson_mean[gen] > 4.7){ //99% prevalence (3 for 95%)
			break;
		}
		#endif

		//********************debugging********************//
		std::cout << "\nGEN: " << gen << "\n";

		//PRINT GLOBAL ALLELE FREQUENCIES
		#ifdef DEBUG_G_CLONE
		std::cout << "-------GLOBAL CLONE FREQUENCIES-------\n";
		for(const uint8_t& c: g_clones){
			if(are_same(generational_g_freqs[gen][c],0)){
				continue;
			}
			std::cout << "clone_" << (int)c << ": " << generational_g_freqs[gen][c] << "\n";
		}
		std::cout << g_clones.size() << " total clones\n\n";
		#endif

		//PRINT HOSTS
		#ifdef DEBUG_HOST
		std::cout << "\n-------HOST SUMMARIES-------\n\n";
		std::cout << "MOI\n";
		for(const Host& host : host_population){
			if(host.moi){
				host.print_summary();
			}
		}
		#endif

		//PRINT DRUG
		#ifdef DEBUG_DRUG
			#ifdef DTS_CYCLING
			std::string drug_names[] = {"AS", "LM", "AQ", "PPQ", "MQ", "CQ", "AL", "ASAQ", "DHAPPQ", "ASMQ", "NO_DRUG"};
			drug prev_drug;
			if(prev_drug != host_population[0].host_drug || gen == 1){
				std::cout << "DRUG: " << drug_names[(int)host_population[0].host_drug] << "\n";
			}
			prev_drug = host_population[0].host_drug;
			#endif
		#endif

		//PRINT TRANSMISSION
		#ifdef DEBUG_TRANSMISSION
		std::cout << "\npoisson_mean: " << generational_poisson_mean[gen] << "\n";
		std::cout << "prop_infected: " << (double)num_infected/NUM_HOSTS << "\n";
		#endif

	}
	//export data
	write_2d_array_to_csv("../data/g_freqs.csv", gen, generational_g_freqs);
	write_array_to_csv("../data/mean_fitness.csv", gen, generational_mean_fitness);
	write_array_to_csv("../data/poisson_mean.csv", gen, generational_poisson_mean);
}