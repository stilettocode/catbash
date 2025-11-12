#include <iostream>         // std::cout, std::cin
#include <string>           // std::string
#include <vector>           // std::vector in parse_input
#include <unordered_map>    // For cmd_table
#include <functional>       // For std::function type
#include <sstream>          // For std::istringstream
#include <filesystem>       // For any filesystem ops
#include <fstream>          // For std::ifstream
#include <cstdlib>          // For system()
#include <Windows.h>        // For HANDLE etc

#include "catcommands.h"
#include "greetings.h"

auto parse_input(const std::string& input) -> std::pair<std::string, std::vector<std::string>> {
    std::istringstream iss(input);
    std::string cmd; iss >> cmd;
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) args.push_back(arg);
    return { cmd, args };
}
int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    int savedInt = 0;
    std::string savedString;
    std::string lastRunDate;

	auto cmd_table = make_cmd_table(savedInt, savedString, lastRunDate);

    // load
    std::ifstream ifs("state.txt");
    if (ifs.is_open()) {
        ifs >> savedInt;
        ifs.ignore();
        std::getline(ifs, savedString);
        std::getline(ifs, lastRunDate);
        ifs.close();
    }
    else {
        // file doesn't exist yet initialize default values
        savedInt = 0;
        savedString = "";
        lastRunDate = "";
    }

	greeting(savedInt, savedString);

    std::string input;
    while (true) {
        std::cout << "\033[31mcat~meow$ \033[0m";
        std::getline(std::cin, input);
        if (input == "exit") break;
        auto [cmd, args] = parse_input(input);

        if (cmd == "cat") {
            cmd = "git";
        }

        if (cmd_table.count(cmd)) {
            cmd_table[cmd](args);
        }
        else {
            std::string system_command = cmd;
            for (const auto& arg : args) system_command += " " + arg;
            system(system_command.c_str());
        }
    }
}
