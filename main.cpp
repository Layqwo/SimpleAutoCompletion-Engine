#include "AutoCompleter.h"
#include "FileHandler.h"
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 3 || (argc <= 3 && (argv[2] == std::string("Add") || argv[2] == std::string("Complete") || argv[2] == std::string("Erase") || argv[2] == std::string("Contains")))) {
		std::cout << "\tERROR: Not enough parametrs" << std::endl;
		return -1;
	}

	bool fileForReadingOpened = true, fileForWritingOpened = true;
	try {
		LoadAutoCompleter(argv[1]);
	}
	catch (std::exception) {
		fileForReadingOpened = false;
	}


	if (argc >= 5) {
		try {
			UnloadAutoCompleter(argv[4], std::vector<std::string>());
		}
		catch (std::exception) {
			fileForWritingOpened = false;
		}
	}


	if (fileForReadingOpened && fileForWritingOpened) {
		if (argc == 3 && std::string("View") == argv[2]) {
			std::vector<std::string> addedWords = AutoCompleter::GetAddedWords();
			std::cout << "\t|File's " << argv[1] << " contents:" << std::endl;
			for (int i = 0; i < addedWords.size(); i++) {
				std::cout << "\t\t" << addedWords[i] << std::endl;
			}
		}
		else if (argc == 4 && std::string("Contains") == argv[2]) {
			std::cout << "\t|" << (AutoCompleter::Contains(argv[3]) ? "True" : "False") << std::endl;
		}
		else if (argc == 5) {
			if (std::string("Add") == argv[2]) {
				AutoCompleter::AddWord(argv[3]);
				UnloadAutoCompleter(argv[4]);
			}
			else if (std::string("Erase") == argv[2]) {
				try {
					AutoCompleter::EraseWord(argv[3]);
					UnloadAutoCompleter(argv[4]);
				}
				catch (std::exception) {
					std::cout << "\tERROR: No such word" << std::endl;
				}
			}
			else if (std::string("Complete") == argv[2]) {
				std::vector<std::string> foundWords = AutoCompleter::Complete(argv[3]);
				std::cout << "\t|Results:" << std::endl;
				for (int i = 0; i < foundWords.size(); i++) {
					std::cout << "\t\t" << foundWords[i] << std::endl;
				}
				UnloadAutoCompleter(argv[4], foundWords);
			}
		}
		else {
			std::cout << "\tERROR: Unknown command" << std::endl;
			return -1;
		}
	}
	else {
		if (!fileForReadingOpened)
			std::cout << "\tERROR: Couldn't open the file " << argv[1] << std::endl;

		if (!fileForWritingOpened)
			std::cout << "\tERROR: Couldn't open the file " << argv[4] << std::endl;

		return -1;
	}
	return 0;
}