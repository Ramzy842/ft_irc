/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:47:44 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/13 21:20:01 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

void Server::cmd_parser(std::string &msg, int fd)
{
	
	std::cout << "Client " << fd << " sent: " << msg << std::endl;
	if (!msg.compare(0, 4, "BONG") || !msg.compare(0, 4, "bong"))
		return;
	else if (!msg.compare(0, 4, "PING") || !msg.compare(0, 4, "ping"))
		// cmd::ping(fd, cmd);
		std::cout << "PING :" << msg << std::endl;
	else if (!msg.compare(0, 4, "PASS") || !msg.compare(0, 4, "pass"))
		// cmd::pass(msg, fd);
		std::cout << "PASS :" << msg << std::endl;
	else if (!msg.compare(0, 4, "USER") || !msg.compare(0, 4, "user"))
		// cmd::user(msg, fd);
		std::cout << "USER :" << msg << std::endl;
	else if (!msg.compare(0, 4, "NICK") || !msg.compare(0, 4, "nick"))
		// cmd::nick(msg, fd);
		std::cout << "NICK :" << msg << std::endl;
	else if (!msg.compare(0, 4, "JOIN") || !msg.compare(0, 4, "join"))
		// cmd::join(msg, fd);
		std::cout << "JOIN :" << msg << std::endl;
	else if (!msg.compare(0, 4, "PART") || !msg.compare(0, 4, "part"))
		// cmd::part(msg, fd);
		std::cout << "PART :" << msg << std::endl;
	else if (!msg.compare(0, 4, "KICK") || !msg.compare(0, 4, "kick"))
		// cmd::kick(msg, fd);
		std::cout << "KICK :" << msg << std::endl;
	else if (!msg.compare(0, 6, "PRIVMSG") || !msg.compare(0, 6, "privmsg"))
		// cmd::privmsg(msg, fd);
		std::cout << "PRIVMSG :" << msg << std::endl;
	else if (!msg.compare(0, 5, "TOPIC") || !msg.compare(0, 5, "topic"))
		// this->topic(msg, fd);
		std::cout << "TOPIC :" << msg << std::endl;
	else if (!msg.compare(0, 4, "MODE") || !msg.compare(0, 4, "mode"))
		// cmd::mode(msg, fd);
		std::cout << "MODE :" << msg << std::endl;
	else if (!msg.compare(0, 4, "QUIT") || !msg.compare(0, 4, "quit"))
		// cmd::quit(fd);
		std::cout << "QUIT :" << msg << std::endl;
	else if (!msg.compare(0, 6, "INVITE") || !msg.compare(0, 6, "invite"))
		Server::invite(msg, fd);
		// std::cout << "INVITE :" << msg << std::endl;
	else
		send(fd, "500 Command not recognized.\n", 28, 0);
}