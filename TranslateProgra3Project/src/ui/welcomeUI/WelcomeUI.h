#pragma once
#include <iostream>
#include <string>

class WelcomeUI {
private:
	void displayWelcomeOptions()const;
	void handleUserChoise();
	void login();
	void registerUser();
	void translator();


public:
	WelcomeUI();
	void run();
};