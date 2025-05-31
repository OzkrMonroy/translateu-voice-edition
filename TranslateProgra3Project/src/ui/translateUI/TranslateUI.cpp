#include "TranslateUI.h"
#include "../welcomeUI/WelcomeUI.h"
#include "../auth/userOptions/UserOptionsUI.h"
using namespace std;

TranslateUI::TranslateUI() {
	authController = AuthController::getInstance();
	tManager = TranslateManager::getInstance();
	currentUser = authController->getCurrentUser();
}

void TranslateUI::run() {
	consoleUtils.clear();
	consoleUtils.printTitle("Traductor");
	if (!currentUser.has_value()) {
		consoleUtils.writeLine("Solo se traducira al ingles, para traducir a mas idiomas inicia sesion");
	}
	consoleUtils.writeLine("Ingresa la palabra u oracion a traducir:");
	getline(cin,wordToTranslate);
	displayTranslateResult();
}

void TranslateUI::displayTranslateResult() {
	englishResult = translator.translate(wordToTranslate, SupportedLanguages::English);
	consoleUtils.clear();
	consoleUtils.printTitle("Resultado");
	if(currentUser.has_value()){
		frenchResult = translator.translate(wordToTranslate, SupportedLanguages::French);
		italianResult = translator.translate(wordToTranslate, SupportedLanguages::Italian);
		germanResult = translator.translate(wordToTranslate, SupportedLanguages::German);

		registerWordToFile();

		consoleUtils.writeLine("Ingles: " + englishResult);
		consoleUtils.writeLine("Frances: " + frenchResult);
		consoleUtils.writeLine("Italiano: " + italianResult);
		consoleUtils.writeLine("Aleman: " + germanResult);

	}else {
		consoleUtils.writeLine("Ingles: " + englishResult);
	}
	verifyUserWantsToHearTheResult();
}

void TranslateUI::verifyUserWantsToHearTheResult() {
	if (currentUser.has_value()) {
		int choise;
		consoleUtils.writeLine("¿Desea reproducir el audio de alguno de los resultados?");
		consoleUtils.writeLine("1. Si");
		consoleUtils.writeLine("2. No");
		cin >> choise;

		if (choise == 1) {
			pronounceWords();
		}
		else {
			consoleUtils.waitForEnter();
			UserOptionsUI userUI;
			userUI.run();
		}
	}
	else {
		consoleUtils.waitForEnter();
		WelcomeUI welcome;
		welcome.run();
	}
}

void TranslateUI::pronounceWords() {
	UserOptionsUI userUI;
	int choise;
	bool displayScreen = true;

	while (displayScreen) {
		consoleUtils.clear();
		consoleUtils.printTitle("Pronunciacion");
		consoleUtils.writeLine("Seleccione el numero de la opcion que desea realizar");
		consoleUtils.writeLine("1. Reproducir en español");
		consoleUtils.writeLine("2. Reproducir en inglés");
		consoleUtils.writeLine("3. Reproducir en francés");
		consoleUtils.writeLine("4. Reproducir en italiano");
		consoleUtils.writeLine("5. Reproducir en alemán");
		consoleUtils.writeLine("6. Volver a la pantalla principal");

		cin >> choise;
		cin.ignore();

		switch (choise) {
		case 1:
			consoleUtils.write("Reproduciendo...");
			player.speakText(wordToTranslate, SupportedLanguages::Spanish);
			break;
		case 2:
			consoleUtils.write("Reproduciendo...");
			player.speakText(englishResult, SupportedLanguages::English);
			break;
		case 3:
			consoleUtils.write("Reproduciendo...");
			player.speakText(frenchResult, SupportedLanguages::French);
			break;
		case 4:
			consoleUtils.write("Reproduciendo...");
			player.speakText(italianResult, SupportedLanguages::Italian);
			break;
		case 5:
			consoleUtils.write("Reproduciendo...");
			player.speakText(germanResult, SupportedLanguages::German);
			break;
		case 6:
			consoleUtils.writeLine("...");
			consoleUtils.wait(500);
			userUI.run();
			displayScreen = false;
			break;
		default:
			consoleUtils.writeLine("Opción no válida. Intente de nuevo.");
			break;
		}
	}
};

void TranslateUI::registerWordToFile(){
	WordTranslations word;
	word.spanish = wordToTranslate;
	word.english = englishResult;
	word.french = frenchResult;
	word.italian = italianResult;
	word.german = germanResult;
	string fileName = currentUser.value().userFile + ".ly";

	tManager->addWord(word, fileName);
}