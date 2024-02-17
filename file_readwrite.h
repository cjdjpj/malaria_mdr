#pragma once
#include <fstream>
#include <sstream>
#include "settings.h"

void read_csv_to_2d_array_drug(const std::string& file_path, long double (&data)[NUM_UNIQUE_CLONES][NUM_DRUGS]) {
    std::ifstream file(file_path);

    std::string line;
    int row = 0;
    while (getline(file, line) && row < NUM_UNIQUE_CLONES) {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;
        while (getline(ss, cell, ',') && col < NUM_DRUGS) {
            data[row][col++] = std::stod(cell);
        }
        ++row;
    }
}

void write_2d_array_to_csv_clonefreq(const std::string& file_path, long double (&data)[NUM_GENERATIONS][NUM_UNIQUE_CLONES]) {
    std::ofstream file(file_path);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (int row = 0; row < NUM_GENERATIONS; ++row) {
        for (int col = 0; col < NUM_UNIQUE_CLONES; ++col) {
            file << std::setprecision(17) << data[row][col];
            if (col != NUM_UNIQUE_CLONES - 1) {
                file << ",";
            }
        }
        file << std::endl;
    }
}

void write_array_to_csv(const std::string& file_path, long double (&data)[NUM_GENERATIONS]) {
    std::ofstream file(file_path);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (int row = 0; row < NUM_GENERATIONS; ++row) {
        file << std::setprecision(17) << data[row];
        file << std::endl;
    }
}