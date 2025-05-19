#pragma once
#pragma once
#include <string>

class ConsoleUtils {
public:
    static void clear();
    static void pause();
    static void printTitle(const std::string& title);
    static void writeLine(const std::string& text);
    static void write(const std::string& text);
    static void wait(int milliseconds);
    static void waitForEnter();
};
