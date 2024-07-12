#include "AutoCompleter.h"
#include "FileHandler.h"
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 3 || (argc <= 3 && (argv[2] == std::string("Add") || argv[2] == std::string("Complete")))) {
		std::cout << "\tERROR: Not enough parametrs" << std::endl;
		return -1;
	}

	bool fileOpened = true;
	try {
		LoadAutoCompleter(argv[1]);
	}
	catch (std::exception) {
		fileOpened = false;
	}

	if (fileOpened) {
		setlocale(LC_ALL, "Ru");
		if (std::string("View") == argv[2]) {
			std::vector<std::string> addedWords = AutoCompleter::GetAddedWords();
			std::cout << "\t|File's " << argv[1] << " contents:" << std::endl;
			for (int i = 0; i < addedWords.size(); i++) {
				std::cout << "\t\t" << addedWords[i] << std::endl;
			}
		}
		else if (std::string("Add") == argv[2]) {
			AutoCompleter::AddWord(argv[3]);
			UnloadAutoCompleter(argv[1]);
		}
		else if (std::string("Complete") == argv[2]) {
			std::vector<std::string> foundWords = AutoCompleter::Complete(argv[3]);
			std::cout << "\t|Results:" << std::endl;
			for (int i = 0; i < foundWords.size(); i++) {
				std::cout << "\t\t" << foundWords[i] << std::endl;
			}
		}
		else {
			std::cout << "\tERROR: Unknown command" << std::endl;
			return -1;
		}
	}
	else {
		std::cout << "\tERROR: Couldn't open the file " << argv[1] << std::endl;
		return -1;
	}
	return 0;
}