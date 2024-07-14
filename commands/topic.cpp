/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:25:19 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/14 14:44:18 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "topic.hpp"

Channel *Server::topicErreurHandler(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() < 2)
	{
		senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
		return NULL;
	}
	Channel *channel = this->getChannelByName(cmd[1]);
	if (!channel)
	{
		senderreur(fd, ERR_NOSUCHCHANNEL(cmd[1]));
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
		if(topic.empty())
			rps = ": 331 " + channel->getName() + " :No topic is set\n";
		else
		rps = ": 332 " + channel->getName() + " " + topic + "\n";
		rps +=": 333 " + channel->getName() + " " + this->clients[fd].getNickname() + " " + std::to_string(time(0)) + "\n"; 
		sendMsg(fd, rps);
	}
	else
	{
		channel->setTopic(newtopic);
		std::string rps = ":" + this->clients[fd].getNickname() + " TOPIC " + channel->getName() + " :" + newtopic + "\n";
		sendMsg(channel->getId(), rps);
	}
}