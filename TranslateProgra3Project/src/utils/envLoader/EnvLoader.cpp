#include "EnvLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, std::string> EnvLoader::variables;
bool EnvLoader::loaded = false;

std::unordered_map<std::string, std::string> EnvLoader::loadEnvFile(const std::string& path) {
    if (loaded) return variables;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open .env file: " << path << std::endl;
        return variables;
    }

    std::string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) continue;

        std::string key = line.substr(0, equalPos);
        std::string value = line.substr(equalPos + 1);

        // Elimina espacios en blanco si los hay
        key.erase(0, key.find_first_not_of(" \t\r\n"));
        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        variables[key] = value;
    }

    loaded = true;
    return variables;
}

std::string EnvLoader::get(const std::string& key) {
    if (!loaded) loadEnvFile();
    return variables.count(key) ? variables[key] : "";
}
