/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:07:27 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/18 11:24:56 by rchahban         ###   ########.fr       */
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
	for (size_t i = 0; i < tokens.size(); i++) //erase the empty channel names
		{if (tokens[i].first.empty())tokens.erase(tokens.begin() + i--);}
	for (size_t i = 0; i < tokens.size(); i++){ //ERR_NOSUCHCHANNEL (403) // if the channel doesn't exist
		if (*(tokens[i].first.begin()) != '#')
			{sendError(403, this->getClient(fd)->getNickname(), tokens[i].first, this->getClient(fd)->getFd(), " :No such channel\r\n"); tokens.erase(tokens.begin() + i--);}
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

// void Server::createChannel(int fd, std::vector<std::pair<std::string, std::string> >&tokens,int x)
// {
// 	Channel newChannel;
// 	newChannel.setName(tokens[x].first);
// 	newChannel.addOperator(*this->getClient(fd));
// 	// newChannel.set_createiontime();
// 	this->channels.push_back(newChannel);
// }

int Server::getClientsNumberInChannel(std::string channelName)
{
	for (size_t x = 0; x < this->channels.size(); x++){
		if (this->channels[x].getName() == channelName)
			return this->channels[x].getMembers().size();
	}
	return 0;
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
  if (!hostname.empty() && !ipaddress.empty() && !channelname.empty()) {
    response += ":" + hostname + "@" + ipaddress + " JOIN #" + channelname + "\n";
  }

  // User list in channel reply
  if (!nickname.empty() && !channelname.empty() && !clientList.empty()) {
    response += ": 353 " + nickname + " @ #" + channelname + " :" + clientList + "\n";
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



// void Server::handleNonExistingChannel(std::vector<std::pair<std::string, std::string> >&tokens, int i, int fd)
// {
// 	(void) fd;
// 	// std::cout << "test test "<< std::endl;
// 	// if (SearchForClients(this->getClient(fd)->getNickname()) >= 10)//ERR_TOOMANYCHANNELS (405) // if the client is already in 10 channels
// 	// {
// 	// 	sendError(405, this->getClient(fd)->getNickname(), this->getClient(fd)->getFd(), " :You have joined too many channels\r\n");
// 	// 	return;
// 	// }
// 	std::cout << "test test 2"<< std::endl;
// 	std::cout << "hello World :" << tokens[i].first << std::endl;
// 	Channel newChannel;
// 	newChannel.setName(tokens[i].first);
// 	// std::cout << tokens[i].first << std::endl;
// 	// newChannel.setName(tokens[i].first); 
// 	std::cout << "test:" << newChannel.getName() << "and i :"<< i << std::endl;
// 	// std::cout << "Channel name:" << newChannel.getName() << std::endl;
// 	// newChannel.addOperator(*this->getClient(fd));
// 	// newChannel.set_createiontime();
// 	this->channels.push_back(newChannel);
// 	// this->channels[i].setName(tokens[i].first);
// 	if (channels.size() > 0)
// 	{
// 		std::cout << "Channels size: " << channels[i].getName() << std::endl;
// 		std::cout << "Channel test:" << channels[i].getName().empty() << std::endl;	
// 	}

// 	// for (size_t x = 0; x < channels.size(); x++)
// 	// {
// 	// 	std::cout << "Channel name: " <<  this->channels[x].getName() << std::endl;
// 	// }
// 	// notifiy that the client joined the channel
// 	// sendResponse(getServerResponse(getClient(fd)->getNickname(), getClient(fd)->getHostname(), getClient(fd)->getIpAddress(),
// 	// 	newChannel.getName(),"", newChannel.clientChannel_list(), "", "", "", ""), fd);
	
// }

// void Server::handleExistingChannel(std::vector<std::pair<std::string, std::string> >&tokens, int i, int fd)
// {
	
// }

// bool Server::clientAlreadyInChannel(std::string channelName, int fd) {
// 	for (size_t x = 0; x < this->channels.size(); x++){
// 		if (this->channels[x].getM == channelName)
// 			return this->channels[x].getMembers().size();
// 	}
// }

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
	// TESTING
	Channel newChannel1;
	channels.push_back(newChannel1);
	channels[channels.size() - 1].setName("Test1");
	channels[channels.size() - 1].addOperator(*this->getClient(fd));
	Client c1;
	c1.setFd(2000);
	Client c2;
	c1.setFd(2001);
	Client c3;
	c1.setFd(2002);
	Client c4;
	c1.setFd(2003);
	Client c5;
	c1.setFd(2004);
	this->channels[channels.size() - 1].addMember(c1);
	this->channels[channels.size() - 1].addMember(c2);
	this->channels[channels.size() - 1].addMember(c3);
	this->channels[channels.size() - 1].addMember(c4);
	this->channels[channels.size() - 1].addMember(c5);
	std::cout << "Number of users in Test1: " << getClientsNumberInChannel("Test1") << std::endl;
	// TESTING
	for (size_t i = 0; i < tokens.size(); i++)
	{
		bool foundChannel = false;
		for (size_t x = 0; x < channels.size(); x++)
		{
			if (channels[x].getName() == tokens[i].first)
			{
				std::cout << "Channel " << tokens[i].first << " already exists" << std::endl;
				foundChannel = true;
				break ;
			}
		}
		// HANDLE NON EXISTING CHANNEL
		if (!foundChannel)
		{
			Channel newChannel;
			channels.push_back(newChannel);
			channels[channels.size() - 1].setName(tokens[i].first);
			channels[channels.size() - 1].addOperator(*this->getClient(fd));
			std::cout << "sizeof operators: " << channels[channels.size() - 1].getOperators().size() << std::endl;
		}
	}
	
}