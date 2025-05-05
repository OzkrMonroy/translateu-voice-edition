#include "AzureTranslator.h"
#include <curl/curl.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../envLoader/EnvLoader.h"

using json = nlohmann::json;

AzureTranslator::AzureTranslator() {
    subscriptionKey = EnvLoader::get("TRANSLATOR_KEY");
    endpoint = EnvLoader::get("TRANSLATOR_ENDPOINT");
    region = EnvLoader::get("TRANSLATOR_REGION");

    if (subscriptionKey.empty() || endpoint.empty() || region.empty()) {
        throw std::runtime_error("Azure Translator API key, endpoint, or region missing in .env file.");
    }
}

std::string AzureTranslator::translate(const std::string& text, SupportedLanguages targetLang) {
    std::string route = "translate?api-version=3.0&to=" + buildTargetLanguageCode(targetLang);
    std::string url = endpoint + route;
    std::string body = buildRequestBody(text);
    return sendRequest(url, body, buildTargetLanguageCode(targetLang));
}

std::string AzureTranslator::buildRequestBody(const std::string& text) {
    json body = json::array({ {{"Text", text}} });
    return body.dump();
}

std::string AzureTranslator::buildTargetLanguageCode(SupportedLanguages lang) {
    // Reutiliza tu función getLanguageCode(lang)
    return getLanguageCode(lang);
}

// Callback para capturar la respuesta de curl
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string AzureTranslator::sendRequest(const std::string& url, const std::string& body, const std::string& langCode) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Ocp-Apim-Subscription-Key: " + subscriptionKey).c_str());
        headers = curl_slist_append(headers, ("Ocp-Apim-Subscription-Region: " + region).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    try {
        auto parsed = json::parse(response);
        return parsed[0]["translations"][0]["text"];
    }
    catch (...) {
        std::cerr << "Error parsing translation response." << std::endl;
        return "";
    }
}
