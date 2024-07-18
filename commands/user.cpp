/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:17:42 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/18 04:33:56 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
//! need to devlope

// Error message macros
#define ERR_NEEDMOREPARAMS "461 USER :Not enough parameters"
#define ERR_ALREADYREGISTRED "462 :You Already registered"


void Server::user(std::string &msg, int fd) {
	std::vector<std::string> cmd = split_command(msg);
	if(!this->getClient(fd)->getIsLoggedIn())
	{
		sendMsg(fd, "YOU NEED TO LOGIN FIRST");
		return;
	}
	if (cmd.size() < 5 )//|| !isEmpyCmd(cmd)) {
	{
		sendMsg(fd, ERR_NEEDMOREPARAMS);
		return;
	}

	if (this->getClient(fd)->getIsRegistered()) {
		senderreur(fd, ERR_ALREADYREGISTRED);
		return;
	}

	this->getClient(fd)->setUsername(cmd[1]);
	this->getClient(fd)->setHostname(cmd[2]);
	this->getClient(fd)->setServername(cmd[3]);
	this->getClient(fd)->setRealname(cmd[4]);

	sendMsg(fd, "001 :Welcome to the Internet Relay Network " + this->getClient(fd)->getNickname());
	this->getClient(fd)->setIsRegistered(true);
}