﻿#include "TranslateManager.h"
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

TranslateManager* TranslateManager::instance = nullptr;

TranslateManager* TranslateManager::getInstance()
{
    if (instance == nullptr) {
        instance = new TranslateManager();
    }
    return instance;
}

TranslateManager::TranslateManager() : dictionary(), fileHandler() {}

void TranslateManager::loadWordsFromJSONFile(const fs::path& path)
{
    ifstream filePath = fileHandler.getFile(path);

    if (!filePath)
    {
        cout << "Error al abrir el archivo JSON \n" << endl;
        return;
    }

    string currentLine;
    WordTranslations word;
    bool insideArray = false;

    while (getline(filePath, currentLine))
    {
        if (currentLine.find_first_not_of(" \t\r\n") == string::npos)
            continue;

        if (currentLine.find("\"translates\"") != string::npos)
        {
            insideArray = true;
            continue;
        }

        if (!insideArray)
            continue;

        if (currentLine.find("\"es\"") != string::npos)
        {
            word.spanish = encryptionHelper.decrypter(fileHandler.getValueFromFile(currentLine));
        }
        else if (currentLine.find("\"it\"") != string::npos)
        {
            word.italian = encryptionHelper.decrypter(fileHandler.getValueFromFile(currentLine));
        }
        else if (currentLine.find("\"fr\"") != string::npos)
        {
            word.french = encryptionHelper.decrypter(fileHandler.getValueFromFile(currentLine));
        }
        else if (currentLine.find("\"de\"") != string::npos)
        {
            word.german = encryptionHelper.decrypter(fileHandler.getValueFromFile(currentLine));
        }
        else if (currentLine.find("\"en\"") != string::npos)
        {
            word.english = encryptionHelper.decrypter(fileHandler.getValueFromFile(currentLine));
        }
        else if (currentLine.find("\"searchCount\"") != string::npos)
        {
            string countStr = fileHandler.getValueFromFile(currentLine);
            try {
                word.searchCount = stoi(countStr);
            }
            catch (...) {
                word.searchCount = 1;
            }
        }
        else if (currentLine.find("}") != string::npos)
        {
            if (word.spanish.empty() || word.english.empty() ||
                word.italian.empty() || word.french.empty() || word.german.empty())
            {
                cout << "Advertencia: Se omitió una palabra por campos incompletos:\n";
                cout << " -> es: " << word.spanish << ", en: " << word.english << "\n";
            }
            else
            {
                dictionary.insert(word);
            }

            word = WordTranslations();
        }
    }

    filePath.close();
}

void TranslateManager::addWord(const WordTranslations& word, const fs::path& path)
{
    dictionary.insert(word);
    WordTranslations encryptedWord;
    encryptedWord.spanish = encryptionHelper.encrypter(word.spanish);
    encryptedWord.english = encryptionHelper.encrypter(word.english);
    encryptedWord.french = encryptionHelper.encrypter(word.french);
    encryptedWord.italian = encryptionHelper.encrypter(word.italian);
    encryptedWord.german = encryptionHelper.encrypter(word.german);
    fileHandler.addTranslationEntry(encryptedWord, path);
}

WordTranslations* TranslateManager::findWord(const string& spanishWord) {
    return dictionary.findWord(spanishWord);
}

vector<WordTranslations> TranslateManager::getWordLists() {
    vector<WordTranslations> wordList;
    dictionary.inOrderTraversal(wordList);
    return wordList;
}

vector<WordTranslations> TranslateManager::getTopSearchedWords() {
    vector<WordTranslations> wordList = getWordLists();

    std::sort(wordList.begin(), wordList.end(), [](const WordTranslations& a, const WordTranslations& b) {
        return a.searchCount > b.searchCount;
    });

    if (wordList.size() > 5) {
        wordList.resize(5);
    }

    return wordList;
}

void TranslateManager::removeWord(const string& spanish, const fs::path& path)
{
    dictionary.remove(spanish);
    updateFileContent(path, true);
}

void TranslateManager::generateDecriptedFile(const fs::path& path) {
    updateFileContent(path, false);
}

void TranslateManager::updateFileContent(const fs::path& path, bool encrypt) {
    fileHandler.writeAllFromTree(dictionary.getRoot(), path, encrypt);
};