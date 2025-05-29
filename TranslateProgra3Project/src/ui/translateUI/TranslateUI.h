#pragma once
#include <iostream>
#include <string>
#include "../../controllers/deprecatedManager/TranslateManager.h"
#include "../../utils/consoleUtils/ConsoleUtils.h"
#include "../../utils/azureTranslator/AzureTranslator.h"
#include "../../utils/azureSpeechPlayer/AzureSpeechPlayer.h"
#include "../../enums/SupportedLanguages.h"
class WelcomeUI;
class UserOptionsUI;

class TranslateUI {
private:
	TranslateManager tManager;
	ConsoleUtils consoleUtils;
	AzureTranslator translator;
	AzureSpeechPlayer player;
	std::string wordToTranslate;
	std::string englishResult;
	std::string frenchResult;
	std::string italianResult;
	std::string germanResult;
	bool isAuthenticated;
	void displayTranslateResult();
	void pronounceWords();
	void verifyUserWantsToHearTheResult();

public:
	TranslateUI();
	void run();
};