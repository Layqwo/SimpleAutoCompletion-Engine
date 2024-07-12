#include "FileHandler.h"
#include "AutoCompleter.h"
#include <string>

void LoadAutoCompleter(std::string filePath) {
	std::fstream file = std::fstream(filePath, std::ios::in | std::ios::out);
	std::string fileContents = "";
	if (file.is_open()) {
		while (std::getline(file, fileContents))
			AutoCompleter::AddWord(fileContents);
		file.close();
	}
	else {
		throw std::exception();
	}
}

void UnloadAutoCompleter(std::string filePath) {
	std::fstream file = std::fstream(filePath, std::ios::in | std::ios::out);
	if (file.is_open()) {
		for (int i = 0; i < AutoCompleter::GetAddedWords().size(); i++)
			file << AutoCompleter::GetAddedWords()[i] << '\n';
		file.close();
	}
	else {
		throw std::exception();
	}
}

