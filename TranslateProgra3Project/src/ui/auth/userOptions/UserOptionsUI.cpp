#include "UserOptionsUI.h"
#include "../../welcomeUI/WelcomeUI.h"
#include "../../translateUI/TranslateUI.h"
using namespace std;

UserOptionsUI::UserOptionsUI()
{
	manager.loadWordsFromJSONFile();
	authController = AuthController::getInstance();
}

void UserOptionsUI::run()
{
	WelcomeUI welcome;
	TranslateUI translateUI;
	currentUser = authController->getCurrentUser();
	string name = "";
	if (currentUser.has_value()) {
		name = currentUser.value().name;
	}

	int choise;
	bool displayScreen = true;

	while (displayScreen) {
		consoleUtils.clear();
		consoleUtils.printTitle("Bienvenido " + name);
		consoleUtils.writeLine("Seleccione el número de la opcion que desea realizar:");
		consoleUtils.writeLine("1. Traducir");
		consoleUtils.writeLine("2. Ver historial de traducciones");
		consoleUtils.writeLine("3. Top de palabras más buscadas");
		consoleUtils.writeLine("4. Cerrar sesion");

		cin >> choise;
		cin.ignore();

		switch (choise)
		{
		case 1:
			translateUI.run();
			displayScreen = false;
			break;
		case 2:
			translateHistory();
			break;
		case 3:
			topMostSearchedWords();
			break;
		case 4:
			authController->logout();
			consoleUtils.writeLine("Cerrando sesion...");
			consoleUtils.wait(2000);
			welcome.run();
			displayScreen = false;
			break;
		default:
			cout << "Opción no válida. Intente de nuevo.\n";
			break;
		}
	}
}

void UserOptionsUI::translateHistory()
{
	cout << "-- Historial de traducciones --\n";
}

void UserOptionsUI::topMostSearchedWords()
{
	cout << "-- Top de palabras más buscadas --\n";
}




