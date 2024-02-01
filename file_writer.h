#pragma once
#include <fstream>

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