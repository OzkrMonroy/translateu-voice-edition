#include "ConsoleUtils.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>

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
    std::cout << text << "\n" << std::endl;
}

void ConsoleUtils::write(const std::string& text) {
    std::cout << text;
}

void ConsoleUtils::wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void ConsoleUtils::waitForEnter() {
    std::cout << "\nPresiona Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}
