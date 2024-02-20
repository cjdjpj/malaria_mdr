#include "settings.h"
#include "utils.h"
#include "host.h"

#include <iostream>

Host::Host(){
	moi = 0;
	host_drug = AS;
	mean_fitness = 1.0; 
	std::unordered_set<uint8_t> i_clones = {};
	long double i_freqs[NUM_UNIQUE_CLONES] = {};
}

void Host::choose_clones(long double global_frequencies[], int total_clones, int indices_for_diceroll[]){
	for(int i=0; i<moi; i++){
		//select clones
		int clone_injected = indices_for_diceroll[weighted_dice_roll_with_indices(global_frequencies, total_clones, indices_for_diceroll)];

		//add to i_clones
		i_clones.insert(clone_injected);

		//add associated frequencies
		i_freqs[clone_injected] += (long double)1/moi;
	}
}

void Host::choose_drugs(int generation, int clone_id , long double generational_mean_fitness[NUM_GENERATIONS]){

	#ifdef DTS_SINGLE
	host_drug = AS;
	#endif

	#ifdef DTS_MFT
	if(clone_id < NUM_UNIQUE_CLONES/3){
		host_drug = LM;
	}
	else if(clone_id >= NUM_UNIQUE_CLONES/3 && clone_id < 2*NUM_UNIQUE_CLONES/3){
		host_drug = AQ;
	}
	else{
		host_drug = CQ;
	}
	#endif

	#ifdef DTS_CYCLING
	if(generational_mean_fitness[generation] > CYCLING_MEAN_FITNESS){
		int n = (int)host_drug;
		n++;
		host_drug = (drug)n;
		if(host_drug == ASAQ){ 
			host_drug = AS;
		}
	}
	#endif
}


void Host::naturally_select(long double fitness_data[NUM_UNIQUE_CLONES][NUM_DRUGS]){
	if(!moi){
		return;
	}
	mean_fitness = 0.0;
	for(const auto& c: i_clones){
		mean_fitness += fitness_data[c][host_drug] * i_freqs[c];
	}
	for(const auto& c: i_clones){
		i_freqs[c] = (fitness_data[c][host_drug] * i_freqs[c])/mean_fitness;
	}
}


void Host::recombine(){
	//determine recombinants
	std::unordered_set<uint8_t> recombinants;
	for(auto it1 = i_clones.begin(); it1 != i_clones.end(); ++it1) {
	    auto it2 = it1;
	    ++it2;  
	    for (; it2 != i_clones.end(); ++it2) {
	    	find_bit_combinations(*it1, *it2, recombinants);
	    }
	}

	//determine freq of each allele
    long double allele_freq0[NUM_LOCI] = {};
    long double allele_freq1[NUM_LOCI] = {};

    for(int i=0; i<NUM_LOCI; i++){
        long double sum = 0.0;
        uint8_t mask = 1 << i;
        for(uint8_t e : i_clones){
            if((e&mask)){
                sum += i_freqs[e];
            }
        }
        allele_freq1[i] = sum;
        allele_freq0[i] = 1-sum;
    }

    //determine new recombinant frequencies 
    for(const auto& recombinant : recombinants){
    	i_clones.insert(recombinant);
    	long double product = 1.0;
    	for(int i=0; i<NUM_LOCI; i++){
        	uint8_t mask = 1 << i;
    		if((recombinant&mask)){
    			product *= allele_freq1[i];
    		}
    		else{
    			product *= allele_freq0[i];
    		}
    	}
    	i_freqs[recombinant] += product;
    }
}

void Host::reset(){
	moi = 0;
	mean_fitness = 1.0;
	std::fill(i_freqs, i_freqs + NUM_UNIQUE_CLONES, 0.0);
	i_clones.clear();
}

void Host::validate_i_freq(){
	long double sum = 0.0;
	for(int j=0; j<NUM_UNIQUE_CLONES; j++){
		sum += i_freqs[j];
	}
	if(moi && !are_same(sum, 1.0)){
		std::cout << "invalid, f=" << sum << std::endl;
	}
}

void Host::print_summary(){
	std::cout << (unsigned)moi << "\n";
	std::cout << "mean_fitness: " << mean_fitness << "\n";
	for(const auto& c: i_clones) {
		if(are_same(i_freqs[c], 0)){
			continue;
		}
	    std::cout << "\t" <<"c_" << (int)c << " freq = " << i_freqs[c] << "\n";
	}
}

