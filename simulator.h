#pragma once
#include <random>

std::random_device rd; // uniformly-distributed integer random number generator
std::mt19937 rng (rd ()); // mt19937: Pseudo-random number generation
std::poisson_distribution<> poisson_generator;
long double poisson_mean;

int num_infected;