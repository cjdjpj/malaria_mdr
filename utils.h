#pragma once
#include <unordered_set>

int weighted_dice_roll_with_indices(long double weights[], int num_sides);

bool weighted_flip(double prob);

void find_bit_combinations(uint8_t a, uint8_t b, std::unordered_set<uint8_t>& set);

bool are_same(long double a, long double b);