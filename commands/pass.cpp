/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:49:41 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/15 13:13:42 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTRED "462 :You may not reregister"

bool Server::handlerpasscommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2)
		return senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	if (this->getClient(fd)->getIsRegistered())
		return senderreur(fd, ERR_ALREADYREGISTRED);
	return true;
}

void Server::pass(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	if(!handlerpasscommand(cmd, fd))
		return;

	if (this->checkpass(cmd[1]))
	{
		sendMsg(fd, "001 :Welcome to the Internet Relay Network " + this->getClient(fd)->getNickname());
		this->getClient(fd)->setIsRegistered(true);
	}
	else 
		senderreur(fd, "464 :Password incorrect ");
}