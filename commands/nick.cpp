/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:44:23 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/18 03:31:12 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

bool Server::handlernickcommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2 || cmd[1].empty())
		return senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	if(this->getClient(fd)->getIsNickSet())
		return senderreur(fd, "462 :You Already set your nickname");
	return true;
}


void Server::nick(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	if(!handlernickcommand(cmd, fd))
		return;
	this->getClient(fd)->setNickname(cmd[1]);
	this->getClient(fd)->setIsNickSet(true);
	sendMsg(fd, "001 :Welcome to the Internet Relay Network " + this->getClient(fd)->getNickname());
}