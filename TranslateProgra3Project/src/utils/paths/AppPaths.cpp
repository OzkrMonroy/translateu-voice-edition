#include "AppPaths.h"
#include <Windows.h>

std::filesystem::path AppPaths::getExecutableDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    return std::filesystem::path(buffer).parent_path();
}

std::filesystem::path AppPaths::getDataDir() {
    auto path = getExecutableDir() / "data";
    std::filesystem::create_directories(path);
    return path;
}

std::filesystem::path AppPaths::getAudiosDir() {
    auto path = getExecutableDir() / "audios";
    std::filesystem::create_directories(path);
    return path;
}

std::filesystem::path AppPaths::getTranslationsDir() {
    auto path = getExecutableDir() / "translations";
    std::filesystem::create_directories(path);
    return path;
}
