/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:17:42 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 07:56:23 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

// Error message macros
#define ERR_NEEDMOREPARAMS "461 USER :Not enough parameters"
#define ERR_ALREADYREGISTRED "462 :You Already registered"


void Server::user(std::string &msg, int fd) {
	std::vector<std::string> cmd = split_command(msg);
	if (cmd.size() < 5 )
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
	this->getClient(fd)->setIsRegistered(true);
	sendWelcome(fd);
}