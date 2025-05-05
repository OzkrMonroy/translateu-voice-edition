#pragma once
#include <string>

class TextSanitizer {
public:
    static std::string sanitizeToUtf8(const std::string& input);
};
