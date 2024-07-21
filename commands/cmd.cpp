/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:47:44 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/21 16:59:14 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

void Server::handler_cmd_parser(std::string &msg, int fd)
{
	// std::cout << "Client " << fd << " sent: " << msg << std::endl;
	// std::vector<std::string> cmd = split_command(msg);
	// if(getClient(fd)->getIsHexChat() || cmd[0] == "CAP")
	// {
	// 	if (cmd[0] == "CAP" && cmd.size() < 3)
	// 		getClient(fd)->setIsHexChat(true);
	// 	else if(cmd[0] == "CAP" && cmd.size() < 5)
	// 	{
	// 		std::cout << "im here  2" << std::endl;
	// 		std::string msg = cmd[2] + " " + cmd[3];
	// 		this->pass(msg, fd);
	// 		std::cout << "111111111 hna PASS :" << msg << std::endl;	
	// 	}
	// 	else if(cmd[0] == "CAP" && cmd.size() > 4)
	// 	{
	// 		std::cout << "im here"	<< std::endl;
	// 		std::string msg = cmd[2] + " " + cmd[3];
	// 		this->pass(msg, fd);
	// 		std::cout << "111111111 hna PASS :" << msg << std::endl;
	// 		msg = cmd[4] + " " + cmd[5];
	// 		std::cout << "NICK :" << msg << std::endl;
	// 		this->nick(msg, fd);
	// 		std::cout << "nick :" << msg << std::endl;
	// 		msg = cmd[6] + " " + cmd[7] + " " + cmd[7] + " " + cmd[7] + " " + cmd[9].substr(1);
	// 		std::cout << "USER :" << msg << "*/*/&&&&&&&&&&" << std::endl;
	// 		this->user(msg, fd);
			
	// 	}
	// 	else if (!msg.compare(0, 4, "BONG") || !msg.compare(0, 4, "bong"))
	// 		return;
	// 	else if (!msg.compare(0, 4, "PING") || !msg.compare(0, 4, "ping"))
	// 		std::cout << "PING :" << msg << std::endl;
	// 	else if (!msg.compare(0, 4, "JOIN") || !msg.compare(0, 4, "join"))
	// 		this->join(msg, fd);
	// 		// std::cout << "JOIN :" << msg << std::endl;
	// 	else if (!msg.compare(0, 4, "PART") || !msg.compare(0, 4, "part"))
	// 		// this->part(msg, fd);
	// 		std::cout << "PART :" << msg << std::endl;
	// 	else if (!msg.compare(0, 4, "KICK") || !msg.compare(0, 4, "kick"))
	// 		this->kick(msg, fd);
	// 		// std::cout << "KICK :" << msg << std::endl;
	// 	else if (!msg.compare(0, 7, "PRIVMSG") || !msg.compare(0, 7, "privmsg"))
	// 		this->privmsg(msg, fd);
	// 		// std::cout << "PRIVMSG :" << msg << std::endl;
	// 	else if (!msg.compare(0, 5, "TOPIC") || !msg.compare(0, 5, "topic"))
	// 		this->topic(msg, fd);
	// 		// std::cout << "TOPIC :" << msg << std::endl;
	// 	else if (!msg.compare(0, 4, "MODE") || !msg.compare(0, 4, "mode"))
	// 		this->mode(msg, fd);
	// 		// std::cout << "MODE :" << msg << std::endl;
	// 	else if (!msg.compare(0, 4, "QUIT") || !msg.compare(0, 4, "quit"))
	// 		// this->quit(msg, fd);
	// 		std::cout << "QUIT :" << msg << std::endl;
	// 	else if (!msg.compare(0, 6, "INVITE") || !msg.compare(0, 6, "invite"))
	// 		this->invite(msg, fd);
	// 		// std::cout << "INVITE :" << msg << std::endl;
	// 	else
	// 		senderreur(fd, "421 :Unknown command");
		
	// }
	// else
	// {
		if (!msg.compare(0, 4, "PASS") || !msg.compare(0, 4, "pass"))
			this->pass(msg, fd);
		// else if(!this->getClient(fd)->getIsLoggedIn())
		// 	senderreur(fd, "451 :You have not logged in");
		else if (!msg.compare(0, 4, "NICK") || !msg.compare(0, 4, "nick"))
			this->nick(msg, fd);
		// else if(!this->getClient(fd)->getIsNickSet())
		// 	senderreur(fd, "451 :You have not set your nickname");
		else if (!msg.compare(0, 4, "USER") || !msg.compare(0, 4, "user"))
			this->user(msg, fd);
		// else if(!this->getClient(fd)->getIsRegistered())
		// 	senderreur(fd, "451 :You have not registered");		
		else if (!msg.compare(0, 4, "BONG") || !msg.compare(0, 4, "bong"))
			return;
		else if (!msg.compare(0, 4, "PING") || !msg.compare(0, 4, "ping"))
			std::cout << "PING :" << msg << std::endl;
		else if (!msg.compare(0, 4, "JOIN") || !msg.compare(0, 4, "join"))
			this->join(msg, fd);
			// std::cout << "JOIN :" << msg << std::endl;
		else if (!msg.compare(0, 4, "PART") || !msg.compare(0, 4, "part"))
			// this->part(msg, fd);
			std::cout << "PART :" << msg << std::endl;
		else if (!msg.compare(0, 4, "KICK") || !msg.compare(0, 4, "kick"))
			this->kick(msg, fd);
			// std::cout << "KICK :" << msg << std::endl;
		else if (!msg.compare(0, 7, "PRIVMSG") || !msg.compare(0, 7, "privmsg"))
			this->privmsg(msg, fd);
			// std::cout << "PRIVMSG :" << msg << std::endl;
		else if (!msg.compare(0, 5, "TOPIC") || !msg.compare(0, 5, "topic"))
			this->topic(msg, fd);
			// std::cout << "TOPIC :" << msg << std::endl;
		else if (!msg.compare(0, 4, "MODE") || !msg.compare(0, 4, "mode"))
			this->mode(msg, fd);
			// std::cout << "MODE :" << msg << std::endl;
		else if (!msg.compare(0, 4, "QUIT") || !msg.compare(0, 4, "quit"))
			// this->quit(msg, fd);
			std::cout << "QUIT :" << msg << std::endl;
		else if (!msg.compare(0, 6, "INVITE") || !msg.compare(0, 6, "invite"))
			this->invite(msg, fd);
			// std::cout << "INVITE :" << msg << std::endl;
		else
			senderreur(fd, "421 :Unknown command");
}

std::vector<std::string> split_recivedBuffer(std::string str)
{
	std::vector<std::string> vec;
	std::istringstream stm(str);
	std::string line;
	while(std::getline(stm, line))
	{
		size_t pos = line.find_first_of("\r\n");
		if(pos != std::string::npos)
			line = line.substr(0, pos);
		vec.push_back(line);
	}
	return vec;
}

void Server::cmd_parser(std::string &msg, int fd)
{
	std::vector<std::string> lines = split_recivedBuffer(msg);
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> cmd = split_command(lines[i]);
		
		if(lines[i].empty())
			continue;
		else if(cmd[0] != "CAP")
		{
			// std::cout << "im in top of handler_cmd_parser " << lines[i] << std::endl;
			handler_cmd_parser(lines[i], fd);
		}
		else 
		{
			// std::cout << "im here : and command is "<< cmd[0] << std::endl;
			getClient(fd)->setIsHexChat(true);
		}
	}
}