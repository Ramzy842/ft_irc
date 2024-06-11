/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:43 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/11 19:45:03 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "./irc_serv.hpp"
#include "./Client.hpp"

class Server {
	private:
		int port;
		std::string password;
		int fd;
		std::vector<Client> clients;
		std::vector<struct pollfd> fds;
	public:
		Server();
		Server(int port, std::string& password);
		Server(const Server& original);
		Server& operator=(const Server& original);
		~Server();
		void init();
		// GETTERS AND SETTERS
		int getPort();
		void setPort(int _port);
		std::string getPassword();
		void setPassword(std::string _password);
		std::vector<Client> getClients();
		void setClients(std::vector<Client> _clients);
		int getFd();
		void setFd(int _fd);
		void AddToClients(Client& client);
		void removeClient(int _fd);
		void removeFd(int _fd);
		Client *getClient(int _fd);
		bool passwordsMatch(std::string _password);
};

#endif