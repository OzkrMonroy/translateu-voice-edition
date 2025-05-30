#pragma once
#include <iostream>
#include <string>
#include "../../models/avlTree/DictionaryAVLTree.h"
#include "../../utils/TranslationFileHandler/TranslationFileHandler.h"

class TranslateManager
{
private:
	DictionaryAVLTree dictionary;
	TranslationFileHandler fileHandler;

public:
	TranslateManager();
	void loadWordsFromJSONFile(std::filesystem::path path);
	void displayWordsInDictionary();
	void addWord(const WordTranslations& word, std::filesystem::path path);
	void removeWord(const std::string& spanish, std::filesystem::path path);
};