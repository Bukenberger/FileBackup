/*
Author: Teran Bukenberger
Date: 2018-09-23
Project: FileManager.hpp
Description: header file used to store FileManager class and it's data
*/
#pragma once

#include "File.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <string>
using namespace std::experimental::filesystem;

class FileManager {
	// data members
	path sourceDir = current_path();// Current working directory
	path backupDir = "C:\\backup";	// backup directory
	uintmax_t totalSize = 0;		// total size of files backed up
	unsigned numFiles = 0;			// number of files backed up
	std::vector<File> sourcePaths;	// hold paths
	unsigned pathSize_ = 0;		// length of path name in characters
public:
	// default constructor
	FileManager() {
		if (!exists("C:\\backup"))
			create_directory("C:\\backup");
		printDirectories();
		getPaths();
		backup();
		report();
	};
	// one arg constructor
	FileManager(path sd)
		: sourceDir(sd) {
		if (!exists(sd))
			sourceDir = current_path();
		if (!exists("C:\\backup"))
			create_directory("C:\\backup");
		printDirectories();
		getPaths();
		backup();
		report();
	}

	// two arg constructor
	FileManager(path sd, path bd)
		: sourceDir(sd), backupDir(bd) {
		if (!exists(sd))
			sourceDir = current_path();
		if (!exists(backupDir))
			backupDir = "C:\\backup";
		printDirectories();
		getPaths();
		backup();
		report();
	}

	// copy constructor
	FileManager(FileManager const&);

	// copy assignment operator
	FileManager& operator=(FileManager const&);

	FileManager(FileManager&&) = delete; // disable move constructor
	FileManager& operator= (FileManager&&) = delete; //disable move assignment operator
	~FileManager() = default;

	void getPaths();// populate paths vector with all appropriate files
	void backup();	// backup files from source directory
	void report();	// shows files in source directory
	void printDirectories(); // print directories on execution
	path const& getSource();	// getter for source directory
	path const& getBackup();	// getter for source directory
};