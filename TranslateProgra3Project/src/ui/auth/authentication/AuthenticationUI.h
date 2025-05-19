#pragma once
#include <iostream>
#include <string>
#include "../../../utils/consoleUtils/ConsoleUtils.h"
class WelcomeUI;
class UserOptionsUI;

class AuthenticationUI {
private:
	void login(bool &displayScreen);
	void registerUser(bool &displayScreen);
	ConsoleUtils consoleUtils;

public:
	AuthenticationUI();
	void run();
};