/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:41 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/19 22:59:50 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "./irc_serv.hpp"
#include "./Channel.hpp"

class Channel;

class Client {
	private:
		std::string ip_address;
		int fd;
		bool isOperator;
		bool isRegistered;
		bool isLoggedin;
		bool isNickSet;
		std::string username;
		std::string nickname;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string buffer;
		std::vector<Channel *> channels;
		std::vector<Channel *> invitedChannels;
	public:
		Client();
		Client(const Client& original);
		Client& operator=(const Client& original);
		~Client();
		// GETTERS AND SETTERS
		int getFd();
		void setFd(int _fd);
		std::string getIpAddress();
		void setIpAddress(std::string _ipAddress);
		void setBuffer(std::string str);
		std::string getBuffer();
		void clearBuffer();
		void setIsLoggedIn();
		bool getIsLoggedIn();
		std::string getUsername();
		void setUsername(std::string _username);
		std::string getNickname();
		void setNickname(std::string _nickname);
		bool getIsOperator();
		void setIsOperator(bool _isOperator);
		bool getIsRegistered();
		void setIsRegistered(bool _isRegistered);
		void sendMsgClient(std::string msg);
		Client *getMembeByName(std::string name);
		void removeChannel(Channel& channel);
		std::vector<Channel>& getChannels();
		void setChannels(std::vector<Channel>& _channels);
		void addChannel(Channel& channel);
		void ckeckpass(std::string pass);
		void user(std::string &msg, int fd);
		void setHostname(std::string hostname);
		void setServername(std::string servername);
		void setRealname(std::string realname);
		std::string getHostname();
		bool getIsNickSet();
		void setIsNickSet(bool _isNickSet);
		std::vector<Channel *> getInvitedChannels();
		
};

#endif