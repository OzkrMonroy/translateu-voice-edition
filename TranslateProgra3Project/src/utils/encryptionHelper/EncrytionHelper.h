#pragma once
#include <string>
#include "../../maps/keyMaps.h"

class EncrytionHelper {

public: 
	std::string encrypter(std:: string text);
	std::string decrypter(std::string codetext);
};
