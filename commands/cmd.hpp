#pragma once

#include "../Server.hpp"
#include "../Client.hpp"
#include <sstream>

std::vector<std::string> split_command(std::string &msg);
std::vector<std::string> split_command_Line(std::string& msg);
Channel *senderreur(int fd, std::string msg);
bool isEmpyCmd(std::vector<std::string> cmd);