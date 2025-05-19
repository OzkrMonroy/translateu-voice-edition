#include "AuthenticationUI.h"
#include "../../welcomeUI/WelcomeUI.h"
#include "../userOptions/UserOptionsUI.h"
using namespace std;

AuthenticationUI::AuthenticationUI(){}

void AuthenticationUI::run() {
	WelcomeUI welcomeUI;
	int choise;
	bool displayScreen = true;

	while (displayScreen) {
		consoleUtils.clear();
		consoleUtils.printTitle("Ingreso al sistema");
		consoleUtils.writeLine("Seleccione el número de la opcion que desea realizar:");
		consoleUtils.writeLine("1. Iniciar sesión");
		consoleUtils.writeLine("2. Registrarse");
		consoleUtils.writeLine("3. Regresar al menu principal");

		cin >> choise;
		cin.ignore();

		switch (choise)
		{
		case 1:
			login(displayScreen);
			break;
		case 2:
			registerUser(displayScreen);
			break;
		case 3: 
			welcomeUI.run();
			displayScreen = false;
			break;
		default:
			break;
		}
	}
}

void AuthenticationUI::login(bool &displayScreen){
	string userName;
	string password;

	consoleUtils.clear();
	consoleUtils.printTitle("Inicio de sesión");
	consoleUtils.write("Ingrese su nombre de usuario:");
	getline(cin, userName);
	consoleUtils.write("Ingrese su contraseña:");
	getline(cin, password);

	consoleUtils.writeLine("Nombre de usuario: " + userName);
	consoleUtils.writeLine("Contraseña: " + password);
	consoleUtils.writeLine("Iniciando sesion...");
	consoleUtils.wait(3000);
	UserOptionsUI userUI;
	userUI.run();
	displayScreen = false;
}
void AuthenticationUI::registerUser(bool &displayScreen) {
	string userName, name, password, confirmPassword;
	consoleUtils.clear();
	consoleUtils.printTitle("Registro de usuario");
	consoleUtils.write("Ingrese su nombre: ");
	getline(cin, name);
	consoleUtils.write("Ingrese su nombre de usuario: ");
	getline(cin, userName);
	consoleUtils.write("Ingrese su contraseña: ");
	getline(cin, password);
	consoleUtils.write("Confirme su contraseña: ");
	getline(cin, confirmPassword);

	consoleUtils.writeLine("Nombre: " + name);
	consoleUtils.writeLine("Nombre de usuario: " + userName);
	consoleUtils.writeLine("Contraseña: " + password);
	consoleUtils.writeLine("Iniciando sesion...");
	consoleUtils.wait(3000);
	UserOptionsUI userUI;
	userUI.run();
	displayScreen = false;
}