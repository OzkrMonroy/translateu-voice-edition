#pragma once
#include <string>
#include <speechapi_cxx.h>
#include <iostream>
#include <memory>
#include <cstdlib> 
#include <stdexcept>
#include "../envLoader/EnvLoader.h"
#include "../ssmlBuilder/SSMLBuilder.h"
#include "../../enums/SupportedLanguages.h"

class AzureSpeechPlayer {
public:
    AzureSpeechPlayer();
    void speakFromConsoleInput();
    void speakText(const std::string& text, SupportedLanguages lang);

private:
    std::string getEnvVar(const char* name);
    std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig> speechConfig;
};
