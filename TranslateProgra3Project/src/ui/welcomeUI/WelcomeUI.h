#pragma once
#include <iostream>
#include <string>
#include "../../utils/consoleUtils/ConsoleUtils.h"
class AuthenticationUI;
class TranslateUI;

class WelcomeUI {
private:
	ConsoleUtils consoleUtils;

public:
	WelcomeUI();
	void run();
};