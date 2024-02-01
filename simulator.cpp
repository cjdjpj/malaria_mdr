#include "file_writer.h"
#include "utils.h"
#include "settings.h"
#include "host.h"
#include "simulator.h"

#include <iostream>

int main(){

	//Initialize hosts and set generations
	int generation = GENERATIONS;
	Host* host_population = new Host[NUM_HOSTS];

	//set initial conditions (could use yaml or smth)	
	poisson_mean = STARTING_POISSON_MEAN;
	Host::g_clones.insert(5);
	Host::g_clones.insert(35);
	Host::g_clones.insert(21);
	Host::g_clones.insert(19);
	Host::g_clones.insert(2);
	Host::g_freqs[5] = 1.0/5;
	Host::g_freqs[35] = 1.0/5;
	Host::g_freqs[21] = 1.0/5;
	Host::g_freqs[19] = 1.0/5;
	Host::g_freqs[2] = 1.0/5;


	//begin sim
	while(generation--){
		
		//*****for hosts: select moi (poisson dist), choose clones (multinomial), set clone freq (uniform)*****
		poisson_generator.reset();
		poisson_generator.param(std::poisson_distribution<>::param_type(poisson_mean));
		num_infected = 0;
		for(int i=0; i<NUM_HOSTS; i++){
			host_population[i].reset();
			host_population[i].moi = poisson_generator(rng);
			if(host_population[i].moi){
				num_infected++;
			}

			//generate indices_for_diceroll (reformat necessary as Host::g_freqs don't go 0->1->2->...)
			int indices_for_diceroll[Host::g_clones.size()];
			int k=0;
			for (const auto& c: Host::g_clones) {
			    indices_for_diceroll[k] = c;
			    k++;
			}

			host_population[i].select_clones(Host::g_freqs, Host::g_clones.size(), indices_for_diceroll);
			host_population[i].recombine();
		}


		//*****census*****
		//clear g_clones and g_freqs
		std::fill(Host::g_freqs, Host::g_freqs+NUM_UNIQUE_CLONES, 0.0);
		Host::g_clones.clear();

		//find average clone freqs
		for(int i=0; i<NUM_HOSTS; i++){
			for (const auto& c: host_population[i].i_clones) {
				Host::g_clones.insert(c);
			    Host::g_freqs[c] += host_population[i].i_freqs[c];
			}
		}
		for(const auto& c: Host::g_clones){
			Host::g_freqs[c] = Host::g_freqs[c]/num_infected;
		}

		//*****mutation***** 
		for(auto it = Host::g_clones.begin(); it != Host::g_clones.end(); ++it){
			uint8_t c = *it;
			int num_mutants = (NUM_LOCI-std::popcount(c));
			for(int i=0; i<NUM_LOCI; i++){
				int current_bit = (uint8_t)pow(2, i);
				if(!(current_bit&c)){
					Host::g_freqs[(c+current_bit)] += Host::g_freqs[c] * LAMBDA;
					Host::g_clones.insert((c+current_bit));
				}
			}
			Host::g_freqs[c] = Host::g_freqs[c] -  (Host::g_freqs[c] * LAMBDA * num_mutants);
		}

		//find new poisson mean
		poisson_mean = R_NAUGHT * ((long double)num_infected/NUM_HOSTS) * (1-((long double)num_infected/NUM_HOSTS));
		
		//********************debugging********************//

		// //print global allele freqs
		// std::cout << "\nGEN " << GENERATIONS - generation<< "\n";
		// std::cout << "-------GLOBAL_ALLELE_FREQUENCIES-------\n";
		// for(const auto& c: Host::g_clones){
		// 	if(are_same(Host::g_freqs[c],0) || Host::g_freqs[c] != Host::g_freqs[c]){
		// 		continue;
		// 	}
		// 	std::cout << "clone_" << (int)c << ": " << Host::g_freqs[c] << "\n";
		// }
		std::cout << Host::g_clones.size() << " total clones\n\n";

		// // print host summaries
		// std::cout << "\n-------HOST_SUMMARIES-------\n\n";
		// std::cout << "MOI\n";
		// for(int i=0; i<NUM_HOSTS; i++){
		// 	host_population[i].print_summary();
		// }

		// // print mean moi
		// std::cout << "\npoisson_mean: " << poisson_mean << "\n";
		// std::cout << "num_infected: " << num_infected << "\n";

	}
	delete[] host_population;
}