#pragma once
#include <iostream>
#include <string>
#include "../../../controllers/deprecatedManager/TranslateManager.h"
#include "../../../controllers/authController/AuthController.h"
#include "../../../models/structs/User.h"
#include "../../../models/avlTree/DictionaryAVLTree.h"
#include "../../../utils/consoleUtils/ConsoleUtils.h"
class WelcomeUI;
class TranslateUI;

class UserOptionsUI {
private:
	TranslateManager* manager;
	ConsoleUtils consoleUtils;
	AuthController* authController;
	AppPaths appPaths;
	std::optional<User> currentUser;
	void translateHistory();
	void topMostSearchedWords();
	void generateDecriptedFile();

public:
	UserOptionsUI();
	void run();
};