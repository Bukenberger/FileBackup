/*
Author: Teran Bukenberger
Date: 2018-09-23
Project: FileManager.cpp
Description: FileManager class implementations
*/
#include <iomanip>	// format output
#include "FileManager.hpp"
#include "File.hpp"



// copy constructor
 FileManager::FileManager(FileManager const &rhs)
	: sourceDir(rhs.sourceDir), backupDir(rhs.backupDir), totalSize(rhs.totalSize) {
	 getPaths();
	 backup();
	 report();
 }

// copy assignment operator
 FileManager& FileManager::operator = (FileManager const &rhs)
{
	sourceDir = rhs.sourceDir;
	backupDir = rhs.backupDir;
	totalSize = rhs.totalSize;
	return *this;
}

/*
Function Name: getSource()
Purpose: return the source directory, so it is accessible outside of the class
Accepts: nothing
Returns: path
*/
path const& FileManager::getSource() {
	return sourceDir;
}

/*
Function Name: getBackup()
Purpose: return the backup directory, so it is accessible outside of the class
Accepts: nothing
Returns: path
*/
path const& FileManager::getBackup() {
	return backupDir;
}

/*
Function Name: printDirectories()
Purpose: print source and backup directories to console
Accepts: nothing
Returns: void
*/
void FileManager::printDirectories() {
	std::cout << "Root Directory: " << absolute(sourceDir) << std::endl;
	std::cout << "Backup Directory: " << absolute(backupDir) << std::endl;
}

/*
Function Name: getPaths()
Purpose: populates sourcePaths vector with files in the source directory
Accepts: nothing
Returns: void
*/
void FileManager::getPaths() {
	for (auto &d : recursive_directory_iterator(sourceDir)) {
		std::string sBackup = backupDir.string();
		std::string sFileName = d.path().filename().string();
		path temp = sBackup + "\\" + sFileName;
		// validate extension
		if (d.path().extension() == ".cpp" || d.path().extension() == ".c" || d.path().extension() == ".hpp" || d.path().extension() == ".h") {
		//if (d.path().extension() == ".mp3") {
			// find length of largest path name
			if (sFileName.size() > pathSize_)
				pathSize_ = sFileName.size();
			if (!exists(temp)) {
				File f(d, d.path().filename().string(), '+');
				sourcePaths.push_back(f);
				numFiles++;
			} else {
				File f(d, d.path().filename().string(), '-');
				sourcePaths.push_back(f);
			}
		}
	}
}

/*
Function Name: backup()
Purpose: create backup files by recursively scanning the source directory,
		 and copying them over to the backup directory
Accepts: nothing
Returns: void
*/
void FileManager::backup() {
	for (auto &p : sourcePaths) {
		std::string sBackup = backupDir.string();
		std::string sFileName = p.getFileName();
		path temp = sBackup + "\\" + sFileName;
		if (p.getStatus() == '+') {
			copy(p.getPathName(), backupDir);
			totalSize += file_size(p.getPathName());
		}
	}// end loop
}// end function

/*
Function Name: report()
Purpose: shows files in the source directory, whether they've been backed up, and their size
Accepts: nothing
Returns: void
*/
void FileManager::report() {
	for (auto &p : sourcePaths) {
		std::cout << p.getStatus() << std::setw(pathSize_) << p.getFileName() << std::setw(25) << " Size: " << file_size(p.getPathName()) << std::endl;
	}
	std::cout << "BackUp Total: " << std::setw(pathSize_ - 13) << numFiles << std::setw(25) << " Size: " << totalSize << std::endl;
}