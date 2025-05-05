#pragma once
#include <iostream>
#include "../../controllers/deprecatedManager/TranslateManager.h"

class DeprecatedMainMenu {
private:
	TranslateManager manager;
	void displayMenu() const;
	void handleUserChoise();
	void displayWords();
	void addWord();
	void deleteWord();

public:
	DeprecatedMainMenu();
	void run();
};