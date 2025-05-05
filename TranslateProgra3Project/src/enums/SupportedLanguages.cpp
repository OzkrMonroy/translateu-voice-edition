#include "SupportedLanguages.h"

std::string getLanguageCode(SupportedLanguages lang) {
	switch (lang)
	{
	case SupportedLanguages::Spanish:
		return "es-ES";
	case SupportedLanguages::English:
		return "en-US";
	case SupportedLanguages::French:
		return "fr-FR";
	case SupportedLanguages::Italian:
		return "it-IT";
	case SupportedLanguages::German:
		return "de-DE";
	default:
		return "en-US";
	}
}

std::string getDefaultVoice(SupportedLanguages lang) {
	switch (lang) {
	case SupportedLanguages::Spanish: return "es-ES-AlvaroNeural";
	case SupportedLanguages::English: return "en-US-JennyNeural";
	case SupportedLanguages::French:  return "fr-FR-DeniseNeural";
	case SupportedLanguages::Italian: return "it-IT-DiegoNeural";
	case SupportedLanguages::German:  return "de-DE-ConradNeural";
	default: return "en-US-JennyNeural";
	}
}