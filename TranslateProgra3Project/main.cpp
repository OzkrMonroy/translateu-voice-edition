#include <windows.h>
#include <iostream>
#include "./src/ui/deprecatedMainMenu/DeprecatedMainMenu.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	DeprecatedMainMenu menu;
	menu.run();
	return 0;
}