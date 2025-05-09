#pragma once
#include <string>
#include <filesystem>

class AppPaths {
public:
    static std::filesystem::path getExecutableDir();
    static std::filesystem::path getDataDir();
    static std::filesystem::path getAudiosDir();
    static std::filesystem::path getTranslationsDir();
};
