/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:41 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/14 17:49:14 by yaidriss         ###   ########.fr       */
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
		std::string username;
		std::string nickname;
		std::string buffer;
		std::vector<Channel *> channels;
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
		void removeChannel(Channel* channel);
		std::vector<Channel*> getChannels();
		void setChannels(std::vector<Channel*> _channels);
		void addChannel(Channel* channel);
		
};

#endif