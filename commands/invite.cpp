/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:21:00 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 04:41:20 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NOTPARAMS "461 :Not enough parameters"
#define ERR_NOSUCHCLIENT(client) "401 " + client + " :No such nick/channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_USERALREADYINCHANNEL(channel) "443 " + channel + " :User is already on channel"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"
#define ERR_LOGIN "530 Please login with USER and PASS\n"
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"

Channel* Server::inviteErreurHandler(std::vector<std::string> cmd, int fd)
{
	if(cmd.size() != 3)
		return (senderreur(fd, ERR_NOTPARAMS));
	Channel *channel = this->getChannelByName(cmd[2].substr(1));
	if(cmd[2][0] != '#' || !channel)
		return senderreur(fd, ERR_NOSUCHCHANNEL(cmd[2].substr(1)));
	if(!this->getClientByName(cmd[1]))
		return senderreur(fd, ERR_NOSUCHCLIENT(cmd[1]));
	if(channel->getMemberByName(cmd[1]))
		return senderreur(fd, ERR_USERALREADYINCHANNEL(cmd[1]));
	return (channel);
}

void Server::invite(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	std::cout << "invite command -> 0" << cmd[0] << std::endl;
	Channel* channel = inviteErreurHandler(cmd, fd);
	if(!channel)
		return;
	std::cout << "invite command -> 1" << cmd[0] << std::endl;
	std::cout << channel->getName() << std::endl;
	std::cout << "invite command ->" << cmd[0] << std::endl;
	
	Client *client = this->getClientByName(cmd[1]);
	std::vector<Channel *>invChannels = client->getInvitedChannels();
	invChannels.push_back(channel);
	client->setInvitedChannels(invChannels);
	std::string rps = ": 341 " + cmd[1] + " :User has been invited"; /* + this->getClientByName(cmd[1])->getInvitedChannels()[0]->getName() */;
	sendMsg(fd, rps);
	std::string rps2 = ":" + this->getClient(fd)->getNickname() + " INVITE " + cmd[1] + " to " + cmd[2];
	sendMsg(this->getClientByName(cmd[1])->getFd(), rps2);
}