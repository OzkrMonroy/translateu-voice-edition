#pragma once
#include <iostream>
#include <string>
#include "../../../controllers/deprecatedManager/TranslateManager.h"
#include "../../../controllers/authController/AuthController.h"
#include "../../../models/structs/User.h"
#include "../../../utils/consoleUtils/ConsoleUtils.h"
#include "../../../utils/paths/AppPaths.h"
class WelcomeUI;
class TranslateUI;

class UserOptionsUI {
private:
	TranslateManager manager;
	ConsoleUtils consoleUtils;
	AuthController* authController;
	AppPaths appPaths;
	std::optional<User> currentUser;
	void translateHistory();
	void topMostSearchedWords();

public:
	UserOptionsUI();
	void run();
};