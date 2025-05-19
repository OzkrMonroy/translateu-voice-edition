#include <windows.h>
#include <iostream>
#include "./src/ui/welcomeUI/WelcomeUI.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	WelcomeUI welcomeUI;
	welcomeUI.run();
	return 0;
}