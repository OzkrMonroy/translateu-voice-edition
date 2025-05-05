#pragma once
#include <iostream>
#include <string>
#include "../../../controllers/deprecatedManager/TranslateManager.h"



class UserOptionsUI {
private:
	TranslateManager manager;
	void displayMenu() const;
	void handleUserChoise();
	void translatorScreen();
	void translateHistory();
	void topMostSearchedWords();

public:
	UserOptionsUI();
	void run();
};