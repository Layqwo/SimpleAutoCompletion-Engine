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
	std::fstream file = std::fstream(filePath, std::ios::app);
	if (file.is_open()) {
		file.close();
		file = std::fstream(filePath, std::ios::in | std::ios::out | std::ios::trunc);
		std::vector<std::string> addedWords = AutoCompleter::GetAddedWords();
		for (int i = 0; i < addedWords.size(); i++)
			file << addedWords[i] << '\n';
		file.close();
	}
	else {
		throw std::exception();
	}
}

void UnloadAutoCompleter(std::string filePath, std::vector<std::string> data) {
	std::fstream file = std::fstream(filePath, std::ios::app);
	if (file.is_open()) {
		file.close();
		file = std::fstream(filePath, std::ios::in | std::ios::out | std::ios::trunc);
		for (int i = 0; i < data.size(); i++)
			file << data[i] << '\n';
		file.close();
	}
	else {
		throw std::exception();
	}
}

