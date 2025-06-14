#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include "../../models/structs/WordTranslations.h"
#include "../../models/structs/AVLNode.h"
#include "../paths/AppPaths.h"
#include "../encryptionHelper/EncrytionHelper.h"

class TranslationFileHandler
{
private:
	std::filesystem::path path_to_main;
	EncrytionHelper encryptionHelper;
	void encryptWords(WordTranslations& translation, AVLNode* node);
	void noEncryptWords(WordTranslations& translation, AVLNode* node);

public:
	TranslationFileHandler();
	std::string getValueFromFile(std::string& line);
	std::ifstream getFile(std::filesystem::path path);
	void addTranslationEntry(const WordTranslations& translation, const std::filesystem::path& file_path);
	void ensureFileExistsWithBaseStructure(const std::filesystem::path& file_path);
	void writeAllFromTree(AVLNode* root, const std::filesystem::path& file_path, bool encrypt);
};