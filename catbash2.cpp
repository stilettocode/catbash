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
#include <ctime>

auto parse_input(const std::string& input) -> std::pair<std::string, std::vector<std::string>> {
    std::istringstream iss(input);
    std::string cmd; iss >> cmd;
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) args.push_back(arg);
    return { cmd, args };
}

std::string getTodayDate() {
    time_t now = time(nullptr);
    tm ltm;
    localtime_s(&ltm, &now);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &ltm);
    return std::string(buf);
}

#include <iostream>
#include <fstream>
#include <cstdio>

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    int savedInt = 0;
    std::string savedString;
    std::string lastRunDate;

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
        // file doesn't exist yet; initialize default values
        savedInt = 0;
        savedString = "";
        lastRunDate = "";
    }

    std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> cmd_table = {
        {"yo", [](auto args) {
            if (args.empty()) {
                std::cout << "Usage: yo <your question>\n";
            return;
            }
            std::string question;
            std::string helper = "? Please answer in a concise sentence.";
            for (const auto& arg : args) question += arg + " ";

            std::string cmd = "llama-cli.exe -m catgemma.gguf -p \"" + question + helper + "\" -n 50 2>nul --no-conversation";

            FILE* pipe = _popen(cmd.c_str(), "r");
            if (!pipe) {
                std::cerr << "Failed to run llama-cli\n";
                return;
            }
            char buffer[256];
            std::cout << "\n\033[32mCATBOT:\033[0m\n";
            while (fgets(buffer, sizeof(buffer), pipe)) {
                std::string line = buffer;
                if (line.find(question) != std::string::npos || line.find("[end of text]") != std::string::npos || line.find("```") != std::string::npos) {
                    continue;
                }
                std::cout << buffer;
            }
            _pclose(pipe);
            std::cout << "\n";
        }},
        {"meow", [](auto args) { std::cout << "Meow!" << std::endl; }},
        {"ls", [](auto args) { system("dir"); }},
        {"cd", [](auto args) {
                if (args.empty()) {
                    std::cout << "cd: missing folder argument\n";
                    return;
                }
                try {
                    std::filesystem::current_path(args[0]);
                }
                catch (std::exception& e) {
                std::cout << "cd: " << e.what() << "\n";
                }
                std::string cwd = std::filesystem::current_path().string();
                SetConsoleTitleA(cwd.c_str());
            }
        },
        {"catbash", [&savedString, &savedInt, &lastRunDate](const std::vector<std::string>& args) {
            if (args.empty()) {
                std::cout << "catbash: no action specified\n";
                return;
            }
            if (args[0] == "feed") {
                std::string today = getTodayDate();
                if (lastRunDate == today) {
					std::cout << "You've already fed your cat today! Come back tomorrow.\n";
                }
                else {
					lastRunDate = today;
                    ++savedInt;
                    std::cout << "You've fed " << savedString << " " << savedInt << " times so far.\n";
                    std::ofstream ofs("state.txt");
                    ofs << savedInt << "\n" << savedString << "\n" << lastRunDate << "\n";
                    ofs.close();
                }
            }
            else if (args[0] == "adopt") {
                savedInt = 0;
				lastRunDate = "";
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

    if (savedInt == 0) {
        std::cout <<
            "\033[33m      _\n"
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
            "bash   `*-*   `*-*  `*-*'\033[0m\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 0 && savedInt < 4) {
        std::cout <<
            "\033[33m      |l     _,,,---,,_\n"
            "ZZZzz /,'.-'''    -.  ;-;;,_\n"
            "     |,4-  ) )-,_. ,l (  ''-'\n"
            "    '---''(_/--'  '-'l_)\033[0m\n\n";
        std::cout << "Your kitten " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 3 && savedInt < 11) {
        std::cout <<
            "\033[33m                ,\n"
            "              _/((\n"
            "     _.---. .'   '\\\n"
            "   .'      '     ^ T=\n"
            "  /     \\       .--'\n"
            " |      /       )'-.\n"
            "  \\ \\-.__)    ''--.)\n"
            "   '.'-.__.-.\n"
            "     '-...-'\033[0m\n\n";
        std::cout << "Your kitten " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 10 && savedInt < 26) {
        std::cout <<
            "\033[33m_                ___       _.--.\n"
            "\\’.|\\..----...-’’   ‘-._.-'_.-’’\n"
            "/  ‘ ‘         ,       __.--’\n"
            ")/’ _/     \\   ‘-_,   /\n"
            "‘-’’ ‘’\\_  ,_.-;_.-\\_ ‘,\n"
            "    _.-’_./   {_.’   ; /\n"
            "   {_.-’’-         {_/\033[0m\n\n";
        std::cout << "Your cat " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }
    else if (savedInt > 25 && savedInt < 76) {
        std::cout <<
            "\033[33m                         ,\n"
            "  ,-.       _,---._ __  / \\\n"
            " /  )    .-'       './ /   \\\n"
            "(  (   ,'            '/    /|\n"
            " \\  '_'             \\'\\   / |\n"
            "  '.              ,  \\ \\ /  |\n"
            "   /'.          ,'-'----Y   |\n"
            "  (            ;        |   '\n"
            "  |  ,-.    ,-'         |  /\n"
            "  |  | (   |            | /\n"
            "  )  |  \\  '.___________|/\n"
            "  '--'   '--'\033[0m\n\n";
        std::cout << "Your cat " << savedString << " looks happy! You've fed it " << savedInt << " times.\n\n"
            "\033[36mgit commands work with git replaced with cat. make sure you have git installed.\n"
            "catbash adopt <name> to adopt your first cat, or adopt a new one.\n"
            "catbash feed to feed your cat.\n"
            "yo <prompt> for command help.\n\n"
            "feed your cat every day to watch it grow!\033[0m\n\n";
    }

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
