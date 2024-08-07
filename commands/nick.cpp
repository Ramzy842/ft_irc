/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:44:23 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 07:46:57 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

bool Server::handlernickcommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2 || cmd[1].empty())
		return senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	if (getClientByName(cmd[1]))
		return senderreur(fd, "433 " + cmd[1] + " :Nickname is already in use");
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
	sendWelcome(fd);
}