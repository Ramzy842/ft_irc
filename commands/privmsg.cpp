/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:44:07 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/23 01:48:18 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./cmd.hpp"

// Error message macros
// #define ERR_NOTEXTTOSEND "412 :No text to send"
// #define ERR_CANNOTSENDTOCHAN(channel) "404 " + channel + " :Cannot send to channel"
// #define ERR_NOSUCHNICK(nick) "401 " + nick + " :No such nick/channel"
// #define ERR_NOTOPLEVEL(mask) "413 " + mask + " :No toplevel domain specified"
// #define ERR_WILDTOPLEVEL(mask) "414 " + mask + " :Wildcard in toplevel domain"
// #define ERR_TOOMANYTARGETS(target) "407 " + target + " :Too many recipients"

// void Server::privmsg(std::string &msg, int fd) {
// 	std::vector<std::string>cmd = split_command(msg);
// 	if (cmd.size() < 3)
// 	{
// 		senderreur(fd, " 411 PRIVMSG :No recipient given");
// 		return;
// 	}
// 	if (cmd[1][0] != '#') {
// 		Client *client = getClientByName(cmd[1]);
// 		if (!client)
// 		{
// 			senderreur(fd, ERR_NOSUCHNICK(cmd[1]));
// 			return;
// 		}
// 		std::string message = cmd[2];
// 		for (size_t i = 3; i < cmd.size(); i++)
// 			message += " " + cmd[i];
// 		std::string resp = ":" + getClient(fd)->getNickname() + "!~" + getClient(fd)->getUsername() + "@localhost PRIVMSG #" + cmd[1] + " :" + message + "\r\n";
// 		sendMsg(client->getFd(), resp);
// 	}
// 	else {
// 		Channel *channel = getChannelByName(cmd[1].substr(1));
// 		if (!channel)
// 		{
// 			senderreur(fd, ERR_CANNOTSENDTOCHAN(cmd[1]));
// 			return;
// 		}
// 		std::string message = cmd[2];
// 		for (size_t i = 3; i < cmd.size(); i++)
// 			message += " " + cmd[i];
// 		for (size_t i = 0; i < channel->getMembers().size(); i++)
// 			sendMsg(channel->getMembers()[i]->getFd(), "PRIVMSG " + channel->getName() + " :" + message);
// 	}
	
// }

#include "./cmd.hpp"

// Error message macros
#define ERR_NOTEXTTOSEND "412 :No text to send"
#define ERR_CANNOTSENDTOCHAN(channel) "404 " + channel + " :Cannot send to channel"
#define ERR_NOSUCHNICK(nick) "401 " + nick + " :No such nick/channel"
#define ERR_NOTOPLEVEL(mask) "413 " + mask + " :No toplevel domain specified"
#define ERR_WILDTOPLEVEL(mask) "414 " + mask + " :Wildcard in toplevel domain"
#define ERR_TOOMANYTARGETS(target) "407 " + target + " :Too many recipients"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"

void Server::privmsg(std::string &msg, int fd) {
    std::vector<std::string> cmd = split_command(msg);
    if (cmd.size() < 3) {
        senderreur(fd, " 411 PRIVMSG :No recipient given");
        return;
    }

    // Get the message text, ensuring to include everything after the third token
    std::string message = cmd[2];
    for (size_t i = 3; i < cmd.size(); ++i) {
        message += " " + cmd[i];
    }

    if (message.empty()) {
        senderreur(fd, ERR_NOTEXTTOSEND);
        return;
    }

    if (cmd[1][0] != '#') {
        Client *client = getClientByName(cmd[1]);
        if (!client) {
            senderreur(fd, ERR_NOSUCHNICK(cmd[1]));
            return;
        }
        std::string resp = ":" + getClient(fd)->getNickname() + "!~" + getClient(fd)->getUsername() + "@localhost PRIVMSG " + cmd[1] + " :" + message;
        sendMsg(client->getFd(), resp);
    } else {
        Channel *channel = getChannelByName(cmd[1].substr(1));
        if (!channel) {
            senderreur(fd, ERR_CANNOTSENDTOCHAN(cmd[1]));
            return;
        }
        Client *client = getClient(fd);
        if(!channel->getMemberByName(client->getNickname()))
        {
            senderreur(fd, ERR_NOTONCHANNEL(cmd[1]));
            return;
        }
        std::string sender = ":" + getClient(fd)->getNickname() + "!~" + getClient(fd)->getUsername() + "@localhost PRIVMSG " + cmd[1] + " :" + message;
        for (size_t i = 0; i < channel->getMembers().size(); ++i) {
            if (channel->getMembers()[i]->getFd() != fd) { // Don't send the message to the sender
                sendMsg(channel->getMembers()[i]->getFd(), sender);
            }
        }
    }
}
