#include <iostream>
#include <bit>

#include "utils.h"

int weighted_dice_roll_with_indices(long double weights[], int num_sides) {
    if (num_sides <= 0) {
           throw std::invalid_argument("Number of sides must > 0");
    }
    uint32_t resolution = 4294967295;
    // Use arc4random_uniform to generate a random number in the range [0, totalWeight).
    uint32_t random_number = arc4random_uniform(resolution);
    long double current_weight = 0;
    
    for (int k=0; k<num_sides; ++k) {
        current_weight += weights[k];
        if (random_number < current_weight * resolution) {
            return k; 
        }
    }
    // This should not happen unless there's an issue with the weights.
    std::cout << "current_weight: " << current_weight << std::endl;
    throw std::logic_error("Invalid weighted dice state.");
}

bool weighted_flip(double prob){
    uint32_t resolution = 4294967295;
    uint32_t random_number = arc4random_uniform(resolution);
    if(random_number < prob * resolution){
        return true;
    }
    else{
        return false;
    }
}

void find_bit_combinations(uint8_t a, uint8_t b, std::unordered_set<uint8_t>& set) {
    if (a == b) {
        set.insert(a);
        return;
    }
    
    uint8_t xor_ab = a ^ b;
    uint8_t mask = 1 << std::countr_zero(xor_ab); // Start at the lowest set bit in a ^ b
    uint8_t highest_bit = 1 << (7 - std::countl_zero(xor_ab)); // Greatest set bit in a ^ b, 7 for 8-bit numbers

    for (; mask <= highest_bit; mask <<= 1) {
        if ((a & mask) != (b & mask)) {
            find_bit_combinations(a & ~mask, b & ~mask, set);
            find_bit_combinations(a | mask, b | mask, set);
            return;
        }
    }
    set.insert(a);
}

bool are_same(long double a, long double b){
    return fabs(a - b) < 0.000000000000001;
}