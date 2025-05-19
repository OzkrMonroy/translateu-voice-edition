#include "UserOptionsUI.h"
#include "../../welcomeUI/WelcomeUI.h"
using namespace std;

UserOptionsUI::UserOptionsUI()
{
	manager.loadWordsFromJSONFile();
}

void UserOptionsUI::run()
{
	WelcomeUI welcome;
	string name = "Test";
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
			translatorScreen();
			break;
		case 2:
			translateHistory();
			break;
		case 3:
			topMostSearchedWords();
			break;
		case 4:
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

void UserOptionsUI::translatorScreen()
{
	string text;
	int languageOption;

	cout << "Ingrese texto a traducir\n";
	getline(cin, text);

	cout << "Ingrese idioma al que quiere traducir\n";
	cin >> languageOption;

}

void UserOptionsUI::translateHistory()
{
	cout << "-- Historial de traducciones --\n";
}

void UserOptionsUI::topMostSearchedWords()
{
	cout << "-- Top de palabras más buscadas --\n";
}




