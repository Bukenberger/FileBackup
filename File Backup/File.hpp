/*
Author: Teran Bukenberger
Date: 2018-09-23
Project: File.hpp
Description: File class data and headers
*/
#pragma once
#include <vector>
#include <filesystem>
using namespace std::experimental::filesystem;

class File {
public:
	// default constructor
	File() = default;
	
	// 2-arg constructor
	File(path f, std::string s, char c) : filePath_(f), fileName_(s), status_(c) {}

	// getters and setters
	path const& getPathName();
	std::string const& getFileName();
	char& getStatus();

private:
	// data members
	path filePath_;
	std::string fileName_;
	char status_;
};

