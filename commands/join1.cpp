/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:07:27 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/19 00:28:31 by yaidriss         ###   ########.fr       */
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
#define RPL_JOINMSG(hostname, ip, channel) (":" + hostname + "!" + ip + " JOIN " + channel + "\r\n")
#define RPL_NAMREPLY(nick, channel, names) (":" + nick + " = " + channel + " :" + names + "\r\n")
#define RPL_ENDOFNAMES(nick, channel) (":" + nick + " 366 " + channel + " :End of /NAMES list\r\n")



int Server::SplitJoin(std::vector<std::pair<std::string, std::string> > &token, std::string cmd, int fd) {
	(void)fd;
    std::vector<std::string> tmp;
    std::string ChStr, PassStr, buff;
    std::istringstream iss(cmd);
    while (iss >> cmd)
        tmp.push_back(cmd);
    if (tmp.size() < 2) {
        token.clear();
        return 0;
    }
    tmp.erase(tmp.begin());
    ChStr = tmp[0];
    tmp.erase(tmp.begin());
    if (!tmp.empty()) {
        PassStr = tmp[0];
        tmp.clear();
    }
    for (size_t i = 0; i < ChStr.size(); i++) {
        if (ChStr[i] == ',') {
            token.push_back(std::make_pair(buff, ""));
            buff.clear();
        } else
            buff += ChStr[i];
    }
    token.push_back(std::make_pair(buff, ""));
    if (!PassStr.empty()) {
        size_t j = 0;
        buff.clear();
        for (size_t i = 0; i < PassStr.size(); i++) {
            if (PassStr[i] == ',') {
                token[j].second = buff;
                j++;
                buff.clear();
            } else
                buff += PassStr[i];
        }
        token[j].second = buff;
    }
    for (size_t i = 0; i < token.size(); i++) { // erase the empty channel names
        if (token[i].first.empty())
            token.erase(token.begin() + i--);
    }
    return 1;
}

void Server::NotExistCh(std::vector<std::pair<std::string, std::string> > &token, int i, int fd) {
    if (getClientByName(getClient(fd)->getNickname())->getChannels().size() >= 10) { // ERR_TOOMANYCHANNELS (405)
        senderreur(fd, " :You have joined too many channels\r\n");
        return;
    }
    Channel newChannel;
    newChannel.setName(token[i].first);
    newChannel.addMember(*getClient(fd));
    newChannel.addOperator(*getClient(fd));
    this->channels.push_back(newChannel);
    sendResponse(RPL_JOINMSG(getClient(fd)->getHostname(), getClient(fd)->getIpAddress(), newChannel.getName()) +
                 RPL_NAMREPLY(getClient(fd)->getNickname(), newChannel.getName(), newChannel.clientChannel_list()) +
                 RPL_ENDOFNAMES(getClient(fd)->getNickname(), newChannel.getName()), fd);
}

void Server::ExistCh(std::vector<std::pair<std::string, std::string> > &token, int i, int j, int fd) {
    if (!token[i].second.empty() && this->channels[j].getPassword() != token[i].second) { // ERR_BADCHANNELKEY (475)
        senderreur(fd, " :Cannot join channel (Incorrect password)\r\n");
        return;
    }
    if (this->channels[j].getIsInviteOnly()) { // ERR_INVITEONLYCHAN (473)
        senderreur(fd, " :Cannot join channel (Invite only)\r\n");
        return;
    }
    if (this->channels[j].getMembers().size() >= (size_t)this->channels[j].getLimit()) { // ERR_CHANNELISFULL (471)
        senderreur(fd, " :Cannot join channel (Channel is full)\r\n");
        return;
    }
    this->channels[j].addMember(*getClient(fd));
    sendResponse(RPL_JOINMSG(getClient(fd)->getHostname(), getClient(fd)->getIpAddress(), this->channels[j].getName()) +
                 RPL_NAMREPLY(getClient(fd)->getNickname(), this->channels[j].getName(), this->channels[j].clientChannel_list()) +
                 RPL_ENDOFNAMES(getClient(fd)->getNickname(), this->channels[j].getName()), fd);
}

void Server::join1(std::string cmd, int fd) {
    std::vector<std::pair<std::string, std::string> > token;
    if (!SplitJoin(token, cmd, fd)) { // ERR_NEEDMOREPARAMS (461)
        senderreur(fd, " :Not enough parameters\r\n");
        return;
    }
    if (token.size() > 10) { // ERR_TOOMANYTARGETS (407)
        senderreur(fd, " :Too many channels\r\n");
        return;
    }
    for (size_t i = 0; i < token.size(); i++) {
        bool flag = false;
        for (size_t j = 0; j < this->channels.size(); j++) {
            if (this->channels[j].getName() == token[i].first) {
                ExistCh(token, i, j, fd);
                flag = true;
                break;
            }
        }
        if (!flag)
            NotExistCh(token, i, fd);
    }
    std::cout << "JOIN command is done: " << getClient(fd)->getNickname() << " joined channels." << std::endl;
}
