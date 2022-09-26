#include "Tree.h"



Node::Node(char value)
	:Value{ value }, UseCount{ 0 }, DoesFormWord{ false }
{
	Children = std::map<char, std::shared_ptr<Node>>(); { };
}


Tree::Tree()
	:Head{ std::make_shared<Node>('$') }{}

int Tree::GetCount()
{
	return Head->UseCount;
}

void Tree::addWord(std::string newWord, int currentIndex, std::shared_ptr<Node> current)
{
	current->UseCount++;
	if (newWord.length() == currentIndex)
	{
		current->DoesFormWord = true;
		return;
	}
	
	//std::shared_ptr<Node> temp = std::make_shared<Node>(Node(newWord[currentIndex]));
	if (!current->Children[newWord[currentIndex]])
	{
		current->Children[newWord[currentIndex]] = std::make_shared<Node>(newWord[currentIndex]);
	}
	Tree::addWord(newWord, currentIndex + 1, current->Children[newWord[currentIndex]]);
}

void Tree::AddWord(std::string newWord)
{
	addWord(newWord,0, Head);
}

bool Tree::DoesWordExist(std::string targetWord)
{
	std::shared_ptr<Node> current = Head;
	for (int currentIndex = 0; currentIndex < targetWord.length(); currentIndex ++)
	{
		if (!current->Children[targetWord[currentIndex]])
		{
			return false;
		}
		current = current->Children[targetWord[currentIndex]];
	}
	return current->DoesFormWord;
}


std::string Tree::RecommendWord(std::string root)
{
	std::shared_ptr<Node> current = Head;
	for (int currentIndex = 0; currentIndex < root.length(); currentIndex++)
	{
		if (!current->Children [root[currentIndex]] )
		{
			return root;
		}
		current = current->Children[root[currentIndex]];
	}
	if (current->DoesFormWord)
	{
		return root;
	}

	std::string returnValue = root;
	while (!current->DoesFormWord)
	{
		int greatestValue = 0;
		std::shared_ptr<Node> greatestChild = nullptr;
		for(int i = 97; i < 122; i++)
		{
			if (current->Children[i] && current->Children[i]->UseCount > greatestValue)
			{
				greatestValue = current->Children[i]->UseCount;
				greatestChild = current->Children[i];
			}
		}
		current = greatestChild;
		if (current)
		{
			returnValue += current->Value;
		}
		else
		{
			return root;
		}
	}
	return returnValue;
}