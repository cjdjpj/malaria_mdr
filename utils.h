#pragma once
#include <unordered_set>
#include <vector>

int weighted_dice_roll(const long double weights[], int num_sides);

bool weighted_flip(double prob);

void find_bit_combinations_many(std::vector<uint8_t>& arr, std::unordered_set<uint8_t>& set);

void find_bit_combinations_pair(uint8_t a, uint8_t b, std::unordered_set<uint8_t>& set);

int comb2(int n);

bool are_same(long double a, long double b);