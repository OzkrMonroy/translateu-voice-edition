#include "WelcomeUI.h"
#include "../auth/authentication/AuthenticationUI.h"
#include "../translateUI/TranslateUI.h"
using namespace std;

WelcomeUI::WelcomeUI()
{
}

void WelcomeUI::run()
{
	AuthenticationUI authUI;
	TranslateUI translateUI;
	int choise;
	bool displayScreen = true;

	while (displayScreen) {
		consoleUtils.clear();
		consoleUtils.printTitle("Bienvenido");
		consoleUtils.writeLine("Seleccione el número de la opcion que desea realizar:");
		consoleUtils.writeLine("1. Ingresar");
		consoleUtils.writeLine("2. Traducir");
		consoleUtils.writeLine("3. Salir");

		cin >> choise;
		cin.ignore();

		switch (choise) {
		case 1:
			authUI.run();
			displayScreen = false;
			break;
		case 2:
			translateUI.run();
			displayScreen = false;
			break;
		case 3:
			consoleUtils.writeLine("Saliendo del programa...");
			consoleUtils.wait(1500);
			exit(0);
			break;
		}
	}
}


