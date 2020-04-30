#pragma once
#include <iostream>
#include <string>
#include "Map.h"
#include "Iterator.h"

class HaffmanTree
{
private:
	struct Node
	{
		size_t amount;
		char symbol;
		Node* right;
		Node* left;

		Node(Node* left, Node* right, char symbol, size_t amount)
		{
			this->left = left;
			this->right = right;
			this->symbol = symbol;
			this->amount = amount;
		}
		Node()
		{
			this->amount = 0;
			this->symbol = ' ';
			this->left = nullptr;
			this->right = nullptr;
		}
		~Node()
		{
			this->left = nullptr;
			this->right = nullptr;
		}
	};
	Node* root;
	
	void clear_tree(Node* node)
	{
		if (node != nullptr)
		{
			clear_tree(node->left);
			clear_tree(node->right);
			delete node;
		}
	}
	
	void BuildTree(int lenght, Map<char, int> frequencies);
	void freqQuickSort(Node*, size_t);
	void Create(Map<char, std::string>& code_table, Map<std::string, char>& decode_table, Node* root, std::string&);
	void PrintFreq(Node*, int);
	

public:
	HaffmanTree(std::string symbols);
	~HaffmanTree() { };
	Map <char, std::string> code_table;
	Map <std::string, char> decode_table;
	std::string getCode(std::string &);
	std::string getText(const std::string&, HaffmanTree&);
	float Compression(std::string, std::string);
};