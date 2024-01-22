#include "settings.h"
#include "utils.h"
#include "host.h"

#include <iostream>

long double Host::g_freqs[NUM_UNIQUE_CLONES] = {};
std::unordered_set<uint8_t> Host::g_clones = {};

Host::Host(){
	moi = 0;
	std::unordered_set<uint8_t> i_clones = {};
	long double i_freqs[NUM_UNIQUE_CLONES] = {};
}

void Host::select_clones(long double global_frequencies[], int total_clones, int indices_for_diceroll[]){
	for(int i=0; i<moi; i++){
		//select clones
		int clone_injected = indices_for_diceroll[weighted_dice_roll_with_indices(global_frequencies, total_clones, indices_for_diceroll)];

		//add to i_clones
		i_clones.insert(clone_injected);

		//add associated frequencies
		i_freqs[clone_injected] += (double)1/moi;
	}
}

void Host::reset(){
	moi = 0;
	for(const auto& c: i_clones){
		i_freqs[c] = 0.0;
	}
}

void Host::print_summary(){
	std::cout << (unsigned)moi << "\n";
	for (const auto& c: i_clones) {
		if(are_same(i_freqs[c], 0)){
			continue;
		}
	    std::cout << "\t" <<"c_" << (int)c << " freq = " << i_freqs[c] << "\n";
	}
}

