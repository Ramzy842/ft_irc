/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:43 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/14 14:30:12 by yassine          ###   ########.fr       */
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
		std::vector<Channel> channels;
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
		int getFd();
		void setFd(int _fd);
		std::string getPassword();
		void setPassword(std::string _password);
		std::vector<Client> getClients();
		void setClients(std::vector<Client> _clients);
		void AddToClients(Client& client);
		void removeClient(int _fd);
		void removeFd(int _fd);
		Client *getClient(int _fd);
		bool passwordsMatch(std::string _password);
		void cmd_parser(std::string &msg, int fd);
		Channel* getChannelByName(std::string name);
		Client* getClientByName(std::string nick);

		//****** IRC COMMANDS ******//
		void invite(std::string &msg, int fd);
		void topic(std::string &msg, int fd);
		Channel* inviteErreurHandler(std::vector<std::string> cmd, int fd);
		Channel* topicErreurHandler(std::vector<std::string> cmd, int fd);
		//****** utils funciton ******//
};

#endif