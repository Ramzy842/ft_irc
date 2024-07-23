/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:07:27 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 07:56:15 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
#include "../Server.hpp"

void Server::sendError(int code, std::string clientname, std::string channelname, int fd, std::string msg)
{
	std::stringstream ss;
	ss << ":localhost " << code << " " << clientname << " " << channelname << msg;
	std::string resp = ss.str();
	if(send(fd, resp.c_str(), resp.size(),0) == -1)
		std::cerr << "send() faild" << std::endl;
}

int Server::splitJoinArgs(std::vector<std::pair<std::string, std::string> >& tokens, std::string msg, int fd)
{
	std::vector<std::string> tmp;
	std::string ChStr, PassStr, buff;
	std::istringstream iss(msg);
	while(iss >> msg)
		tmp.push_back(msg);
	if (tmp.size() < 2) {tokens.clear(); return 0;}
	tmp.erase(tmp.begin());
	ChStr = tmp[0]; tmp.erase(tmp.begin());
	if (!tmp.empty()) {PassStr = tmp[0]; tmp.clear();}
	for (size_t i = 0; i < ChStr.size(); i++){
		if (ChStr[i] == ',')
				{tokens.push_back(std::make_pair(buff, "")); buff.clear();}
		else buff += ChStr[i];
	}
	tokens.push_back(std::make_pair(buff, ""));
	if (!PassStr.empty()){
		size_t j = 0; buff.clear();
		for (size_t i = 0; i < PassStr.size(); i++){
			if (PassStr[i] == ',')
				{tokens[j].second = buff; j++; buff.clear();}
			else buff += PassStr[i];
		}
		tokens[j].second = buff;
	}
	for (size_t x = 0; x < tokens.size(); x++)
	{
		if (tokens[x].first.empty())
			tokens.erase(tokens.begin() + x--);		
	}
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (*(tokens[i].first.begin()) != '#')
		{
			sendError(403, this->getClient(fd)->getNickname(),
				tokens[i].first, this->getClient(fd)->getFd(), " :No such channel\r\n");
			tokens.erase(tokens.begin() + i--);
		}
		else
			tokens[i].first.erase(tokens[i].first.begin());
	}
	return 1;
}

void Server::sendError(int code, std::string clientname, int fd, std::string msg)
{
	std::stringstream ss;
	ss << ":localhost " << code << " " << clientname << msg;
	std::string resp = ss.str();
	if(send(fd, resp.c_str(), resp.size(),0) == -1)
		std::cerr << "send() faild" << std::endl;
}


int Server::getClientsNumberInChannel(std::string channelName)
{
	for (size_t x = 0; x < this->channels.size(); x++){
		if (this->channels[x]->getName() == channelName)
			return this->channels[x]->getMembers().size();
	}
	return 0;
}

std::string Server::getClientList(Channel *channel)
{
	std::string clientList;
	for (size_t x = 0; x < channel->getMembers().size(); x++)
	{
		clientList += channel->getMembers()[x]->getNickname();
		clientList += " ";
	}
	return clientList;
}


std::string getServerResponse(const std::string& nickname,
                              const std::string& hostname, 
                              const std::string& ipaddress, 
                              const std::string& channelname,
                              const std::string& clientList) {
	std::string response;
  	if (!nickname.empty() && !hostname.empty() && !ipaddress.empty() && !channelname.empty())
  		response += ":" + nickname + "!" + hostname + "@" + ipaddress + " JOIN #" + channelname + "\n";
  	if (!nickname.empty() && !channelname.empty() && !clientList.empty())
    	response += ": 353 " + nickname + " @ #" + channelname + " :@" + clientList + "\n";
  	if (!nickname.empty() && !channelname.empty())
    	response += ": 366 " + nickname + " #" + channelname + " :END of /NAMES list";
	return response;
}

bool Server::clientAlreadyInChannel(int fd, std::string channelName)
{
	for(size_t x = 0; x < this->channels.size(); x++)
	{
		std::vector<Client *> members_ = this->channels[x]->getMembers();
		for (size_t y = 0; y < members_.size(); y++)
		{
			if (this->channels[x]->getName() == channelName
				&& members_[y]->getFd() == fd)
				return true;
		}
	}
	return false;
}

bool Server::clientIsInvited(int fd,Channel *channel)
{
	for (size_t y = 0; y < this->getClient(fd)->getInvitedChannels().size(); y++)
	{
		if (this->getClient(fd)->getInvitedChannels()[y]->getName() == channel->getName())
			return true;
	}
	return false;
}


void Server::join(std::string &msg, int fd)
{
	std::vector<std::pair<std::string, std::string> > tokens;
	if (!splitJoinArgs(tokens, msg, fd))
		return ;
	if (tokens.size() > 10)
	{
		sendError(407, this->getClient(fd)->getNickname(), this->getClient(fd)->getFd(), " :Too many channels\r\n");
		return;
	}
	Client *client = this->getClient(fd);
	for (size_t i = 0; i < tokens.size(); i++)
	{
		bool foundChannel = false;
		for (size_t x = 0; x < channels.size(); x++)
		{
			if (channels[x]->getName() == tokens[i].first)
			{
				if (!clientAlreadyInChannel(fd,channels[x]->getName()))
				{
					if (!this->channels[x]->getPassword().empty() && this->channels[x]->getPassword() != tokens[i].second)
					{
						std::string msg = ":localhost 475 " + client->getNickname() + " #" + channels[x]->getName() + " :Cannot join channel (+k) - bad key";
						senderreur(fd, msg);		
					}
					else if (this->channels[x]->getIsInviteOnly() && !clientIsInvited(fd, channels[x]))
					{
						std::string msg = ":localhost 473 " + client->getNickname() + " #" + channels[x]->getName() + " :Cannot join channel (+i)";
						senderreur(fd, msg);
					}
					else if (this->channels[x]->getLimit() && this->channels[x]->getMembers().size() >= this->channels[x]->getLimit())
					{
						std::string msg = ":localhost 471 " + client->getNickname() + " #" + channels[x]->getName() + " :Cannot join channel (+l)";
						senderreur(fd, msg);
						
					}
					else
					{
						channels[x]->addMember(*client);
						this->sendMsg(fd,
							getServerResponse(client->getNickname(),
								client->getUsername(), client->getIpAddress(),
								channels[x]->getName(), this->getClientList(channels[x])));
								
						for(size_t i = 0; i < channels[x]->getMembers().size(); i++)
						{
							if (fd != channels[x]->getMembers()[i]->getFd())
							{
								sendMsg(channels[x]->getMembers()[i]->getFd(),
									getServerResponse(client->getNickname(), "",
								client->getHostname(), client->getIpAddress(),
								channels[x]->getName()));
							}
							
						}
						
					}
				}	
				foundChannel = true;
				break ;
			}
		}
		if (!foundChannel)
		{
			Channel *newChannel = new Channel;
			newChannel->setName(tokens[i].first);
			newChannel->addOperator(*this->getClient(fd));
			channels.push_back(newChannel);
			channels[channels.size() - 1]->addMember(*client);
			this->sendMsg(fd,
				getServerResponse(client->getNickname(),
					client->getUsername(), client->getIpAddress(),
						newChannel->getName(), this->getClientList(newChannel)));
		}
	}
	
}