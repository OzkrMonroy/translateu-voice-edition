#include <windows.h>
#include <iostream>
#include "./src/ui/deprecatedMainMenu/DeprecatedMainMenu.h"
#include "./src/models/user/UserModel.h"
#include "./src/models/structs/NewUser.h"
#include "./src/models/structs/User.h"


using namespace std;

int main()
{
    UserModel userModel;
    if (!userModel.createTable()) {
        std::cerr << "No se pudo crear la tabla de usuarios." << std::endl;
        return 1;
    }
    NewUser newUser{ "Oscar Monroy", "oscar123", "miclave123" };

    if (userModel.addUser(newUser)) {
        std::cout << "Usuario agregado exitosamente." << std::endl;
    }
    else {
        std::cerr << "Error al agregar el usuario (posiblemente ya existe)." << std::endl;
    }

    auto result = userModel.getUser("oscar123", "miclave123");

    if (result) {
        std::cout << "Usuario encontrado:" << std::endl;
        std::cout << "ID: " << result->id << std::endl;
        std::cout << "Nombre: " << result->name << std::endl;
        std::cout << "Username: " << result->username << std::endl;
    }
    else {
        std::cout << "Usuario no encontrado." << std::endl;
    }


	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	DeprecatedMainMenu menu;
	menu.run();
	return 0;
}