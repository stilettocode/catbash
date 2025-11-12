#include "catcommands.h"
#include <iostream>
#include <filesystem> 
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cstdlib>

// You can use the extern variables as declared in the header.
extern int savedInt;
extern std::string savedString;
extern std::string lastRunDate;

std::string getTodayDate() {
    time_t now = time(nullptr);
    tm ltm;
    localtime_s(&ltm, &now);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &ltm);
    return std::string(buf);
}

std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> make_cmd_table(int& savedInt, std::string& savedString, std::string& lastRunDate) {
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
               if (line.find(question) != std::string::npos || line.find("[end of text]") != std::string::npos || line.find("```") != std::string::npos || line.find("**Okay, hereΓÇÖs a concise answer : **") != std::string::npos) {
                   continue;
               }
               std::cout << buffer;
           }
           _pclose(pipe);
           std::cout << "\n";
       }},
       {"ls", [](auto args) { system("dir"); }},
       {"clear", [](auto args) { system("cls"); }},
       {"touch", [](auto args) {
            if (args.empty()) {
                std::cout << "touch: missing file argument\n";
                return;
            }
            else {
                system(("type nul > " + args[0]).c_str());
            }
        }},
       {"rm", [](auto args) {
            if (args.empty()) {
                std::cout << "rm: missing file argument\n";
                return;
            } else if (args[0] == "-r") {
                system(("rmdir /s " + args[1]).c_str());
            }
            else {
                system(("del " + args[0]).c_str());
            }
        }},
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

    return cmd_table;
}