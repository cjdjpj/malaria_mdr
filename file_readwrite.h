#pragma once
#include <fstream>
#include <sstream>
#include "settings.h"

template<typename T>
void write_array_to_txt(T arr, int generations, std::string header, std::string file_name){
	std::ofstream out;
	out.open(file_name);
	out << header << std::endl;
	for(int i=0; i<generations; i++){
		out << arr[i] << std::endl;
	}
	out.close();
}

void read_csv_to_2d_array(const std::string& file_path, long double (&data)[NUM_UNIQUE_CLONES][NUM_DRUGS]) {
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