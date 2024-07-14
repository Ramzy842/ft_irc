#pragma once

#include "../Server.hpp"
#include "../Client.hpp"
#include <sstream>

std::vector<std::string> split_command(std::string &msg);
Channel *senderreur(int fd, std::string msg);
void sendMsg(int fd, std::string msg);

class cmd
{

	public:
		// void invite(std::string &msg, int fd);
		void pass(std::string &msg, int fd);
		void user(std::string &msg, int fd);
		void nick(std::string &msg, int fd);
		void join(std::string &msg, int fd);
		void part(std::string &msg, int fd);
		void kick(std::string &msg, int fd);
		void privmsg(std::string &msg, int fd);
		// static void topci(std::string &msg, int fd);
		void topic(std::string &msg, int fd);
		void mode(std::string &msg, int fd);
};