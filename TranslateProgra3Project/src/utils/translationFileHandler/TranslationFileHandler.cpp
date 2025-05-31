#include "TranslationFileHandler.h"

using namespace std;
namespace fs = filesystem;

TranslationFileHandler::TranslationFileHandler()
{
	path_to_main = AppPaths::getTranslationsDir();
}

ifstream TranslationFileHandler::getFile(fs::path path)
{
	string jsonFile = (path_to_main / path).string();
	ensureFileExistsWithBaseStructure(path);
	ifstream filePath(jsonFile);

	return filePath;
}

string TranslationFileHandler::getValueFromFile(string& line)
{
	size_t lineStart = line.find(":");
	if (lineStart == string::npos)
		return "";

	lineStart++;
	while (lineStart < line.size() && isspace(line[lineStart]))
	{
		lineStart++;
	}

	if (line[lineStart] == '\"')
	{
		size_t lineEnd = line.find("\"", lineStart + 1);
		if (lineEnd == string::npos)
			return "";
		return line.substr(lineStart + 1, lineEnd - lineStart - 1);
	}
	else
	{
		size_t lineEnd = line.find_first_of(",}", lineStart);
		if (lineEnd == string::npos)
			lineEnd = line.size();
		return line.substr(lineStart, lineEnd - lineStart);
	}
}

void TranslationFileHandler::ensureFileExistsWithBaseStructure(const fs::path& file_path)
{
	string fullPath = (path_to_main / file_path).string();
	fs::create_directories(fs::path(fullPath).parent_path());

	if (!fs::exists(fullPath))
	{
		ofstream outFile(fullPath);
		if (!outFile.is_open())
		{
			cerr << "No se pudo crear el archivo.\n";
			return;
		}

		outFile << "{\n\t\"translates\": [\n\t]\n}";
		outFile.close();
	}
}

void TranslationFileHandler::addTranslationEntry(const WordTranslations& translation, const fs::path& file_path)
{
	string fullPath = (path_to_main / file_path).string();

	ifstream inFile(fullPath);
	string content;
	if (inFile.is_open())
	{
		content.assign((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
		inFile.close();
	}

	if (content.empty())
	{
		content = "{\n\t\"translates\": [\n\t]\n}";
	}

	size_t pos = content.rfind("]");
	if (pos == string::npos)
	{
		cerr << "Archivo con formato incorrecto.\n";
		return;
	}

	size_t arrayStart = content.find("[");
	bool hasEntries = false;

	if (arrayStart != string::npos && arrayStart < pos)
	{
		string arrayContent = content.substr(arrayStart + 1, pos - arrayStart - 1);
		hasEntries = arrayContent.find("{") != string::npos;
	}

	string newEntry = hasEntries ? ",\n\t\t{" : "\n\t\t{";
	newEntry += "\n\t\t\t\"es\": \"" + translation.spanish + "\",";
	newEntry += "\n\t\t\t\"it\": \"" + translation.italian + "\",";
	newEntry += "\n\t\t\t\"fr\": \"" + translation.french + "\",";
	newEntry += "\n\t\t\t\"de\": \"" + translation.german + "\",";
	newEntry += "\n\t\t\t\"en\": \"" + translation.english + "\"";
	newEntry += "\n\t\t}";

	content.insert(pos, newEntry);

	ofstream outFile(fullPath);
	if (!outFile.is_open())
	{
		cerr << "No se pudo abrir el archivo para escritura.\n";
		return;
	}
	outFile << content;
	outFile.close();
}

void TranslationFileHandler::writeAllFromTree(AVLNode* root, const fs::path& file_path, bool encrypt)
{
	std::string fullPath = (path_to_main / file_path).string();
	fs::create_directories(fs::path(fullPath).parent_path());

	std::ofstream outFile(fullPath);
	if (!outFile.is_open())
	{
		std::cerr << "No se pudo abrir el archivo para escritura.\n";
		return;
	}

	outFile << "{\n\t\"translates\": [";

	bool first = true;
	auto writeInOrder = [&](auto&& self, AVLNode* node)
		{
			if (!node)
				return;

			self(self, node->left);

			if (!first)
			{
				outFile << ",";
			}
			else
			{
				first = false;
			}

			WordTranslations translations;
			if (encrypt) {
				encryptWords(translations, node);
			}
			else {
				noEncryptWords(translations, node);
			}

			outFile << "\n\t\t{";
			outFile << "\n\t\t\t\"es\": \"" << translations.spanish << "\",";
			outFile << "\n\t\t\t\"it\": \"" << translations.italian << "\",";
			outFile << "\n\t\t\t\"fr\": \"" << translations.french << "\",";
			outFile << "\n\t\t\t\"de\": \"" << translations.german << "\",";
			outFile << "\n\t\t\t\"en\": \"" << translations.english << "\"";
			outFile << "\n\t\t}";

			self(self, node->right);
		};

	writeInOrder(writeInOrder, root);

	outFile << "\n\t]\n}";
	outFile.close();
}

void TranslationFileHandler::encryptWords(WordTranslations& translations, AVLNode* node){
	translations.spanish = encryptionHelper.encrypter(node->word.spanish);
	translations.italian = encryptionHelper.encrypter(node->word.italian);
	translations.french = encryptionHelper.encrypter(node->word.french);
	translations.german = encryptionHelper.encrypter(node->word.german);
	translations.english = encryptionHelper.encrypter(node->word.english);
}
void TranslationFileHandler::noEncryptWords(WordTranslations& translations, AVLNode* node) {
	translations.spanish = node->word.spanish;
	translations.italian = node->word.italian;
	translations.french = node->word.french;
	translations.german = node->word.german;
	translations.english = node->word.english;
}