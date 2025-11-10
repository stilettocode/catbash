#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>

auto parse_input(const std::string& input) -> std::pair<std::string, std::vector<std::string>> {
    std::istringstream iss(input);
    std::string cmd; iss >> cmd;
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) args.push_back(arg);
    return { cmd, args };
}

int main() {
    int savedInt = 0;
    std::string savedString;

    // load
    std::ifstream ifs("state.txt");
    if (ifs.is_open()) {
        ifs >> savedInt;
        ifs.ignore();
        std::getline(ifs, savedString);
        ifs.close();
    }
    else {
        // file doesn't exist yet; initialize default values
        savedInt = 0;
        savedString = "";
    }

    std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> cmd_table = {
        {"meow", [](auto args) { std::cout << "Meow!" << std::endl; }},
        {"ls", [](auto args) { system("dir"); }},
        {"catbash", [&savedString, &savedInt](const std::vector<std::string>& args) {
            if (args.empty()) {
                std::cout << "catbash: no action specified\n";
                return;
            }
            if (args[0] == "feed") {
                ++savedInt;
                std::cout << "You've fed " << savedString << " " << savedInt << " times so far.\n";
                std::ofstream ofs("state.txt");
                ofs << savedInt << "\n" << savedString << "\n";
                ofs.close();
            }
            else if (args[0] == "adopt") {
                savedInt = 0;
                if (args.size() < 2) {
                    std::cout << "catbash: no name specified for adoption\n";
                    return;
                }
                else {
                    savedInt = 0;
                    savedString = args[1];
                    std::cout << "You've adopted a cat named " << savedString << "!\n";
                    std::ofstream ofs("state.txt");
                    ofs << savedInt << "\n" << savedString << "\n";
					ofs.close();
                }
            }
            else {
                std::cout << "catbash: unknown subcommand '" << args[0] << "'\n";
            }
            }},
     };

    std::cout <<
        "      _\n"
        "       l`*-.\n"
        "        )  _`-.\n"
        "       .  : `. .\n"
        "       : _   '  l\n"
        "       ; *` _.   `*-._\n"
        "       `-.-'          `-.\n"
        "         ;       `       `.\n"
        "         :.       .        l\n"
        "         . l  .   :   .-'   .\n"
        "         '  `+.;  ;  '      :\n"
        "         :  '  |    ;       ;-.\n"
        "         ; '   : :`-:     _.`* ;\n"
        "cat    .*' /  .*' ; .*`- +'  `*'\n"
        "bash   `*-*   `*-*  `*-*'\n\n"
		"git commands work with git replaced with cat. make sure you have git installed.\n"
		"catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
		"catbash feed to feed your cat.\n"
		"feed your cat every day to watch it grow!\n\n";

    std::string input;
    while (true) {
        std::cout << "cat~meow$ ";
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
