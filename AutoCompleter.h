#pragma once
#include <unordered_map>
#include <string>
#include <vector>

class PrefixTreeNode {
	friend class AutoCompleter;
private:
	char m_Value;
	bool m_EndOfWord;
	std::unordered_map<char, PrefixTreeNode*> m_Children;

	PrefixTreeNode();
	PrefixTreeNode(char value);

	PrefixTreeNode* AddChild(char value);
	bool ContainsChild(char value);
	PrefixTreeNode* GetChild(char value);
};

class AutoCompleter {
private:
	static PrefixTreeNode* m_Root;

	static void DestroyRecursive(PrefixTreeNode* treeNode);
	static void Complete(PrefixTreeNode* currentNode, std::vector<std::string>& ans, std::string word, std::string currentWord, int currentIndex);
	static void GetAddedWords(PrefixTreeNode* currentNode, std::string currentString, std::vector<std::string>& ans);
public:
	AutoCompleter();
	~AutoCompleter();

	static void AddWord(std::string word);
	static void EraseWord(std::string word);
	static bool Contains(std::string word);
	static std::vector<std::string> Complete(std::string word);

	static const std::vector<std::string> GetAddedWords();
};

