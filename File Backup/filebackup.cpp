/*
Author: Teran Bukenberger
Date: 2018-09-23
Project: filebackup.cpp
Description: Parses drive and creates backup files, using the FileManager and File classes and their implementations
*/

#include <iostream>	// cin, cout
#include "FileManager.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	// format output for NA
	cout.imbue(locale(""));

	//	create FileManager object, calling the constructor 
	//	based on the number of command line arguments
	if (argc == 1) 
		FileManager fm;
	else if (argc == 2)
		FileManager fm(argv[1]);
	else 
		FileManager fm(argv[1], argv[2]);
}