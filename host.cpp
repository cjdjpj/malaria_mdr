#include "settings.h"
#include "utils.h"
#include "host.h"

#include <iostream>

Host::Host() : moi(NAN), mean_fitness(NAN), host_drug(NO_DRUG), i_clones(), i_freqs{}{}

void Host::choose_clones(const long double g_freqs[NUM_UNIQUE_CLONES]){
	for(int i=0; i<moi; i++){
		//select clones
		int clone_injected = weighted_dice_roll(g_freqs, NUM_UNIQUE_CLONES);

		//add to i_clones
		i_clones.insert(clone_injected);

		//add associated frequencies
		i_freqs[clone_injected] += (long double)1/moi;
	}
}

void Host::choose_drugs(int generation, int clone_id , const long double clone_drug_avg_fitness[NUM_DRUGS], const long double generational_mean_fitness[NUM_GENERATIONS]){

	if(clone_id > NUM_HOSTS * TREATED_PROP){
		host_drug = NO_DRUG;
		return;
	}

	#ifdef DTS_SINGLE
	host_drug = SINGLE_DRUG;
	#endif

	#ifdef DTS_MFT
	if(clone_id < NUM_HOSTS/3){
		host_drug = MFT_DRUG1;
	}
	else if(clone_id >= NUM_HOSTS/3 && clone_id < 2*NUM_HOSTS/3){
		host_drug = MFT_DRUG2;
	}
	else{
		host_drug = MFT_DRUG3;
	}
	#endif

	#ifdef DTS_CYCLING
	if(generation == 0){
		host_drug = CYCLING_DRUG1;
		return;
	}
	if(generational_mean_fitness[generation] > clone_drug_avg_fitness[(int)host_drug]){
		if(host_drug == CYCLING_DRUG1){
			host_drug = CYCLING_DRUG2;
		}
		else if(host_drug == CYCLING_DRUG2){
			host_drug = CYCLING_DRUG3;
		}
		else{
			host_drug = CYCLING_DRUG1;
		}
	}
	#endif
}


void Host::naturally_select(const long double clone_drug_fitness[NUM_UNIQUE_CLONES][NUM_DRUGS]){
	mean_fitness = 0.0;
	if(!moi){
		return;
	}
	for(const auto& c: i_clones){
		mean_fitness += clone_drug_fitness[c][host_drug] * i_freqs[c];
	}
	for(const auto& c: i_clones){
		i_freqs[c] = (clone_drug_fitness[c][host_drug] * i_freqs[c])/mean_fitness;
	}
}


void Host::recombine(){
	if(!weighted_flip(RECOMBINATION_RATE) || !moi){
		return;
	}
    long double new_freqs[NUM_UNIQUE_CLONES]{};
    for (const auto p1 : i_clones) {
        for (const auto p2 : i_clones) {
            if(p1 == p2){
                new_freqs[p1] += i_freqs[p1] * i_freqs[p1];
                continue;
            }
            std::set<uint8_t> recombinants {};
            find_bit_combinations_pair(p1, p2, recombinants);
            for(const auto& c : recombinants){
                long double recombinant_freq = (i_freqs[p1] * i_freqs[p2])/recombinants.size();
                if(opposite_chr5_alleles(p1, p2)){
                    if(diff_chr5_alleles(c, p1) && diff_chr5_alleles(c, p2)){
                        recombinant_freq = recombinant_freq*2 * CHR5_UNLINKED_PROB;
                    }
                    else{
                        recombinant_freq = recombinant_freq*2 * (1-CHR5_UNLINKED_PROB);
                    }
                }
                if(!are_same(recombinant_freq, 0.0)){
	                new_freqs[c] += recombinant_freq;
	                i_clones.insert(c);
                }

            }
        }
    }
    std::copy(std::begin(new_freqs), std::end(new_freqs), std::begin(i_freqs));
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
	long double sum2 = 0.0;
	for(int j=0; j<NUM_UNIQUE_CLONES; j++){
		sum += i_freqs[j];
	}
	for(const auto& c : i_clones){
		sum2 += i_freqs[c];
	}
	if(moi && !are_same(sum, 1.0) && !are_same(sum2, 1.0)){
		std::cout << "invalid, f=" << sum << std::endl;
		print_summary();
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