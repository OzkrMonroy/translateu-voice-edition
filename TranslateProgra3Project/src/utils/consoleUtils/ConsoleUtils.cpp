#include "ConsoleUtils.h"
#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <limits>

void ConsoleUtils::clear() {
    system("cls");
}

void ConsoleUtils::pause() {
    system("pause");
}

void ConsoleUtils::printTitle(const std::string& title) {
    ConsoleUtils::clear();
    std::cout << "==== " << title << " ====" << std::endl << std::endl;
}

void ConsoleUtils::writeLine(const std::string& text) {
    std::cout << text << std::endl << std::endl;
}

void ConsoleUtils::write(const std::string& text) {
    std::cout << text;
}

void ConsoleUtils::wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void ConsoleUtils::waitForEnter() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.get();
}
