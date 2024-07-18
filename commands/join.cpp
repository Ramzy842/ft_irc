/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:07:27 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/18 09:10:37 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
#define ERR_TOOMANYCHANNELS "405 :You have joined too many channels"
#define ERR_BADCHANNELKEY(channel) "475 " + channel + " :Cannot join channel (incorrect key)"
#define ERR_CHANNELISFULL(channel) "471 " + channel + " :Cannot join channel (channel is full)"
#define ERR_INVITEONLYCHAN(channel) "473 " + channel + " :Cannot join channel (invite only)"
#define ERR_BANNEDFROMCHAN(channel) "474 " + channel + " :Cannot join channel (banned)"
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

int Server::splitJoinArgs(std::vector<std::pair<std::string, std::string> >& tokens, std::string msg, int fd)
{
	std::vector<std::string> tmp;
	std::string ChStr, PassStr, buff;
	(void)PassStr, (void)fd;
	std::istringstream iss(msg);
	while(iss >> msg)
		tmp.push_back(msg);
	if (tmp.size() < 2) {tokens.clear(); return 0;}
	tmp.erase(tmp.begin());
	ChStr = tmp[0]; tmp.erase(tmp.begin());
	// if (!tmp.empty()) {PassStr = tmp[0]; tmp.clear();}
	for (size_t i = 0; i < ChStr.size(); i++){
		if (ChStr[i] == ',')
				{tokens.push_back(std::make_pair(buff, "")); buff.clear();}
		else buff += ChStr[i];
	}
	tokens.push_back(std::make_pair(buff, ""));
	// if (!PassStr.empty()){
	// 	size_t j = 0; buff.clear();
	// 	for (size_t i = 0; i < PassStr.size(); i++){
	// 		if (PassStr[i] == ',')
	// 			{tokens[j].second = buff; j++; buff.clear();}
	// 		else buff += PassStr[i];
	// 	}
	// 	tokens[j].second = buff;
	// }
	// for (size_t i = 0; i < tokens.size(); i++) //erase the empty channel names
	// 	{if (tokens[i].first.empty())tokens.erase(tokens.begin() + i--);}
	// for (size_t i = 0; i < tokens.size(); i++){ //ERR_NOSUCHCHANNEL (403) // if the channel doesn't exist
	// 	if (*(tokens[i].first.begin()) != '#')
	// 		{senderreur(403, this->getClient(fd)->getNickname(), tokens[i].first, this->getClient(fd)->getFd(), " :No such channel\r\n"); tokens.erase(tokens.begin() + i--);}
	// 	else
	// 		tokens[i].first.erase(tokens[i].first.begin());
	// }
	return 1;
}

void Server::join(std::string &msg, int fd)
{
	std::vector<std::string> cmd = split_command(msg);
	if (cmd.size() < 2)
	{
		senderreur(fd, "461 JOIN :Not enough parameters\r\n");
		return;
	}
	std::vector<std::pair<std::string, std::string> > tokens;
	if(!splitJoinArgs(tokens, msg, fd))
	{
		senderreur(fd, "461 JOIN :Not enough parameters\r\n");
		return;
	}
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].first.empty())
			continue;
		if (*(tokens[i].first.begin()) != '#')
		{
			senderreur(fd, "461 JOIN :Not enough parameters\r\n");
			// senderreur(403, this->getClient(fd)->getNickname(), tokens[i].first, fd, " :No such channel\r\n");
			continue;
		}
		tokens[i].first.erase(tokens[i].first.begin());
		Channel *channel = this->getChannelByName(tokens[i].first);
		if (!channel)
		{
			channel = new Channel(tokens[i].first);
			this->channels.push_back(*channel);
		}
		if (channel->getMemberByName(this->getClient(fd)->getNickname()))
			continue;
		if (this->getClient(fd)->getChannels().size() >= 10)
		{
			senderreur(fd, "461 JOIN :Not enough parameters\r\n");
			// senderreur(405, this->getClient(fd)->getNickname(), fd, " :You have joined too many channels\r\n");
			continue;
		}
		if (!channel->getPassword().empty() && channel->getPassword() != tokens[i].second)
		{
			// if (!channel->isInvited(this->getClient(fd), 0))
			// {
				senderreur(fd, "461 JOIN :Not enough parameters\r\n");
				// senderreur(475, this->getClient(fd)->getNickname(), fd, " :Cannot join channel (+k) - bad key\r\n");
				continue;
			// }
		}
		if (channel->getIsInviteOnly())
		{
			// senderreur(473, this->getClient(fd)->getNickname(), fd, " :Cannot join channel (invite only)\r\n");
			senderreur(fd, "461 JOIN :Not enough parameters\r\n");
			continue;
		}
		if (channel->getIsInviteOnly())
		//! if (channel->isBanned(this->getClient(fd)->getNickname()))
		{
			senderreur(fd, "461 JOIN :Not enough parameters\r\n");
			// senderreur(474, this->getClient(fd)->getNickname(), fd, " :Cannot join channel (banned)\r\n");
			continue;
		}
		if (channel->getMembers().size() >= 10)
		{
			senderreur(fd, "461 JOIN :Not enough parameters\r\n");
			// senderreur(471, this->getClient(fd)->getNickname(), fd, " :Cannot join channel (channel is full)\r\n");
			continue;
		}
		channel->addMember(*this->getClient(fd));
		channel->sendToAll(":" + this->getClient(fd)->getNickname() + " JOIN " + channel->getName() + "\r\n");
	}
}