/*
Author: Teran Bukenberger
Date: 2018-09-23
Project: File.cpp
Description: File class implementations
*/
#include "File.hpp"
#include <filesystem>
using namespace std::experimental::filesystem;


// filePath getter
path const& File::getPathName() { return filePath_; }

// fileName getter
std::string const& File::getFileName() { return fileName_; }

// status getter
char& File::getStatus() { return status_; }

