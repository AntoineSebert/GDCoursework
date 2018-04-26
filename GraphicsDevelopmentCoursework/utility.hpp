#pragma once

#include <fstream>
#include <iostream>
#include <string>

// declare as static to avoid linking errors
static std::string extractFileContent(const std::string& sourceFile) {
	std::ifstream file(sourceFile);
	if(!file) {
		std::cout << "Error : the file " << sourceFile << " cannot be found" << std::endl;
		return "";
	}
	std::string line, sourceCode;
	std::cout << "loading file " + sourceFile << "..." << std::endl;
	while(getline(file, line))
		sourceCode += line + '\n';
	file.close();
	return sourceCode;
}