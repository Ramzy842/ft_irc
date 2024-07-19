/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:14:07 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/19 21:15:08 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

// Error message macros
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
#define ERR_NOSUCHNICK(nick) "401 " + nick + " :No such nick/channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"
#define ERR_UNKNOWNMODE(mode) "472 " + mode + " :Unknown MODE flag"
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

Channel *Server::handlermodecommand(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2)// || !isEmpyCmd(cmd))
	{
		senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
		return NULL;
	}
	Channel *channel = this->getChannelByName(cmd[1].substr(1));
	if(!channel)
	{
		senderreur(fd, ERR_NOSUCHCHANNEL(cmd[1]));
		return NULL;
	}
	Client *isClient = this->getClient(fd);
	if(!channel->getMemberByName(isClient->getNickname()))
	{
		senderreur(fd, ERR_NOTONCHANNEL(cmd[1]));
		return NULL;
	}
	if(!channel->getOperatorByName(isClient->getNickname()))
	{
		senderreur(fd, ERR_CHANOPRIVSNEEDED(cmd[1]));
		return NULL;
	}
	return channel;
}

bool IsPlus(std::string mode)
{
	if (mode[0] == '+')
		return true;
	return false;
}

void Server::mode(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	Channel *channel = handlermodecommand(cmd, fd);
	if(!channel)
		return;
	bool isPlus = IsPlus(cmd[2]);
	if(isPlus)
	{
		if(cmd[2][1] == 'o')
		{
			if(cmd.size() < 4)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); 
				return;
			}
			Client *client = this->getClientByName(cmd[3]);
			if(!client)
			{
				senderreur(fd, ERR_NOSUCHNICK(cmd[3])); 
				return;
			}
			channel->addOperator(*client);
			sendMsg(fd, "MODE " + channel->getName() + " +o " + client->getNickname());
			sendMsg(client->getFd(), "MODE " + channel->getName() + " +o " + client->getNickname());
		}
	}
	else
	{
		if(cmd[2][1] == 'o')
		{
			if(cmd.size() < 4)
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); return;
			Client *client = this->getClientByName(cmd[3]);
			if(!client)
				senderreur(fd, ERR_NOSUCHNICK(cmd[3]));	return;
			channel->removeOperator(*client);
			sendMsg(fd, "MODE " + channel->getName() + " -o " + client->getNickname());
			sendMsg(client->getFd(), "MODE " + channel->getName() + " -o " + client->getNickname());
		}
	}
	// if (cmd[2][0] == '+')
	// {
	// 	if (cmd.size() < 4)
	// 	{
	// 		senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	// 		return;
	// 	}
	// 	if (cmd[3] == "o")
	// 	{
	// 		Client *client = this->getClientByName(cmd[3]);
	// 		if (!client)
	// 		{
	// 			senderreur(fd, ERR_NOSUCHNICK(cmd[3]));
	// 			return;
	// 		}
	// 		channel->addOperator(*client);
	// 	}
	// }
	// else if (cmd[2][0] == '-')
	// {
	// 	if (cmd.size() < 4)
	// 	{
	// 		senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	// 		return;
	// 	}
	// 	if (cmd[3] == "o")
	// 	{
	// 		Client *client = this->getClientByName(cmd[3]);
	// 		if (!client)
	// 		{
	// 			senderreur(fd, ERR_NOSUCHNICK(cmd[3]));
	// 			return;
	// 		}
	// 		channel->removeOperator(*client);
	// 	}
	// }
}