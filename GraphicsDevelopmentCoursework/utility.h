#pragma once

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

// declare as static to avoid linking errors
static std::optional<std::string> extractFileContent(const std::string& sourceFile) {
	std::ifstream file(sourceFile);
	if(!file) {
		std::cout << "Error : the file " << sourceFile << " cannot be found" << std::endl;
		return std::optional<std::string>();
	}
	std::string line, sourceCode;
	std::cout << "loading file " + sourceFile << "..." << std::endl;
	while(getline(file, line))
		sourceCode += line + '\n';
	file.close();
	return std::optional<std::string>(sourceCode);
}