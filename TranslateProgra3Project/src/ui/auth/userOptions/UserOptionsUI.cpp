#include "UserOptionsUI.h"
#include "../../welcomeUI/WelcomeUI.h"
#include "../../translateUI/TranslateUI.h"
using namespace std;

UserOptionsUI::UserOptionsUI()
{
	authController = AuthController::getInstance();
	manager = TranslateManager::getInstance();
}

void UserOptionsUI::run()
{
	WelcomeUI welcome;
	TranslateUI translateUI;
	currentUser = authController->getCurrentUser();
	string name = "";
	if (currentUser.has_value()) {
		name = currentUser.value().name;
		string fileName = currentUser.value().userFile + ".ly";
		manager->loadWordsFromJSONFile(fileName);
	}

	int choise;
	bool displayScreen = true;

	while (displayScreen) {
		consoleUtils.clear();
		consoleUtils.printTitle("Bienvenido " + name);
		consoleUtils.writeLine("Seleccione el n�mero de la opcion que desea realizar:");
		consoleUtils.writeLine("1. Traducir");
		consoleUtils.writeLine("2. Ver historial de traducciones");
		consoleUtils.writeLine("3. Top de palabras m�s buscadas");
		consoleUtils.writeLine("4. Generar archivo desencriptado");
		consoleUtils.writeLine("5. Cerrar sesion");

		cin >> choise;
		cin.ignore();

		switch (choise)
		{
		case 1:
			translateUI.run();
			displayScreen = false;
			break;
		case 2:
			translateHistory();
			displayScreen = false;
			break;
		case 3:
			topMostSearchedWords();
			displayScreen = false;
			break;
		case 4: 
			generateDecriptedFile();
			displayScreen = false;
			break;
		case 5:
			authController->logout();
			consoleUtils.writeLine("Cerrando sesion...");
			consoleUtils.wait(2000);
			welcome.run();
			displayScreen = false;
			break;
		default:
			cout << "Opci�n no v�lida. Intente de nuevo.\n";
			break;
		}
	}
}

void UserOptionsUI::translateHistory()
{
	vector<WordTranslations> wordList = manager->getWordLists();
	consoleUtils.printTitle("Historial de b�squedas");
	for (size_t i = 0; i < wordList.size(); ++i) {
		consoleUtils.writeLine("=== " + to_string(i + 1) + ". " + wordList[i].spanish + " ===");
		consoleUtils.writeLine("Ingl�s: " + wordList[i].english);
		consoleUtils.writeLine("Italiano: " + wordList[i].italian);
		consoleUtils.writeLine("Franc�s: " + wordList[i].french);
		consoleUtils.writeLine("Alem�n: " + wordList[i].german);
	}
	askForDelete(wordList);
}

void UserOptionsUI::askForDelete(vector<WordTranslations>& wordList) {
	int choise;
	consoleUtils.writeLine("�Desea eliminar una palabra y su traducci�n?");
	consoleUtils.writeLine("1. Si");
	consoleUtils.writeLine("2. No");

	cin >> choise;

	if(choise == 1){
		deleteWord(wordList);
	}
	else {
		consoleUtils.writeLine("Regresando al men� anterior...");
		consoleUtils.wait(500);
		run();
	}
}

void UserOptionsUI::deleteWord(vector<WordTranslations>& wordList) {
	string fileName = currentUser.value().userFile + ".ly";
	consoleUtils.writeLine("Ingrese el n�mero de la palabra a eliminar: ");
	int index;
	cin >> index;
	cin.ignore();

	if (index > 0 && index <= wordList.size()) {
		std::string wordToDelete = wordList[index - 1].spanish;
		manager->removeWord(wordToDelete, fileName);
		consoleUtils.writeLine("Palabra eliminada correctamente.");
		consoleUtils.wait(750);
		translateHistory();
	}
	else {
		consoleUtils.writeLine("�ndice inv�lido.");
	}
}

void UserOptionsUI::topMostSearchedWords()
{
	consoleUtils.printTitle("Top 5 palabras m�s buscadas");
	vector<WordTranslations> topWords = manager->getTopSearchedWords();
	int index = 1;
	for (WordTranslations word : topWords) {
		consoleUtils.writeLine(to_string(index++) + ". " + word.spanish + " (buscada " + to_string(word.searchCount) + " veces)");
	}
	consoleUtils.waitForEnter();
	run();
}

void UserOptionsUI::generateDecriptedFile() {
	consoleUtils.clear();
	consoleUtils.writeLine("Generando archivo...");
	string fileName = currentUser.value().userFile + ".dec";
	manager->generateDecriptedFile(fileName);
	consoleUtils.wait(750);
	consoleUtils.writeLine("Archivo generado con exito!");
	consoleUtils.writeLine("Regresando a la pantalla anterior...");
	consoleUtils.wait(750);
	run();
}


