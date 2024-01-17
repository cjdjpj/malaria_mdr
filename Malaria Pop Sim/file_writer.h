#pragma once
#include <fstream>

template<typename T>
void WriteArrayToTxt(T arr, int generations, std::string header, std::string file_name){
	std::ofstream out;
	out.open(file_name);
	out << header << std::endl;
	for(int i=0; i<generations; i++){
		out << arr[i] << std::endl;
	}
	out.close();
}

// template<typename T>
// void Write2dArrayToCSV(T arr, int col, int row, std::string file_name, std::string title){
// 	std::ofstream out;
// 	out.open(file_name);

// 	// header
// 	if(title=="mutation"){
// 		for(int i=1; i<col+1; i++){
// 			out << title <<"_" << dec_to_binary(i) << ",";
// 		}
// 	}
// 	if(title=="clone"){
// 		for(int i=0; i<col; i++){
// 			out << title <<"_" << dec_to_binary(i) << ",";
// 		}
// 	}
// 	out << "\n";

// 	for (int i=0; i<row; i++) {
// 	  	for (int j=0; j<col; j++){
// 	    	out << arr[i][j] <<',';
// 		}
// 	  	out << '\n';
// 	}
// 	out.close();
// }