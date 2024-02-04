#pragma once
#include <unordered_set>
#include <stdint.h>

class Host{
public:
	Host();
	uint8_t moi;

	// storing clones and clone freqs for INDIVIDUALS
	std::unordered_set<uint8_t> i_clones;
	long double i_freqs[NUM_UNIQUE_CLONES];

	// storing clones and clone freqs for POPULATION
	static std::unordered_set<uint8_t> g_clones;
	static long double g_freqs[NUM_UNIQUE_CLONES];

	void select_clones(long double frequencies[], int total_clones, int indices_for_diceroll[]);
	void recombine();
	void select();
	void reset();
	void print_summary();
};
