#pragma once
#include <string>
#include "../../maps/keyMaps.h"

class EncrytionHelper {

private:
	int utf8_num_bytes(unsigned char c) const;
public: 
	std::string encrypter(const std::string& text);
	std::string decrypter(const std::string& codeText);
};
