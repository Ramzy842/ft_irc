/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:07:27 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/21 02:50:35 by rchahban         ###   ########.fr       */
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

// bool IsInvited(Client *cli, std::string ChName, int flag){
// 	if(cli->GetInviteChannel(ChName)){
// 		if (flag == 1)
// 			cli->RmChannelInvite(ChName);
// 		return true;
// 	}
// 	return false;
// }

void Server::sendError(int code, std::string clientname, int fd, std::string msg)
{
	std::stringstream ss;
	ss << ":localhost " << code << " " << clientname << msg;
	std::string resp = ss.str();
	if(send(fd, resp.c_str(), resp.size(),0) == -1)
		std::cerr << "send() faild" << std::endl;
}



// void Server::ExistCh(std::vector<std::pair<std::string, std::string> >&token, int i, int j, int fd)
// {
// 	if (this->channels[j].GetClientInChannel(GetClient(fd)->GetNickName()))// if the client is already registered
// 		return;
// 	if (SearchForClients(GetClient(fd)->GetNickName()) >= 10)//ERR_TOOMANYCHANNELS (405) // if the client is already in 10 channels
// 		{senderror(405, GetClient(fd)->GetNickName(), GetClient(fd)->GetFd(), " :You have joined too many channels\r\n"); return;}
// 	if (!this->channels[j].GetPassword().empty() && this->channels[j].GetPassword() != token[i].second){// ERR_BADCHANNELKEY (475) // if the password is incorrect
// 		if (!IsInvited(GetClient(fd), token[i].first, 0))
// 			{senderror(475, GetClient(fd)->GetNickName(), "#" + token[i].first, GetClient(fd)->GetFd(), " :Cannot join channel (+k) - bad key\r\n"); return;}
// 	}
// 	if (this->channels[j].GetInvitOnly()){// ERR_INVITEONLYCHAN (473) // if the channel is invit only
// 		if (!IsInvited(GetClient(fd), token[i].first, 1))
// 			{senderror(473, GetClient(fd)->GetNickName(), "#" + token[i].first, GetClient(fd)->GetFd(), " :Cannot join channel (+i)\r\n"); return;}
// 	}
// 	if (this->channels[j].GetLimit() && this->channels[j].GetClientsNumber() >= this->channels[j].GetLimit())// ERR_CHANNELISFULL (471) // if the channel reached the limit of number of clients
// 		{senderror(471, GetClient(fd)->GetNickName(), "#" + token[i].first, GetClient(fd)->GetFd(), " :Cannot join channel (+l)\r\n"); return;}
// 	// add the client to the channel
// 	Client *cli = GetClient(fd);
// 	this->channels[j].add_client(*cli);
// 	if(channels[j].GetTopicName().empty())
// 		_sendResponse(RPL_JOINMSG(GetClient(fd)->getHostname(),GetClient(fd)->getIpAdd(),token[i].first) + \
// 			RPL_NAMREPLY(GetClient(fd)->GetNickName(),channels[j].GetName(),channels[j].clientChannel_list()) + \
// 			RPL_ENDOFNAMES(GetClient(fd)->GetNickName(),channels[j].GetName()),fd);
// 	else
// 		_sendResponse(RPL_JOINMSG(GetClient(fd)->getHostname(),GetClient(fd)->getIpAdd(),token[i].first) + \
// 			RPL_TOPICIS(GetClient(fd)->GetNickName(),channels[j].GetName(),channels[j].GetTopicName()) + \
// 			RPL_NAMREPLY(GetClient(fd)->GetNickName(),channels[j].GetName(),channels[j].clientChannel_list()) + \
// 			RPL_ENDOFNAMES(GetClient(fd)->GetNickName(),channels[j].GetName()),fd);
//     channels[j].sendTo_all(RPL_JOINMSG(GetClient(fd)->getHostname(),GetClient(fd)->getIpAdd(),token[i].first), fd);
// }


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
                              const std::string& arguments, 
                              const std::string& clientList, 
                              const std::string& creationTime, 
                              const std::string& mode, 
                              const std::string& oldNickname, 
                              const std::string& topic) {
  std::string response;

  // Welcome message
  if (!nickname.empty() && hostname.empty() && ipaddress.empty()
  		&& channelname.empty() && arguments.empty() && clientList.empty()
		&& creationTime.empty() && mode.empty() && oldNickname.empty() && topic.empty())
    response += ": 001 " + nickname + " : Welcome to the IRC server!\n";

  // User mode info
  if (!hostname.empty() && !channelname.empty() && !mode.empty() && !arguments.empty())
    response += ":" + hostname + " MODE " + channelname + " " + mode + " " + arguments + "\n";

  // Channel creation time
  if (!nickname.empty() && !channelname.empty() && !creationTime.empty()) {
    response += ": 329 " + nickname + " #" + channelname + " " + creationTime + "\n";
  }

  // Channel modes
  if (!nickname.empty() && !channelname.empty() && !mode.empty()) {
    response += ": 324 " + nickname + " #" + channelname + " " + mode + "\n";
  }

  // Channel mode change
  if (!hostname.empty() && !channelname.empty() && !mode.empty() && !arguments.empty()) {
    response += ":" + hostname + " MODE #" + channelname + " " + mode + " " + arguments + "\n";
  }

  // Nick change
  if (!oldNickname.empty() && !nickname.empty()) {
    response += ":" + oldNickname + " NICK " + nickname + "\n";
  }

  // Join message
  if (!nickname.empty() && !hostname.empty() && !ipaddress.empty() && !channelname.empty()) {
    response += ":" + nickname + "!" + hostname + "@" + ipaddress + " JOIN #" + channelname + "\n";
  }

  // User list in channel reply
  if (!nickname.empty() && !channelname.empty() && !clientList.empty()) {
    response += ": 353 " + nickname + " @ #" + channelname + " :@" + clientList + "\n";
  }

  // End of names list
  if (!nickname.empty() && !channelname.empty()) {
    response += ": 366 " + nickname + " #" + channelname + " :END of /NAMES list" + "\n";
  }

  // Channel topic
  if (!nickname.empty() && !channelname.empty() && !topic.empty()) {
    response += ": 332 " + nickname + " #" + channelname + " :" + topic + "\r\n";
  }

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
		// std::vector<Channel *> invitations = getClient(fd)->getInvitedChannels();
		for (size_t y = 0; y < this->getClient(fd)->getInvitedChannels().size(); y++)
		{
			std::cout << RED << "channel ivited : " << getClient(fd)->getInvitedChannels()[y]->getName() << RESET << std::endl;
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
				// HANDLE EXISTING CHANNEL
				std::cout << "Channel " << tokens[i].first << " already exists" << std::endl;
				std::cout << "Channel " << tokens[i].first << " password: " << this->channels[x]->getPassword() << std::endl;
				std::cout << "tokens[i].second (password): " << tokens[i].second << std::endl;	
				if (!clientAlreadyInChannel(fd,channels[x]->getName() ))
				{
					if (!this->channels[x]->getPassword().empty() && this->channels[x]->getPassword() != tokens[i].second)
						std::cout << "Channel " << this->channels[x]->getName() << " password incorrect"  << std::endl;
					else if (this->channels[x]->getIsInviteOnly() && !clientIsInvited(fd, channels[x]))
						std::cout << "Channel " << this->channels[x]->getName() << " is invite only and " << this->getClient(fd)->getNickname() << " is not invited."  << std::endl;
					else if (this->channels[x]->getLimit() && this->channels[x]->getMembers().size() >= this->channels[x]->getLimit())
						std::cout << "Channel " << this->channels[x]->getName() << " limit is surpassed. Client " << this->getClient(fd)->getNickname() << " not allowed to join"  << std::endl;
					else
					{
						channels[x]->addMember(*client);
						this->sendMsg(fd,
							getServerResponse(client->getNickname(),
								client->getHostname(), client->getIpAddress(),
								channels[x]->getName(), "", this->getClientList(channels[x]), "", "", "", ""));
					}
				}
				else
					this->sendMsg(fd, "Client " + this->getClient(fd)->getNickname() + " is already in channel " + this->channels[x]->getName());
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
					client->getHostname(), client->getIpAddress(),
						newChannel->getName(), "", this->getClientList(newChannel), "", "", "", ""));
		}
	}
	
}