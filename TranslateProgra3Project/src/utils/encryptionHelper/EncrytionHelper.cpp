#include "EncrytionHelper.h"
#include <map>
#include <string> 
#include <iostream>


using namespace std; 


string EncrytionHelper::encrypter(string text)
{

    std::string resultado = "";


    for (char letra : text) {
        if (keyWords.count(letra)) {
            resultado += keyWords.at(letra);
        }
        else {
            resultado += letra;
        }
    }

    std::cout << resultado << std::endl;

    return resultado;
   
}


std::string EncrytionHelper::decrypter(std::string codeText)
{
    std::string resultado = "";
    for (size_t i = 0; i < codeText.length(); ) {
        if (codeText[i] == 'm' || codeText[i] == 'U') {
            std::string clave(1, codeText[i]); 
            ++i;
            
            while (i < codeText.length() && isdigit(codeText[i])) {
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
            resultado += codeText[i]; 
            ++i;
        }
    }

    std::cout << resultado << std::endl;
    return resultado;
}
