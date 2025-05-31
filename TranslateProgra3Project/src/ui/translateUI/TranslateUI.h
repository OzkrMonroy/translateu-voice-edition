#pragma once
#include <iostream>
#include <string>
#include "../../controllers/deprecatedManager/TranslateManager.h"
#include "../../utils/consoleUtils/ConsoleUtils.h"
#include "../../utils/azureTranslator/AzureTranslator.h"
#include "../../utils/azureSpeechPlayer/AzureSpeechPlayer.h"
#include "../../enums/SupportedLanguages.h"
#include "../../controllers/authController/AuthController.h"
#include "../../models/structs/User.h"
#include "../../models/structs/WordTranslations.h"

class WelcomeUI;
class UserOptionsUI;

class TranslateUI {
private:
	TranslateManager* tManager;
	AuthController* authController;
	ConsoleUtils consoleUtils;
	AzureTranslator translator;
	AzureSpeechPlayer player;
	std::string wordToTranslate;
	std::string englishResult;
	std::string frenchResult;
	std::string italianResult;
	std::string germanResult;
	std::optional<User> currentUser;
	void displayTranslateResult();
	void pronounceWords();
	void verifyUserWantsToHearTheResult();
	void registerWordToFile();
	void translateWords();
	void verifyWordAlreadyExists(std::string& spanishWord);

public:
	TranslateUI();
	void run();
};