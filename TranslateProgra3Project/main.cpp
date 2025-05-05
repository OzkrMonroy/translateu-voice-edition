#include <windows.h>
#include <iostream>
#include "./src/utils/azureSpeechPlayer/AzureSpeechPlayer.h"
#include "./src/ui/deprecatedMainMenu/DeprecatedMainMenu.h"
#include "./src/enums/SupportedLanguages.h"

using namespace std;

int main()
{
    try {
        AzureSpeechPlayer player;
        player.speakText("Hola mundo, ¡este es un ejemplo! ¿Detecta esto si estoy haciendo una pregunta?", SupportedLanguages::Spanish);
        player.speakText("Hello World! This is an example. Can this speak with entonation?", SupportedLanguages::English);
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