#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include "../../models/structs/WordTranslations.h"
#include "../../models/structs/AVLNode.h"
#include "../paths/AppPaths.h"

class TranslationFileHandler
{
private:
	std::filesystem::path path_to_main;

public:
	TranslationFileHandler();
	std::string getValueFromFile(std::string& line);
	std::ifstream getFile(std::filesystem::path path);
	void addTranslationEntry(const WordTranslations& translation, const std::filesystem::path& file_path);
	void ensureFileExistsWithBaseStructure(const std::filesystem::path& file_path);
	void ensureDirectoryExists(const std::string& folderPath);
	void writeAllFromTree(AVLNode* root, const std::filesystem::path& file_path);
};