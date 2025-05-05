#pragma once
#include <string>
#include <speechapi_cxx.h>
#include <iostream>
#include <memory>
#include <cstdlib> 
#include <stdexcept>
#include "../envLoader/EnvLoader.h"

class AzureSpeechPlayer {
public:
    AzureSpeechPlayer();
    void speakFromConsoleInput(); // Usa entrada desde consola para hablar
    void speakText(const std::string& text); // Habla el texto directamente

private:
    std::string getEnvVar(const char* name);
    std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig> speechConfig;
};
