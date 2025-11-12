#pragma once
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

// Declare the function that returns your command table
std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> make_cmd_table(int& savedInt, std::string& savedString, std::string& lastRunDate);

std::string getTodayDate();