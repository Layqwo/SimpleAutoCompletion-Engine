#include "AutoCompleter.h"
#include <iostream>

int main(int argc, char** argv) {
	AutoCompleter::AddWord("m_WordsAdded");
	AutoCompleter::AddWord("m_Root");
	AutoCompleter::AddWord("Yep!");
	AutoCompleter::AddWord("Morphling");

	std::vector<std::string> foundWords = AutoCompleter::Complete("m_WordsAdded");
	for (int i = 0; i < foundWords.size(); i++) {
		std::cout << foundWords[i] << std::endl;
	}
	return 0;
}