#pragma once

#include <string>

class SSMLBuilder {
public:
    static std::string escapeTextForSSML(const std::string& input);
    static std::string buildSSML(const std::string& languageCode, const std::string& voiceName, const std::string& text);
};
