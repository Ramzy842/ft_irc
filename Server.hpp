/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:43 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/13 05:48:27 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "./irc_serv.hpp"
#include "./Client.hpp"


#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"


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
		void cmd_parser(std::string &msg, int fd);
		void topic(std::string &msj, int fd);
};

#endif