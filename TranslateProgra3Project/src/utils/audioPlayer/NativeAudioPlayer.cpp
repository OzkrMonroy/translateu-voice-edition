#include "NativeAudioPlayer.h"
using namespace std;
#ifdef _WIN32

enum Lenguage : int {
    ES = 0x0C0A,
    EN = 0x0409,
    FR = 0x040C,
    IT = 0x0410,
    DE = 0x0407
};

wstring constructLangTag(int languageCode) {
    wstringstream ss;
    ss << L"Language=";
    ss << hex << uppercase << languageCode;
    return ss.str();
}
#endif

AUDIOPlayer::AUDIOPlayer()
{

}

void AUDIOPlayer::speak(std::string& text, int& languageOption)
{
#ifdef _WIN32
    winSpeak(text, languageOption);

#elif _APPLE_
    macSpeak(text);
#endif
}

void AUDIOPlayer::winSpeak(std::string& text, int& languageOption)
{
    Lenguage languageSelect;

    switch (languageOption) {
    case 1: languageSelect = ES; break;
    case 2: languageSelect = EN; break;
    case 3: languageSelect = FR; break;
    case 4: languageSelect = IT; break;
    case 5: languageSelect = DE; break;
    default:
        cout << "Opción inválida." << endl;
        return;
    }

    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr)) {
        ISpVoice* pVoice = NULL;
        hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
        if (SUCCEEDED(hr)) {
            wstring wtext(text.begin(), text.end());

            wstring langTagW = constructLangTag(languageSelect);
            const WCHAR* langTag = langTagW.c_str();

            IEnumSpObjectTokens* pEnum = NULL;
            ULONG count = 0;
            ISpObjectToken* cpToken = NULL;

            hr = SpEnumTokens(SPCAT_VOICES, langTag, NULL, &pEnum);
            if (SUCCEEDED(hr) && pEnum != NULL) {
                hr = pEnum->Next(1, &cpToken, &count);
                if (SUCCEEDED(hr) && count > 0 && cpToken != NULL) {
                    pVoice->SetVoice(cpToken);
                    cpToken->Release();
                }
                else {
                    cout << "No se encontró una voz para ese idioma." << endl;
                }
                pEnum->Release();
            }

            pVoice->Speak(wtext.c_str(), SPF_IS_XML, NULL);
            pVoice->Release();
        }
        CoUninitialize();
    }

}

void AUDIOPlayer::macSpeak(std::string& text)
{
    string command = "say \"" + text + "\"";
    system(command.c_str());
}





