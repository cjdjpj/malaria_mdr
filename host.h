#pragma once
#include <set>

class Host{
public:
	Host();
	uint8_t moi;
	drug host_drug;
	long double mean_fitness;

	// storing clones and clone freqs for INDIVIDUALS
	std::set<uint8_t> i_clones;
	long double i_freqs[NUM_UNIQUE_CLONES];

	void choose_clones(const long double g_freqs[NUM_UNIQUE_CLONES]);
	void choose_drugs(int generation, int clone_id, const long double avg_fitness_data[NUM_DRUGS], const long double generational_mean_fitness[NUM_GENERATIONS]);
	void recombine();
	void naturally_select(const long double clone_drug_fitness[NUM_UNIQUE_CLONES][NUM_DRUGS]);
	void reset();

	//debug
	void validate_i_freq() const;
	void print_summary() const;
};
