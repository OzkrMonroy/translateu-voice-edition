#pragma once

#include <string>
#include <unordered_map>

class EnvLoader {
public:
    static std::unordered_map<std::string, std::string> loadEnvFile();
    static std::unordered_map<std::string, std::string> loadEnvFile(const std::string& path);

    static std::string get(const std::string& key);

private:
    static std::unordered_map<std::string, std::string> variables;
    static bool loaded;

    static std::string getExecutableDir(); // ?? agregado
};
