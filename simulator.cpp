#include "file_readwrite.h"
#include "utils.h"
#include "settings.h"
#include "host.h"
#include "simulator.h"

#include <iostream>

int main(){

	//initialize hosts
	Host* host_population = new Host[NUM_HOSTS];

	//read in drug-clone fitness values
	long double clone_drug_fitness[NUM_UNIQUE_CLONES][NUM_DRUGS] = {};
	read_csv_to_2d_array_drug("../data/fitness_values.csv", clone_drug_fitness);

	//global clone data collection
	long double generational_poisson_mean[NUM_GENERATIONS] = {};
	long double generational_g_freqs[NUM_GENERATIONS][NUM_UNIQUE_CLONES] = {};
	long double generational_mean_fitness[NUM_GENERATIONS] = {};
	std::unordered_set<uint8_t> g_clones = {};

	//set initial conditions
	generational_poisson_mean[0] = STARTING_POISSON_MEAN;
	g_clones.insert(0);
	generational_g_freqs[0][0] = 1.0;


	//begin sim
	int gen = 0;
	while(gen<NUM_GENERATIONS-1){

		//*****for hosts: transmission, drug distribution, selection, recombination*****//
		poisson_generator.reset();
		poisson_generator.param(std::poisson_distribution<>::param_type(generational_poisson_mean[gen]));
		num_infected = 0;
		for(int i=0; i<NUM_HOSTS; i++){
			host_population[i].reset();

			host_population[i].moi = poisson_generator(rng);

			if(host_population[i].moi){
				num_infected++;
			}

			host_population[i].choose_clones(generational_g_freqs[gen], NUM_UNIQUE_CLONES);

			host_population[i].choose_drugs(gen, i, generational_mean_fitness);

			host_population[i].naturally_select(clone_drug_fitness);

			host_population[i].recombine();

			host_population[i].validate_i_freq();
		}

		//*****census*****//
		g_clones.clear();
		gen++; //store data into next gen.

		//find average (weighted) clone freqs
		long double total_fitness = 0.0;
		for(int i=0; i<NUM_HOSTS; i++){
			total_fitness += host_population[i].mean_fitness;
		}
		generational_mean_fitness[gen] = total_fitness/NUM_HOSTS;

		for(int i=0; i<NUM_HOSTS; i++){
			for (const auto& c: host_population[i].i_clones) {
				g_clones.insert(c);
			    generational_g_freqs[gen][c] += host_population[i].i_freqs[c] * (host_population[i].mean_fitness / total_fitness);
			}
		}
		long double total_freq = 0.0;
		for(const auto& c : g_clones){
			total_freq += generational_g_freqs[gen][c];
		}
		for(const auto& c : g_clones){
			generational_g_freqs[gen][c] /= total_freq;
		}

		//*****mutation*****//
		for(auto it = g_clones.begin(); it != g_clones.end(); ++it){
			uint8_t c = *it;
			int num_mutants = (NUM_LOCI-std::popcount(c));
			for(int i=0; i<NUM_LOCI; i++){
				int current_bit = 1 << i;
				if(!(current_bit&c)){
					generational_g_freqs[gen][(c+current_bit)] += generational_g_freqs[gen][c] * LAMBDA;
					g_clones.insert((c+current_bit));
				}
			}
			generational_g_freqs[gen][c] -= (generational_g_freqs[gen][c] * LAMBDA * num_mutants);
		}

		//find new poisson mean
		generational_poisson_mean[gen] = R_NAUGHT * generational_mean_fitness[gen] * (1-num_infected/NUM_HOSTS);

		//********************debugging********************//

		std::cout << "\nGEN " << gen << "\n";

		//PRINT GLOBAL ALLELE FREQUENCIES
		#ifdef DEBUG_G_CLONE
		std::cout << "-------GLOBAL CLONE FREQUENCIES-------\n";
		for(const auto& c: g_clones){
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
		for(int i=0; i<NUM_HOSTS; i++){
			host_population[i].print_summary();
		}
		#endif

		//PRINT DRUG
		#ifdef DEBUG_DRUG
			#ifdef DTS_CYCLING
			std::cout << "DRUG IN CIRCULATION: " << (int)host_population[5].host_drug << "\n";
			#endif
		#endif

		//PRINT TRANSMISSION
		#ifdef DEBUG_TRANSMISSION
		std::cout << "\npoisson_mean: " << generational_poisson_mean[gen] << "\n";
		std::cout << "num_infected: " << num_infected << "\n";
		#endif

	}
	//export data
	write_2d_array_to_csv_clonefreq("../data/g_freqs.csv", generational_g_freqs);
	write_array_to_csv("../data/mean_fitness.csv", generational_mean_fitness);
	write_array_to_csv("../data/poisson_mean.csv", generational_poisson_mean);

	//cleanup
	delete[] host_population;
}