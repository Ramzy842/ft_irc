/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:17:42 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/15 13:50:49 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
//! need to devlope

// Error message macros
#define ERR_NEEDMOREPARAMS "461 USER :Not enough parameters"
#define ERR_ALREADYREGISTRED "462 :You may not reregister"


void Server::user(std::string &msg, int fd) {
	std::vector<std::string> cmd = split_command(msg);
	if (cmd.size() < 5) {
		sendMsg(fd, ERR_NEEDMOREPARAMS);
		return;
	}

	if (this->getClient(fd)->getIsRegistered()) {
		sendMsg(fd, ERR_ALREADYREGISTRED);
		return;
	}

	this->getClient(fd)->setUsername(cmd[1]);
	this->getClient(fd)->setHostname(cmd[2]);
	this->getClient(fd)->setServername(cmd[3]);
	this->getClient(fd)->setRealname(cmd[4]);

	sendMsg(fd, "001 :Welcome to the Internet Relay Network " + this->getClient(fd)->getNickname());
	this->getClient(fd)->setIsRegistered(true);
}