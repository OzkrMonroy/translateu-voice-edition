#pragma once
#include <iostream>
#include <string>
#include "../../../controllers/deprecatedManager/TranslateManager.h"
#include "../../../controllers/authController/AuthController.h"
#include "../../../utils/consoleUtils/ConsoleUtils.h"
#include "../../../models/structs/User.h"
class WelcomeUI;
class TranslateUI;

class UserOptionsUI {
private:
	TranslateManager manager;
	ConsoleUtils consoleUtils;
	AuthController* authController;
	std::optional<User> currentUser;
	void translateHistory();
	void topMostSearchedWords();

public:
	UserOptionsUI();
	void run();
};