#pragma once
#include <unordered_map>
#include <string>
#include <vector>

class PrefixTreeNode {
private:
	char m_Value;

public:
	std::unordered_map<char, PrefixTreeNode*> m_Children;
	PrefixTreeNode();
	PrefixTreeNode(char value);

	PrefixTreeNode* AddChild(char value);
	bool ContainsChild(char value);
	PrefixTreeNode* GetChild(char value, bool checkContains = true);
};

class AutoCompleter {
private:
	static PrefixTreeNode* m_Root;
	static std::vector<std::string> m_WordsAdded;

	static void DestroyRecursive(PrefixTreeNode* treeNode);
	static void Complete(PrefixTreeNode* currentNode, std::vector<std::string>& ans, std::string word, std::string currentWord, int currentIndex);
public:
	AutoCompleter();
	~AutoCompleter();

	static void AddWord(std::string word);
	static std::vector<std::string> Complete(std::string word);
};

