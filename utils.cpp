#include <stdexcept>
#include <assert.h>
#include <iostream>

#include "utils.h"

int weighted_dice_roll_with_indices(long double weights[], int num_sides, int indices[]) {
    if (num_sides <= 0) {
           throw std::invalid_argument("Number of sides must > 0");
    }
    uint32_t resolution = 4294967295;
    // Use arc4random_uniform to generate a random number in the range [0, totalWeight).
    uint32_t random_number = arc4random_uniform(resolution);
    long double current_weight = 0;
    
    for (int k=0; k<num_sides; ++k) {
        current_weight += weights[indices[k]];
        if (random_number <= current_weight * resolution) {
            return k; 
        }
    }
    // This should not happen unless there's an issue with the weights.
    std::cout << "current_weight: " << current_weight << std::endl;
    throw std::logic_error("Invalid weighted dice state.");
}

bool are_same(long double a, long double b){
    return fabs(a - b) < 0.00000000000000000000000001;
}