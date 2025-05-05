#pragma once
#include <iostream>
#include <string>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4996) // Silencia 'GetVersionExW' deprecated

#include <sapi.h>
#include <sphelper.h>

#pragma warning(pop)
#endif

class AUDIOPlayer
{
private:
	void winSpeak(std::string& text, int& languageOption);
	void macSpeak(std::string& text);

public:
	AUDIOPlayer();
	void speak(std::string& text, int& languageOption);
};