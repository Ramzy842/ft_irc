/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:21:00 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/21 22:10:09 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

// Error message macros
#define ERR_NOTPARAMS "461 :Not enough parameters"
#define ERR_NOSUCHCLIENT(client) "401 " + client + " :No such nick/channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_USERALREADYINCHANNEL(channel) "443 " + channel + " :User is already on channel"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"
#define ERR_LOGIN "530 Please login with USER and PASS\n"
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
//! need to add erreur of login in all others commands
Channel* Server::inviteErreurHandler(std::vector<std::string> cmd, int fd)
{
	if(cmd.size() != 3)
		return (senderreur(fd, ERR_NOTPARAMS));
	Channel *channel = this->getChannelByName(cmd[2].substr(1));
	if(cmd[2][0] != '#' || !channel)
		// failedsend = send(fd, "403 No such channel.\n", 21, 0);
		return senderreur(fd, ERR_NOSUCHCHANNEL(cmd[2].substr(1)));
	if(!this->getClientByName(cmd[1]))
		return senderreur(fd, ERR_NOSUCHCLIENT(cmd[1]));
	if(channel->getMemberByName(cmd[1]))
		return senderreur(fd, ERR_USERALREADYINCHANNEL(cmd[1]));
	// if(channel->getIsInviteOnly() == true)// || !channel->getOperatorByName(cmd[1]))
	// 	return senderreur(fd, ERR_CHANOPRIVSNEEDED(cmd[1]));
	return (channel);
}

void Server::invite(std::string &msg, int fd)
{
	//! still need to add if else for erreur but i need other commands to be implemented first
	std::vector<std::string> cmd = split_command(msg);
	// std::cout << "invite command ->" << cmd[0] << std::endl;
	Channel* channel = inviteErreurHandler(cmd, fd);
	std::cout << channel->getName() << std::endl;
	if(!channel)
		return;
    // channel->addMember(*this->getClientByName(cmd[1]));
	std::cout << "invite command ->" << cmd[0] << std::endl;
	
	//! need to check message ot send
	Client *client = this->getClientByName(cmd[1]);
	std::vector<Channel *>invChannels = client->getInvitedChannels();
	invChannels.push_back(channel);
	client->setInvitedChannels(invChannels);
	std::string rps = ": 341 " + cmd[1] + " :User has been invited"; /* + this->getClientByName(cmd[1])->getInvitedChannels()[0]->getName() */;
	sendMsg(fd, rps);
	std::string rps2 = ":" + this->getClient(fd)->getNickname() + " INVITE " + cmd[1] + " to " + cmd[2];
	sendMsg(this->getClientByName(cmd[1])->getFd(), rps2);
	// sendMsg(channel->getId(), Channelrps);
	// std::string channel = cmd[2].substr(1);
	// if (channel.empty() || !channel.compare(0, 1, "#") == 0 || this->channels.find(channel) == this->channels.end())
	// {
	// 	send(fd, ":No such Channel\n", 27, 0);
	// 	return;
	// }
	// if (t)
	// {
	// 	send(fd, ":No such Channel\n", 27, 0);
	// 	return;
	// }
	// if(this->users[fd].is_logged == false)
	// {
	// 	send(fd, "530 Please login with USER and PASS.\n", 37, 0);
	// 	return;
	// }
	// std::string channel = msg.substr(6);
	// if (channel.empty())
	// {
	// 	send(fd, "461 Not enough parameters.\n", 27, 0);
	// 	// return;
	// }
	// if (channel.find(" ") != std::string::npos)
	// {
	// 	send(fd, "461 Not enough parameters.\n", 27, 0);
	// 	// return;
	// }
	// if (channel[0] != '#')
	// {
	// 	send(fd, "403 No such channel.\n", 21, 0);
	// 	// return;
	// }
	// if (this->users[fd].is_logged == false)
	// {
	// 	send(fd, "530 Please login with USER and PASS.\n", 37, 0);
	// 	return;
	// }
	// if (this->channels.find(channel) == this->channels.end())
	// {
	// 	send(fd, "403 No such channel.\n", 21, 0);
	// 	return;
	// }
	// if (this->channels[channel].users.find(this->users[fd].username) == this->channels[channel].users.end())
	// {
	// 	send(fd, "442 You're not on that channel.\n", 31, 0);
	// 	return;
	// }
	// std::string user = msg.substr(msg.find(" ", 7) + 1);
	// if (user.empty())
	// {
	// 	send(fd, "461 Not enough parameters.\n", 27, 0);
	// 	return;
	// }
	// if (user.find(" ") != std::string::npos)
	// {
	// 	send(fd, "461 Not enough parameters.\n", 27, 0);
	// 	return;
	// }
	// if (this->users.find(user) == this->users.end())
	// {
	// 	send(fd, "401 No such nick.\n", 18, 0);
	// 	return;
	// }
	// if (this->channels[channel].users.find(user) != this->channels[channel].users.end())
	// {
	// 	send(fd, "443 User is already on channel.\n", 31, 0);
	// 	return;
	// }
	// this->channels[channel].users.insert(user);
	// send(fd, "341 User has been invited.\n", 27, 0);
}