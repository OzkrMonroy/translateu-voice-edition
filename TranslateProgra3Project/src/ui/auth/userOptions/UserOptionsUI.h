#pragma once
#include <iostream>
#include <string>
#include "../../../controllers/deprecatedManager/TranslateManager.h"
#include "../../../utils/consoleUtils/ConsoleUtils.h"
class WelcomeUI;

class UserOptionsUI {
private:
	TranslateManager manager;
	ConsoleUtils consoleUtils;
	void translatorScreen();
	void translateHistory();
	void topMostSearchedWords();

public:
	UserOptionsUI();
	void run();
};