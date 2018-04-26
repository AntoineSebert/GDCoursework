#pragma once

#include <fstream>
#include <iostream>
#include <string>

std::string extractFileContent(const std::string& sourceFile) {
	std::ifstream file(sourceFile);
	if(!file) {
		std::cout << "Error : the file " << sourceFile << " cannot be found" << std::endl;
		return "";
	}
	std::string line, sourceCode;
	while(getline(file, line))
		sourceCode += line + '\n';
	file.close();
	return sourceCode;
}