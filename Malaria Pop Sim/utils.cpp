#include <stdexcept>
#include <assert.h>

#include "utils.h"

int weighted_dice_roll_with_indices(long double weights[], int num_sides, int indices[]) {
    if (num_sides <= 0) {
           throw std::invalid_argument("Number of sides must > 0");
    }
    const int resolution = 1000000000;
    // Use arc4random_uniform to generate a random number in the range [0, totalWeight).
    unsigned int randomNumber = arc4random_uniform(resolution);
    double current_weight = 0;
    
    for (int k=0; k<num_sides; ++k) {
        current_weight += weights[indices[k]];
        if (randomNumber <= current_weight * resolution) {
            return k; // Adding 1 to make the result 1-based (like a standard dice).
        }
    }
    // This should not happen unless there's an issue with the weights.
    throw std::logic_error("Invalid weighted dice state.");
}