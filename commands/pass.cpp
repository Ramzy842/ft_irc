/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:49:41 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 07:47:07 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"
#define ERR_ALREADYLOGGEDIN "462 :You Already logged in"

bool Server::handlerpasscommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() != 2)
		return senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	if (this->getClient(fd)->getIsLoggedIn())
		return senderreur(fd, ERR_ALREADYLOGGEDIN);
	return true;
}

void Server::pass(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	if(!handlerpasscommand(cmd, fd))
		return;
	if (this->checkpass(cmd[1]))
	{
		this->getClient(fd)->setIsLoggedIn();
	}
	else {
		senderreur(fd, "464 :Password incorrect ");
	} 
}