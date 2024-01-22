#pragma once
#include <unordered_set>
#include <stdint.h>

class Host{
public:
	Host();
	uint8_t moi;
	enum Strata : uint8_t{
		HOST_DRUGFREE, HOST_DRUGTREATED
	};

	// storing clones and clone freqs for INDIIVIDUALS
	std::unordered_set<uint8_t> i_clones;
	long double i_freqs[NUM_UNIQUE_CLONES];

	// storing clones and clone freqs for POPULATION
	static long double g_freqs[NUM_UNIQUE_CLONES];
	static std::unordered_set<uint8_t> g_clones;

	void select_clones(long double frequencies[], int total_clones, int indices_for_diceroll[]);
	void reset();
	void print_summary();
};
