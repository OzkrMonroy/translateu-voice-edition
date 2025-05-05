#include <windows.h>
#include <iostream>
#include "./src/utils/azureSpeechPlayer/AzureSpeechPlayer.h"
#include "./src/ui/deprecatedMainMenu/DeprecatedMainMenu.h"

using namespace std;

int main()
{
    try {
        AzureSpeechPlayer player;
        player.speakText("Hola mundo, ¡este es un ejemplo!");
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	DeprecatedMainMenu menu;
	menu.run();
	return 0;
}