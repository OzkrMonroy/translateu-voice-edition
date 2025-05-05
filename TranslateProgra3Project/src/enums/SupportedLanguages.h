#pragma once
#include <string>

enum class SupportedLanguages {
	Spanish,
	English,
	French,
	Italian,
	German
};

std::string getLanguageCode(SupportedLanguages lang);
std::string getDefaultVoice(SupportedLanguages lang);