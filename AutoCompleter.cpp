#include "AutoCompleter.h"

PrefixTreeNode::PrefixTreeNode() {
	m_Value = '\0';
	m_EndOfWord = false;
	m_Children = std::unordered_map<char, PrefixTreeNode*>();
}

PrefixTreeNode::PrefixTreeNode(char value) : PrefixTreeNode() {
	m_Value = value;
}

PrefixTreeNode* PrefixTreeNode::AddChild(char value) {
	return m_Children[value] = new PrefixTreeNode(value);
}

bool PrefixTreeNode::ContainsChild(char value) {
	return m_Children.find(value) != m_Children.end();
}

PrefixTreeNode* PrefixTreeNode::GetChild(char value) {
	return m_Children[value];
}

/////////////////////////////////////////////////////////////////////////////

PrefixTreeNode* AutoCompleter::m_Root;
AutoCompleter mainAutoCompleter = AutoCompleter();

void AutoCompleter::DestroyRecursive(PrefixTreeNode* treeNode) {
	for (auto dictValue : treeNode->m_Children) {
		AutoCompleter::DestroyRecursive(dictValue.second);
	}
	delete treeNode;
}

void AutoCompleter::Complete(PrefixTreeNode* currentNode, std::vector<std::string>& ans, std::string word, std::string currentWord, int currentIndex) {
	if (currentIndex < word.size()) {
		if (!std::isalpha(word[currentIndex]) && currentNode->ContainsChild(word[currentIndex])) {
			AutoCompleter::Complete(currentNode->GetChild(word[currentIndex]), ans, word, currentWord + word[currentIndex], currentIndex + 1);
		}
		else if (std::isalpha(word[currentIndex])) {
			if (currentNode->ContainsChild(std::tolower(word[currentIndex])))
				AutoCompleter::Complete(currentNode->GetChild(std::tolower(word[currentIndex])), ans, word, currentWord + char(std::tolower(word[currentIndex])), currentIndex + 1);

			if (currentNode->ContainsChild(std::toupper(word[currentIndex])))
				AutoCompleter::Complete(currentNode->GetChild(std::toupper(word[currentIndex])), ans, word, currentWord + char(std::toupper(word[currentIndex])), currentIndex + 1);
		}
	}
	else {
		if (currentNode->m_EndOfWord)
			ans.push_back(currentWord);

		for (auto dictValue : currentNode->m_Children) {
			AutoCompleter::Complete(dictValue.second, ans, word, currentWord + dictValue.first, currentIndex);
		}
	}
}

void AutoCompleter::GetAddedWords(PrefixTreeNode* currentNode, std::string currentString, std::vector<std::string>& ans) {
	if (currentNode != m_Root) {
		currentString += currentNode->m_Value;
		if (currentNode->m_EndOfWord)
			ans.push_back(currentString);
	}

	for (auto dictValue : currentNode->m_Children)
		AutoCompleter::GetAddedWords(dictValue.second, currentString, ans);
}

AutoCompleter::AutoCompleter() {
	m_Root = new PrefixTreeNode();
}

AutoCompleter::~AutoCompleter() {
	DestroyRecursive(m_Root);
	m_Root = nullptr;
}

void AutoCompleter::AddWord(std::string word) {
	if (word.size() > 0) {
		PrefixTreeNode* currentNode = m_Root;
		for (int i = 0; i < word.size(); i++) {
			if (currentNode->ContainsChild(word[i]))
				currentNode = currentNode->GetChild(word[i]);
			else
				currentNode = currentNode->AddChild(word[i]);
		}
		currentNode->m_EndOfWord = true;
	}
}

std::vector<std::string> AutoCompleter::Complete(std::string word) {
	std::vector<std::string> ans = std::vector<std::string>();
	AutoCompleter::Complete(m_Root, ans, word, std::string(""), 0);
	return ans;
}

const std::vector<std::string> AutoCompleter::GetAddedWords() {
	std::vector<std::string> ans = std::vector<std::string>();
	AutoCompleter::GetAddedWords(m_Root, "", ans);
	return ans;
}


