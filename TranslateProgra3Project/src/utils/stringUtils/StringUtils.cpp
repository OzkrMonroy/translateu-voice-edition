#include "StringUtils.h"
#include <algorithm>
#include <cctype>

std::string StringUtils::toLowerCase(const std::string& input) {
    std::string lowered = input;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) {
        return std::tolower(c);
        });
    return lowered;
}
