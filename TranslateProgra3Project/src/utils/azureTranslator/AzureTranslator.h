#pragma once

#include <string>
#include "../../enums/SupportedLanguages.h"

class AzureTranslator {
public:
    AzureTranslator();

    std::string translate(const std::string& text, SupportedLanguages targetLang);

private:
    std::string subscriptionKey;
    std::string endpoint;
    std::string region;

    std::string buildRequestBody(const std::string& text);
    std::string buildTargetLanguageCode(SupportedLanguages lang);
    std::string sendRequest(const std::string& url, const std::string& body, const std::string& langCode);
};
