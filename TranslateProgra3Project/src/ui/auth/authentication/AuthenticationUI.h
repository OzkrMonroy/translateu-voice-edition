#pragma once
#include <iostream>
#include <string>
#include "../../../utils/consoleUtils/ConsoleUtils.h"
#include "../../../controllers/authController/AuthController.h"
class WelcomeUI;
class UserOptionsUI;

class AuthenticationUI {
private:
	void login(bool &displayScreen);
	void registerUser(bool &displayScreen);
	ConsoleUtils consoleUtils;
	AuthController* controller;

public:
	AuthenticationUI();
	void run();
};