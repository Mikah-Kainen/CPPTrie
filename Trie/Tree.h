#pragma once
#include <string>
#include <map>
#include <memory>

class Node
{

public:
	char Value;
	int UseCount;
	bool DoesFormWord;
	std::map<char, std::shared_ptr<Node>> Children;

	Node(char value);
};

class Tree
{
private:
	void addWord(std::string newWord, int currentIndex, std::shared_ptr<Node> currentNode);
	
public:
	std::shared_ptr<Node> Head;

	int GetCount();
	void AddWord(std::string newWord);
	bool DoesWordExist(std::string targetWord);
	std::string RecommendWord(std::string root);

	Tree();
	~Tree();
};

