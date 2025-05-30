#include "TranslateManager.h"
using namespace std;
namespace fs = filesystem;

TranslateManager::TranslateManager() : dictionary(), fileHandler() {}

void TranslateManager::loadWordsFromJSONFile(fs::path path)
{
	ifstream filePath = fileHandler.getFile(path);

	if (!filePath)
	{
		cout << "Error al abrir el archivo JSON \n"
			<< endl;
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
			word.spanish = fileHandler.getValueFromFile(currentLine);
		}
		else if (currentLine.find("\"it\"") != string::npos)
		{
			word.italian = fileHandler.getValueFromFile(currentLine);
		}
		else if (currentLine.find("\"fr\"") != string::npos)
		{
			word.french = fileHandler.getValueFromFile(currentLine);
		}
		else if (currentLine.find("\"de\"") != string::npos)
		{
			word.german = fileHandler.getValueFromFile(currentLine);
		}
		else if (currentLine.find("\"en\"") != string::npos)
		{
			word.english = fileHandler.getValueFromFile(currentLine);
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

void TranslateManager::displayWordsInDictionary()
{
	cout << "\nPalabras en el Diccionario:\n";
	dictionary.inOrderTraversal();
}

void TranslateManager::addWord(const WordTranslations& word, fs::path path)
{
	dictionary.insert(word);
	fileHandler.addTranslationEntry(word, path);
}

void TranslateManager::removeWord(const string& spanish, fs::path path)
{
	dictionary.remove(spanish);
	fileHandler.writeAllFromTree(dictionary.getRoot(), path);
}