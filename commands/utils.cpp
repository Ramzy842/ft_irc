/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:07:22 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 05:43:52 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
std::vector<std::string> split_command(std::string& msg) // , int parm )
{
	std::vector<std::string> cmd;
	std::string word = "";
	for (size_t i = 0; i < msg.size(); i++)
	{
		if (msg[i] == ' ') //* && parm > i);
		{
			std::cout << "word is :" << word << i << std::endl;
			cmd.push_back(word);
			word = "";
		}
		else
			word += msg[i];
	}
	word = word.substr(0, word.size());
	cmd.push_back(word);
	return cmd;
}

std::vector<std::string> split_command_Line(std::string& msg) // , int parm )
{
	std::vector<std::string> cmd;
	std::string word = "";
	for (size_t i = 0; i < msg.size(); i++)
	{
		if (msg[i] == '\r') //* && parm > i);
		{
			if(msg[i + 1] == '\n')
				i++;
				cmd.push_back(word);
				word = "";
		}
		else
			word += msg[i];
	}
	word = word.substr(0, word.size());
	cmd.push_back(word);
	return cmd;
}



Channel *Server::senderreur(int fd, std::string msg)
{

	if (!this->getClient(fd)->getIsHexChat())
		msg = GREEN + msg + RESET + "\n";
	else
		msg += "\r\n";
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
	{
		if(!this->getClient(fd)->getIsHexChat())
			std::cerr << RED << "Failed to send message" << RESET << std::endl;
		else
			std::cerr << "Failed to send message" << std::endl;
	}
	return (NULL);
}

Channel *senderreur(int fd, std::string msg, bool hexChat)
{
	(void) hexChat;
	msg = RED + msg + RESET + "\n";
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
		std::cerr  << "Failed to send message" << RESET << std::endl;
	return (NULL);
}

void Server::sendMsg(int fd, std::string msg)
{
	std::cout << "im here in sendMsg and getIshexChat is " << this->getClient(fd)->getIsHexChat() << " and message is :" << msg << std::endl;
	if (!this->getClient(fd)->getIsHexChat())
		msg = GREEN + msg + RESET + "\n";
	else
		msg += "\r\n";
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
	{
		if(!this->getClient(fd)->getIsHexChat())
			std::cerr << RED << "Failed to send message" << RESET << std::endl;
		else
			std::cerr << "Failed to send message" << std::endl;
	}
}

bool isEmpyCmd(std::vector<std::string> cmd)
{
	for (size_t i = 1; i < cmd.size(); i++)
	{
		if (!cmd[i].empty())
			return false;
	}
	return true;
}

void Server::sendWelcome(int fd)
{
	if(!getClient(fd)->getIsRegistered() || !getClient(fd)->getIsLoggedIn() || !getClient(fd)->getIsNickSet())
		return;
	std::string msg = "001 :Welcome to the Internet Relay Network " + this->getClient(fd)->getNickname();
	sendMsg(fd, msg);
}