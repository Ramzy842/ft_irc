/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:47:44 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 04:38:26 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

void Server::handler_cmd_parser(std::string &msg, int fd)
{
		if (!msg.compare(0, 4, "PASS") || !msg.compare(0, 4, "pass"))
			this->pass(msg, fd);
		else if (!msg.compare(0, 4, "NICK") || !msg.compare(0, 4, "nick"))
			this->nick(msg, fd);
		else if (!msg.compare(0, 4, "USER") || !msg.compare(0, 4, "user"))
			this->user(msg, fd);
		else if(!getClient(fd)->getIsNickSet() || !getClient(fd)->getIsLoggedIn() || !getClient(fd)->getIsRegistered())
			senderreur(fd, "451 :You have not registered");
		else if (!msg.compare(0, 4, "JOIN") || !msg.compare(0, 4, "join"))
			this->join(msg, fd);
		else if (!msg.compare(0, 4, "KICK") || !msg.compare(0, 4, "kick"))
			this->kick(msg, fd);
		else if (!msg.compare(0, 7, "PRIVMSG") || !msg.compare(0, 7, "privmsg"))
			this->privmsg(msg, fd);
		else if (!msg.compare(0, 5, "TOPIC") || !msg.compare(0, 5, "topic"))
			this->topic(msg, fd);
		else if (!msg.compare(0, 4, "MODE") || !msg.compare(0, 4, "mode"))
			this->mode(msg, fd);
		else if (!msg.compare(0, 4, "QUIT") || !msg.compare(0, 4, "quit"))
			this->quit(msg, fd);
		else if (!msg.compare(0, 6, "INVITE") || !msg.compare(0, 6, "invite"))
			this->invite(msg, fd);
		else
			senderreur(fd, "421 :Unknown command");
}

void Server::cmd_parser(std::string &msg, int fd)
{
	std::vector<std::string> lines = split_command_Line(msg);
	for (size_t i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> cmd = split_command(lines[i]);
		
		if(lines[i].empty())
			continue;
		else if(cmd[0] != "CAP")
			handler_cmd_parser(lines[i], fd);
		else 
			getClient(fd)->setIsHexChat(true);
	}
}