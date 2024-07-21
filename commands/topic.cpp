/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:25:19 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/21 22:50:10 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"


#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

Channel *Server::topicErreurHandler(std::vector<std::string> cmd, int fd)
{
	// if (cmd.size() < 2 || !isEmpyCmd(cmd))
	// {
	// 	senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
	// 	return NULL;
	// }
	Channel *channel = this->getChannelByName(cmd[1].substr(1));
	if (!channel)
	{
		senderreur(fd, ERR_NOSUCHCHANNEL(cmd[1]));
		return NULL;
	}
	if (!channel->getMemberByName(this->getClient(fd)->getNickname()))
	{
		senderreur(fd, ERR_NOTONCHANNEL(cmd[1]));
		return NULL;
	}
	if (channel->getIsTopic() && !channel->getOperatorByName(this->getClient(fd)->getNickname()))
	{
		senderreur(fd, ERR_CHANOPRIVSNEEDED(cmd[1]));
		return NULL;
	}
	return channel;
}

void Server::topic(std::string &msj, int fd)
{
	// std::string channel = msj.substr(6);
	std::vector<std::string> cmd = split_command(msj);
	Channel *channel = topicErreurHandler(cmd, fd);
	if (!channel)
		return;
	std::string rps;
	std::string newtopic = msj.substr(msj.find(":", 1) + 1);
	if (cmd.size() == 2)
	{
		std::string topic = channel->getTopic();
		if(topic == "")
		{
			rps = ": 331 " + channel->getName() + " :No topic is set\n";
			
		}
		else
		{
			rps = ": 332 " + this->getClient(fd)->getNickname() + " #" + channel->getName() + " " + topic + "\n";
			rps +=": 333 " + this->getClient(fd)->getNickname() + " #" + channel->getName() + " " + this->getClient(fd)->getNickname()+ " " + std::to_string(time(0)); 
			std::cout << "rps: " << rps << std::endl;
		}
		for(size_t i = 0; i < channel->getMembers().size(); i++)
			sendMsg(channel->getMembers()[i]->getFd(), rps);
	}
	else
	{
		channel->setTopic(newtopic);
		std::string rps = ":" + this->getClient(fd)->getNickname() + "!" + this->getClient(fd)->getUsername() + "@localhost TOPIC #" + channel->getName() + " " + newtopic;
		for(size_t i = 0; i < channel->getMembers().size(); i++)
			sendMsg(channel->getMembers()[i]->getFd(), rps);
	}
}