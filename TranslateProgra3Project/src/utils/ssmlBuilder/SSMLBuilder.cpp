#include "SSMLBuilder.h"
#include <sstream>

std::string SSMLBuilder::escapeTextForSSML(const std::string& input) {
    std::ostringstream escaped;

    for (char c : input) {
        switch (c) {
        case '&': escaped << "&amp;"; break;
        case '<': escaped << "&lt;"; break;
        case '>': escaped << "&gt;"; break;
        case '\"': escaped << "&quot;"; break;
        case '\'': escaped << "&apos;"; break;
        case '¡': escaped << ""; break;
        case '¿': escaped << ""; break;
        default: escaped << c;
        }
    }

    return escaped.str();
}

std::string SSMLBuilder::buildSSML(const std::string& languageCode, const std::string& voiceName, const std::string& text) {
    std::ostringstream ssml;
    std::string safeText = escapeTextForSSML(text);

    ssml << "<speak version='1.0' xml:lang='" << languageCode << "'>";
    ssml << "<voice name='" << voiceName << "'>";
    ssml << safeText;
    ssml << "</voice></speak>";

    return ssml.str();
}
