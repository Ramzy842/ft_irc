/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:44:23 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/15 12:00:48 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTRED "462 :You may not reregister"


bool Server::handlernickcommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2)
		return senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	if (!this->getClient(fd)->getIsRegistered())
		return senderreur(fd, ERR_ALREADYREGISTRED);
	// std::cout << "im here " << this->getClient(fd)->getIsRegistered() << std::endl;
	return true;
}


void Server::nick(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	if(!handlernickcommand(cmd, fd))
		return;
	this->getClient(fd)->setNickname(cmd[1]);
}