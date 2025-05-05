#ifndef AVLNODE_H
#define AVLNODE_H

#include "./WordTranslations.h"

struct AVLNode
{
	WordTranslations word;
	AVLNode* left;
	AVLNode* right;
	int height;

	AVLNode(const WordTranslations& newWord) : word(newWord), left(nullptr), right(nullptr), height(1) {}
};

#endif // AVLNODE_H
