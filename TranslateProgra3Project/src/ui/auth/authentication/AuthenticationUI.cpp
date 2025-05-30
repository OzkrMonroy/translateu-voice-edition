#include "AuthenticationUI.h"
#include "../../welcomeUI/WelcomeUI.h"
#include "../userOptions/UserOptionsUI.h"


using namespace std;


AuthenticationUI::AuthenticationUI() {
	controller = AuthController::getInstance(); 
}

void AuthenticationUI::run() {
	WelcomeUI welcomeUI;
	int choise;
	bool displayScreen = true;

	while (displayScreen) {
		consoleUtils.clear();
		consoleUtils.printTitle("Ingreso al sistema");
		consoleUtils.writeLine("Seleccione el n�mero de la opcion que desea realizar:");
		consoleUtils.writeLine("1. Iniciar sesi�n");
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
	consoleUtils.printTitle("Inicio de sesi�n");
	consoleUtils.write("Ingrese su nombre de usuario:");
	getline(cin, userName);
	consoleUtils.write("Ingrese su contrase�a:");
	getline(cin, password);

	if (controller->login(userName, password)) {
		consoleUtils.writeLine("Nombre de usuario: " + userName);
		consoleUtils.writeLine("Contrase�a: " + password);
		consoleUtils.writeLine("Iniciando sesion...");
		consoleUtils.wait(1000);
		UserOptionsUI userUI;
		userUI.run();
		displayScreen = false;
	}
	else {
		consoleUtils.writeLine("Credenciales incorrectas");
		consoleUtils.wait(1000);
	}


}
void AuthenticationUI::registerUser(bool& displayScreen) {
	string userName, name, password, confirmPassword;
	consoleUtils.clear();
	consoleUtils.printTitle("Registro de usuario");
	consoleUtils.write("Ingrese su nombre: ");
	getline(cin, name);
	consoleUtils.write("Ingrese su nombre de usuario: ");
	getline(cin, userName);
	consoleUtils.write("Ingrese su contrase�a: ");
	getline(cin, password);
	consoleUtils.write("Confirme su contrase�a: ");
	getline(cin, confirmPassword);

	if (password != confirmPassword) {
		consoleUtils.writeLine("Las contrase�as no coinciden.");
		consoleUtils.wait(1000);
		return;
	}
	string userFile = encryptionHelper.encrypter(userName);
	NewUser newUser{ name, userName, password, userFile };
	
	if (controller->registeredUser(newUser)) {
		controller->login(newUser.username, newUser.password);
		consoleUtils.writeLine("Iniciando sesion...");
		consoleUtils.wait(1000);
		UserOptionsUI userUI;
		userUI.run();
		displayScreen = false;
	}
	else {
		consoleUtils.writeLine("Error: El usuario ya existe");
		consoleUtils.wait(1000);
	}
}