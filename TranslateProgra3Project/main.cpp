#include <windows.h>
#include <iostream>
#include "./src/utils/azureSpeechPlayer/AzureSpeechPlayer.h"
#include "./src/ui/deprecatedMainMenu/DeprecatedMainMenu.h"

using namespace std;

int main()
{
	AzureSpeechPlayer player;

	player.speakText("Hola, ¿cómo estás?");
	player.speakText("Hello, how are you?");

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	DeprecatedMainMenu menu;
	menu.run();
	return 0;
}