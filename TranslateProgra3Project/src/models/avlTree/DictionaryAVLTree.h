#pragma once
#include <vector>
#include "../structs/AVLNode.h"
#include "../../utils/consoleUtils/ConsoleUtils.h"
#include "../../utils/stringUtils/StringUtils.h"

class DictionaryAVLTree
{
public:
	DictionaryAVLTree();
	~DictionaryAVLTree();

	void insert(const WordTranslations& word);
	void remove(const std::string& word);
	void inOrderTraversal(std::vector<WordTranslations>& words) const;
	WordTranslations* findWord(const std::string& spanishWord);
	AVLNode* getRoot() const;

private:
	AVLNode* root;
	ConsoleUtils console;

	AVLNode* insert(AVLNode* node, const WordTranslations& word);
	AVLNode* removeNode(AVLNode* node, const std::string& word);
	AVLNode* findMinNode(AVLNode* node);
	int getHeight(AVLNode* node);
	int getBalanceFactor(AVLNode* node);

	AVLNode* rotateRight(AVLNode* unbalancedNode);
	AVLNode* rotateLeft(AVLNode* unbalancedNode);

	void inOrderTraversal(AVLNode* node, std::vector<WordTranslations>& words) const;
	void destroyTree(AVLNode* node);
};