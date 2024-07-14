/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:14:06 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/14 15:49:03 by yassine          ###   ########.fr       */
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
    if (cmd.size() < 2)
    {
        senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
        return NULL;
    }
    Channel *channel = this->getChannelByName(cmd[1]);
    if(!channel)
    {
        senderreur(fd, ERR_NOSUCHCHANNEL(cmd[1]));
        return NULL;
    }
    Client *userToKick = channel->getMemberByName(cmd[2]);
    Clinet *isClient = this->getClientByName(cmd[2]);
    if(!userToKick || !isClient)
    {
        if(!userToKick)
            senderreur(fd, ERR_NOSUCHNICK(cmd[2]));
        else
            senderrur(fd, ERR_USERNOTINCHANNEL(cmd[2], cmd[1]));
        return NULL;
    }
    if(channel->getOperatorByName(this->getClientByFd(fd)->getNickname()))
    {
        senderreur(fd, ERR_CHANOPRIVSNEEDED(cmd[1]));
        return NULL;
    }
    
}


void Server::kick(std::string &msg, int fd)
{
    handlerkickcommand(std::vector<std::string> cmd, int fd);
}