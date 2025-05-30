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
#include "../../utils/paths/AppPaths.h"

class WelcomeUI;
class UserOptionsUI;

class TranslateUI {
private:
	TranslateManager tManager;
	ConsoleUtils consoleUtils;
	AzureTranslator translator;
	AzureSpeechPlayer player;
	AuthController* authController;
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

public:
	TranslateUI();
	void run();
};