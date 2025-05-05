#include "UserOptionsUI.h"
using namespace std;

UserOptionsUI::UserOptionsUI()
{
	manager.loadWordsFromJSONFile();
}

void UserOptionsUI::run()
{
	while (true) {
		displayMenu();
		handleUserChoise();
	}
}


void UserOptionsUI::displayMenu() const
{
	cout << "\n--- Opciones de Usuario ---\n";
	cout << "1. Traducir\n";
	cout << "2. Ver historial de traducciones\n";
	cout << "3. Top de palabras más buscadas\n";
	cout << "4. Salir\n";
	cout << "Seleccione una opción: ";
}

void UserOptionsUI::handleUserChoise()
{
	int choise;
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
		cout << "Saliendo del programa...\n";
		exit(0);
	default:
		cout << "Opción no válida. Intente de nuevo.\n";
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




