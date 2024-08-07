/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:14:06 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 07:46:43 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

// Error message macros
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
#define ERR_NOSUCHNICK(nick) "401 " + nick + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(nick, channel) "441 " + nick + " " + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"


Channel *Server::handlerkickcommand(std::vector<std::string> cmd, int fd)
{
    Channel *channel = this->getChannelByName(cmd[1].substr(1));
    if(!channel)
    {
        senderreur(fd, ERR_NOSUCHCHANNEL(cmd[2]));
        return NULL;
    }
    Client *userToKick = channel->getMemberByName(cmd[2]);
    Client *isClient = this->getClientByName(cmd[2]);
    if(!userToKick || !isClient)
    {
        if(!userToKick)
            senderreur(fd, ERR_NOSUCHNICK(cmd[2]));
        else
            senderreur(fd, ERR_USERNOTINCHANNEL(cmd[2], cmd[1]));
        return NULL;
    }
    if(!channel->getOperatorByName(this->getClient(fd)->getNickname()))
    {
        senderreur(fd, ERR_CHANOPRIVSNEEDED(cmd[1]));
        return NULL;
    }
    return channel;    
}


void Server::kick(std::string &msg, int fd)
{
    std::vector<std::string> cmd = split_command(msg);
    Channel* channel = handlerkickcommand(cmd,fd);
    if(!channel)
        return;
    std::string msj = ":" + this->getClient(fd)->getNickname() + "!~" + this->getClient(fd)->getHostname() + "@localhost KICK " + cmd[1] + " " + cmd[2];
    if(channel->getOperatorByName(cmd[2]))
      channel->removeOperator(*channel->getOperatorByName(cmd[2]));
    channel->removeMember(*channel->getMemberByName(cmd[2]));
    this->getClientByName(cmd[2])->removeChannel(*channel);
    for(size_t i = 0; i < channel->getMembers().size(); i++)
            sendMsg(channel->getMembers()[i]->getFd(), msj);
    sendMsg(getClientByName(cmd[2])->getFd(), msj);
}