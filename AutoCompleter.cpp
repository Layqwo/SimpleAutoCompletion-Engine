#include "AutoCompleter.h"

PrefixTreeNode::PrefixTreeNode() {
	m_Value = '\0';
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

PrefixTreeNode* PrefixTreeNode::GetChild(char value, bool checkContains) {
	return m_Children[value];
}

/////////////////////////////////////////////////////////////////////////////

PrefixTreeNode* AutoCompleter::m_Root;
std::vector<std::string> AutoCompleter::m_WordsAdded;
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
		if (std::find(m_WordsAdded.begin(), m_WordsAdded.end(), currentWord) != m_WordsAdded.end())
			ans.push_back(currentWord);

		for (auto dictValue : currentNode->m_Children) {
			AutoCompleter::Complete(dictValue.second, ans, word, currentWord + dictValue.first, currentIndex);
		}
	}
}

AutoCompleter::AutoCompleter() {
	m_Root = new PrefixTreeNode();
}

AutoCompleter::~AutoCompleter() {
	DestroyRecursive(m_Root);
	m_Root = nullptr;
}

void AutoCompleter::AddWord(std::string word) {
	PrefixTreeNode* currentNode = m_Root;
	for (int i = 0; i < word.size(); i++) {
		if (currentNode->ContainsChild(word[i]))
			currentNode = currentNode->GetChild(word[i]);
		else {
			currentNode = currentNode->AddChild(word[i]);
		}
	}

	if (std::find(m_WordsAdded.begin(), m_WordsAdded.end(), word) == m_WordsAdded.end())
		m_WordsAdded.push_back(word);
}

std::vector<std::string> AutoCompleter::Complete(std::string word) {
	std::vector<std::string> ans = std::vector<std::string>();
	AutoCompleter::Complete(m_Root, ans, word, std::string(""), 0);
	return ans;
}


