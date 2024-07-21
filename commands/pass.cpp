/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:49:41 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/21 16:52:54 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"
#define ERR_ALREADYLOGGEDIN "462 :You Already logged in"

bool Server::handlerpasscommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2)
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
	std::cout << "im here in pass :" << cmd[1] << std::endl;
	if (this->checkpass(cmd[1]))
	{
		std::cout << "im here in pass inside" << cmd[1] << std::endl;
		// sendMsg(fd, "001 :Welcome to the Internet Relay Network" + this->getClient(fd)->getNickname());
		this->getClient(fd)->setIsLoggedIn();
	}
	else {
		std::cout << "im here in pass outside" << cmd[1] << std::endl;
		senderreur(fd, "464 :Password incorrect ");
	} 
}