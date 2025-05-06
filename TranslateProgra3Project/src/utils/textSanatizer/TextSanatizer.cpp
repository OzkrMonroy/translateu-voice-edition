#include "TextSanitizer.h"
#include <Windows.h>

std::string TextSanitizer::sanitizeToUtf8(const std::string& input) {
    // Convert input (local codepage) to UTF-16
    int wideSize = MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, nullptr, 0);
    if (wideSize == 0) return "";

    std::wstring wide(wideSize, 0);
    MultiByteToWideChar(CP_ACP, 0, input.c_str(), -1, &wide[0], wideSize);

    // Convert UTF-16 to UTF-8
    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Size == 0) return "";

    std::string utf8(utf8Size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, &utf8[0], utf8Size, nullptr, nullptr);

    return utf8;
}
