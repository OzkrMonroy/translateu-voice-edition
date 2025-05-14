#include <windows.h>
#include <iostream>
#include "./src/utils/azureSpeechPlayer/AzureSpeechPlayer.h"
#include "./src/utils/azureTranslator/AzureTranslator.h"
#include "./src/maps/keyMaps.h"
#include "./src/utils/textSanatizer/TextSanitizer.h"
#include "./src/ui/deprecatedMainMenu/DeprecatedMainMenu.h"
#include "./src/enums/SupportedLanguages.h"
#include "./src/utils/encryptionHelper/EncrytionHelper.h"



using namespace std;

int main()
{
   /* try {
        AzureTranslator translator;
        AzureSpeechPlayer player;
        std::string baseText = "Hola mundo ¡este es un ejemplo! ¿Detecta esto si estoy haciendo una pregunta?";
        std::string safeText = TextSanitizer::sanitizeToUtf8(baseText);
        std::string translatedText = translator.translate(safeText, SupportedLanguages::English);

        player.speakText(baseText, SupportedLanguages::Spanish);
        player.speakText(translatedText, SupportedLanguages::English);

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
    }*/
   
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	DeprecatedMainMenu menu;
	menu.run();
	return 0;
}