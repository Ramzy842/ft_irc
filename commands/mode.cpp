/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:14:07 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 07:47:12 by rchahban         ###   ########.fr       */
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
	if (cmd.size() < 3)
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
		senderreur(fd, ERR_CHANOPRIVSNEEDED(getClient(fd)->getNickname()));
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
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " +o " + client->getNickname();
			for(std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(), msg);
		}
		else if(cmd[2][1] == 'i')
		{
			if(cmd.size() != 3)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); 
				return;
			}
			channel->setIsInviteOnly(true);
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " +i";
			sendMsg(fd, msg);
		}
		else if(cmd[2][1] == 'k')
		{
			if(cmd.size() < 4)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); 
				return;
			}
			channel->setPassword(cmd[3]);
			std::string msg = ":" + getClient(fd)->getNickname() + "!"  + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " +k " + cmd[3];
			for (std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(), msg);
		}
		else if(cmd[2][1] == 'l')
		{
			if(cmd.size() < 4)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); 
				return;
			}
			channel->setLimit(std::stoi(cmd[3]));
			std::string msg = ":" + getClient(fd)->getNickname() + "!"+ getClient(fd)->getHostname() + " MODE #" + channel->getName() + " +l " + cmd[3];
			for (std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(),msg);
		}
		else if (cmd[2][1] == 't')
		{
			if (cmd.size() != 3)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
				return;
			}
			channel->setIsTopic(true);
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " +t";
			sendMsg(fd, msg);
			for (std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(), msg);
		}
		else
			senderreur(fd, ERR_UNKNOWNMODE(cmd[2]));
	}
	else
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
			channel->removeOperator(*client);
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " -o " + client->getNickname();
			sendMsg(fd, msg);
			sendMsg(client->getFd(), msg);
		}
		else if(cmd[2][1] == 'i')
		{
			if(cmd.size() != 3)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
				return;
			}
			channel->setIsInviteOnly(false);
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " -i";
			sendMsg(fd, msg);
		}
		else if (cmd[2][1] == 'k')
		{
			channel->setPassword("");
			if(cmd.size() != 3)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); 
				return;
			}
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " -k";
			for(std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(), msg);
		}
		else if (cmd[2][1] == 'l')
		{
			if(cmd.size() != 3)
			{
				senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0])); 
				return;
			}
			channel->setLimit(0);
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " -l";
			for (std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(), msg);
		}
		else if (cmd[2][1] == 't')
		{
			channel->setIsTopic(false);
			std::string msg = ":" + getClient(fd)->getNickname() + "!" + getClient(fd)->getHostname() + " MODE #" + channel->getName() + " -t";
			for (std::vector<Client *>::iterator it = channel->getMembers().begin(); it != channel->getMembers().end(); ++it)
				sendMsg((*it)->getFd(), msg);
		}
		else
			senderreur(fd, ERR_UNKNOWNMODE(cmd[2]));
	}
}