#pragma once

#include "Server.hpp"

class cmd
{

	public:
		void invite(std::string &msg, int fd);
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