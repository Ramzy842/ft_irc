/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:41 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/11 19:49:04 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "./irc_serv.hpp"
#include "./Channel.hpp"

class Client {
	private:
		std::string ip_address;
		int fd;
		bool isOperator;
		// bool isRegistered;
		bool isLoggedin;
		std::string username;
		std::string nickname;
		std::string buffer;
		// std::vector<Channel*> Channels;
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
};

#endif