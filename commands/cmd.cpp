/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:47:44 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/17 22:29:51 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

void Server::cmd_parser(std::string &msg, int fd)
{
	
	std::cout << "Client " << fd << " sent: " << msg << std::endl;
	if (!msg.compare(0, 4, "PASS") || !msg.compare(0, 4, "pass"))
		this->pass(msg, fd);
	else if(this->getClient(fd)->getIsLoggedIn() == false)
		senderreur(fd, "451 :You have not registered");
	else if (!msg.compare(0, 4, "BONG") || !msg.compare(0, 4, "bong"))
		return;
	else if (!msg.compare(0, 4, "PING") || !msg.compare(0, 4, "ping"))
		// this->ping(fd, cmd);
		std::cout << "PING :" << msg << std::endl;
		// std::cout << "PASS :" << msg << std::endl;
	else if (!msg.compare(0, 4, "USER") || !msg.compare(0, 4, "user"))
		this->user(msg, fd);
		// std::cout << "USER :" << msg << std::endl;
	else if (!msg.compare(0, 4, "NICK") || !msg.compare(0, 4, "nick"))
		this->nick(msg, fd);
		// std::cout << "NICK :" << msg << std::endl;
	else if (!msg.compare(0, 4, "JOIN") || !msg.compare(0, 4, "join"))
		this->join(msg, fd);
		// std::cout << "JOIN :" << msg << std::endl;
	else if (!msg.compare(0, 4, "PART") || !msg.compare(0, 4, "part"))
		// this->part(msg, fd);
		std::cout << "PART :" << msg << std::endl;
	else if (!msg.compare(0, 4, "KICK") || !msg.compare(0, 4, "kick"))
		this->kick(msg, fd);
		// std::cout << "KICK :" << msg << std::endl;
	else if (!msg.compare(0, 6, "PRIVMSG") || !msg.compare(0, 6, "privmsg"))
		// this->privmsg(msg, fd);
		std::cout << "PRIVMSG :" << msg << std::endl;
	else if (!msg.compare(0, 5, "TOPIC") || !msg.compare(0, 5, "topic"))
		this->topic(msg, fd);
		// std::cout << "TOPIC :" << msg << std::endl;
	else if (!msg.compare(0, 4, "MODE") || !msg.compare(0, 4, "mode"))
		this->mode(msg, fd);
		// std::cout << "MODE :" << msg << std::endl;
	else if (!msg.compare(0, 4, "QUIT") || !msg.compare(0, 4, "quit"))
		// this->quit(fd);
		std::cout << "QUIT :" << msg << std::endl;
	else if (!msg.compare(0, 6, "INVITE") || !msg.compare(0, 6, "invite"))
		this->invite(msg, fd);
		// std::cout << "INVITE :" << msg << std::endl;
	else
		senderreur(fd, "421 :Unknown command");
}