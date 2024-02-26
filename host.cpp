#include "settings.h"
#include "utils.h"
#include "host.h"

#include <iostream>

Host::Host(){
	moi = NAN;
	mean_fitness = NAN;
	host_drug = NO_DRUG;
	std::unordered_set<uint8_t> i_clones = {};
	long double i_freqs[NUM_UNIQUE_CLONES] = {};
}

void Host::choose_clones(const long double global_frequencies[], int total_clones){
	for(int i=0; i<moi; i++){
		//select clones
		int clone_injected = weighted_dice_roll(global_frequencies, total_clones);

		//add to i_clones
		i_clones.insert(clone_injected);

		//add associated frequencies
		i_freqs[clone_injected] += (long double)1/moi;
	}
}

void Host::choose_drugs(int generation, int clone_id , const long double generational_mean_fitness[NUM_GENERATIONS]){

	#ifdef DTS_SINGLE
	host_drug = LM;
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
	if(generation == 0){
		host_drug = AS;
		return;
	}
	if(generation % 30 == 0){
		// generational_mean_fitness[generation] > CYCLING_MEAN_FITNESS
		int n = (int)host_drug;
		n++;
		host_drug = (drug)n;
		if(host_drug == ASAQ){ 
			host_drug = AS;
		}
	}
	#endif
}


void Host::naturally_select(const long double fitness_data[NUM_UNIQUE_CLONES][NUM_DRUGS]){
	if(!moi){
		mean_fitness = 1.0;
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
	if(!weighted_flip(THETA) || !moi){
		return;
	}
	//determine recombinants
	std::unordered_set<uint8_t> recombinants = {};
	std::vector<uint8_t> vec_i_clones(i_clones.begin(), i_clones.end());
	find_bit_combinations(vec_i_clones, recombinants);

	//determine freq of each allele
    long double allele_freq0[NUM_LOCI] = {};
    long double allele_freq1[NUM_LOCI] = {};

    for(int i=0; i<NUM_LOCI; i++){
        long double sum = 0.0;
        uint8_t mask = 1 << i;
        for(uint8_t c : i_clones){
            if(c&mask){
                sum += i_freqs[c];
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
    	i_freqs[recombinant] = product;
    }
}

void Host::reset(){
	moi = NAN;
	mean_fitness = NAN;
	#ifndef DTS_CYCLING
		host_drug = NO_DRUG;
	#endif
	std::fill(i_freqs, i_freqs + NUM_UNIQUE_CLONES, 0.0);
	i_clones.clear();
}

void Host::validate_i_freq() const {
	long double sum = 0.0;
	for(int j=0; j<NUM_UNIQUE_CLONES; j++){
		sum += i_freqs[j];
	}
	if(moi && !are_same(sum, 1.0)){
		std::cout << "invalid, f=" << sum << std::endl;
	}
}

void Host::print_summary() const {
	std::cout << (unsigned)moi << "\n";
	std::cout << "mean_fitness: " << mean_fitness << "\n";
	for(const auto& c: i_clones) {
		if(are_same(i_freqs[c], 0)){
			continue;
		}
	    std::cout << "\t" <<"c_" << (unsigned)c << " freq = " << i_freqs[c] << "\n";
	}
}