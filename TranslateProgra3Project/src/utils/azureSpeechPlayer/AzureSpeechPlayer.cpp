#include "AzureSpeechPlayer.h"

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

AzureSpeechPlayer::AzureSpeechPlayer() {
    std::string key = EnvLoader::get("SPEECH_KEY");
    std::string region = EnvLoader::get("SPEECH_REGION");

    if (key.empty() || region.empty()) {
        throw std::runtime_error("SPEECH_KEY or SPEECH_REGION not found in .env file.");
    }

    speechConfig = SpeechConfig::FromSubscription(key, region);
    speechConfig->SetSpeechSynthesisVoiceName("es-ES-AlvaroNeural");
}

void AzureSpeechPlayer::speakFromConsoleInput() {
    std::cout << "Enter some text that you want to speak >" << std::endl;
    std::string text;
    std::getline(std::cin, text);

    speakText(text, SupportedLanguages::English);
}

void AzureSpeechPlayer::speakText(const std::string& text, SupportedLanguages lang) {
    auto synthesizer = SpeechSynthesizer::FromConfig(speechConfig);
    
    std::string language = getLanguageCode(lang);
    std::string voiceByLanguage = getDefaultVoice(lang);

    std::string ssml = SSMLBuilder::buildSSML(language, voiceByLanguage, text);
    auto result = synthesizer->SpeakSsmlAsync(ssml).get();

    if (result->Reason == ResultReason::SynthesizingAudioCompleted) {
        std::cout << "Speech synthesized to speaker for text [" << text << "]" << std::endl;
    }
    else if (result->Reason == ResultReason::Canceled) {
        auto cancellation = SpeechSynthesisCancellationDetails::FromResult(result);
        std::cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error) {
            std::cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            std::cout << "CANCELED: ErrorDetails=[" << cancellation->ErrorDetails << "]" << std::endl;
        }
    }
}

std::string AzureSpeechPlayer::getEnvVar(const char* name) {
#if defined(_MSC_VER)
    size_t requiredSize = 0;
    getenv_s(&requiredSize, nullptr, 0, name);
    if (requiredSize == 0)
        return "";
    auto buffer = std::make_unique<char[]>(requiredSize);
    getenv_s(&requiredSize, buffer.get(), requiredSize, name);
    return buffer.get();
#else
    auto value = getenv(name);
    return value ? value : "";
#endif
}
