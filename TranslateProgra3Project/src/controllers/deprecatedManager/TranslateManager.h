// TranslateManager.h
#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "../../models/avlTree/DictionaryAVLTree.h"
#include "../../utils/TranslationFileHandler/TranslationFileHandler.h"
#include "../../utils/encryptionHelper/EncrytionHelper.h"

class TranslateManager
{
private:
    static TranslateManager* instance;
    DictionaryAVLTree dictionary;
    TranslationFileHandler fileHandler;
    EncrytionHelper encryptionHelper;

    TranslateManager();
    ~TranslateManager() = default;

    TranslateManager(const TranslateManager&) = delete;
    TranslateManager& operator=(const TranslateManager&) = delete;
    TranslateManager(TranslateManager&&) = delete;
    TranslateManager& operator=(TranslateManager&&) = delete;

public:
    static TranslateManager* getInstance();

    void loadWordsFromJSONFile(const std::filesystem::path& path);
    void addWord(const WordTranslations& word, const std::filesystem::path& path);
    void removeWord(const std::string& spanish, const std::filesystem::path& path);
    WordTranslations* findWord(const std::string& spanishWord);
    std::vector<WordTranslations> getWordLists();
    void generateDecriptedFile(const std::filesystem::path& path);
};
