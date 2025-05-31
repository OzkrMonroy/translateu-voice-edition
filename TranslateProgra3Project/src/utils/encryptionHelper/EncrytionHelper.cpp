#include "EncrytionHelper.h"
#include <map>
#include <string> 
#include <iostream>


using namespace std; 
int EncrytionHelper::utf8_num_bytes(unsigned char c) const {
    if ((c & 0x80) == 0x00) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

std::string EncrytionHelper::encrypter(const std::string& text)
{
    std::string resultado;
    resultado.reserve(text.size());

    size_t i = 0;
    while (i < text.length()) {
        unsigned char c = static_cast<unsigned char>(text[i]);
        if (c < 128) {
            if (keyWords.count(c)) {
                resultado += keyWords.at(c);
            }
            else {
                resultado += text[i];
            }
            i++;
        }
        else {
            int n = utf8_num_bytes(c);
            for (int j = 0; j < n && i + j < text.length(); ++j) {
                resultado += text[i + j];
            }
            i += n;
        }
    }
    return resultado;
}

std::string EncrytionHelper::decrypter(const std::string& codeText)
{
    std::string resultado;
    resultado.reserve(codeText.size());

    size_t i = 0;
    while (i < codeText.length()) {
        unsigned char c = static_cast<unsigned char>(codeText[i]);

        if (codeText[i] == 'm' || codeText[i] == 'U' || codeText[i] == 'g') {
            std::string clave;
            clave += codeText[i];
            ++i;

            while (i < codeText.length() &&
                isdigit(static_cast<unsigned char>(codeText[i])))
            {
                clave += codeText[i];
                ++i;
            }

            if (reverseKeyWords.count(clave)) {
                resultado += reverseKeyWords.at(clave);
            }
            else {
                resultado += clave;
            }
        }
        else {
            if (c < 128) {
                resultado += codeText[i];
                ++i;
            }
            else {
                int n = utf8_num_bytes(c);
                for (int j = 0; j < n && (i + j) < codeText.length(); ++j) {
                    resultado += codeText[i + j];
                }
                i += n;
            }
        }
    }

    return resultado;
}

