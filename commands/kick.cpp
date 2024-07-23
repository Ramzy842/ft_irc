/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:14:06 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/23 01:32:26 by yaidriss         ###   ########.fr       */
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

// class Client;

Channel *Server::handlerkickcommand(std::vector<std::string> cmd, int fd)
{
    // if (cmd.size() < 2 )//|| !isEmpyCmd(cmd))
    // {
    //     senderreur(fd, ERR_NEEDMOREPARAMS(cmd[0]));
    //     return NULL;
    // }
	std::cout << "cmd :" << cmd[1] << cmd[2] << std::endl;
    Channel *channel = this->getChannelByName(cmd[1].substr(1));
    if(!channel)
    {
        senderreur(fd, ERR_NOSUCHCHANNEL(cmd[1]));
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
    channel->removeMember(*channel->getMemberByName(cmd[2]));
    std::string msj = ":" + this->getClient(fd)->getNickname() + "!~" + this->getClient(fd)->getHostname() + "@localhost KICK " + cmd[1] + " " + cmd[2];
    for(size_t i = 0; i < channel->getMembers().size(); i++)
    {
        // if(channel->getMembers()[i]->getFd() != fd)
            sendMsg(channel->getMembers()[i]->getFd(), msj);
    }
    if(channel->getOperatorByName(cmd[2]))
    {
      channel->removeOperator(*channel->getOperatorByName(cmd[2]));
    }
    //channel->removeMember(*channel->getMemberByName(cmd[2])); 
    this->getClientByName(cmd[2])->removeChannel(*channel);
    sendMsg(getClientByName(cmd[2])->getFd(), msj);


    // if(cmd.size() == 3)
    //     kickmsg += "\n";
    // else
    // {
    //     kickmsg += " :";
    //     for(size_t i = 3; i < cmd.size(); i++)
    //         kickmsg += cmd[i] + " ";
    //     kickmsg += "\n";
    // }
    // for (size_t i = 0; i < channel->getMembers().size(); i++)
    // {
    //     if(channel->getMembers()[i]->getFd() != fd)
    //         sendMsg(channel->getMembers()[i]->getFd(), msg);
    // }
    // sendMsg(fd, msj);
}