/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:43 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/20 00:50:57 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "./irc_serv.hpp"
#include "./Client.hpp"
#include "./Channel.hpp"

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
		std::vector<Client *> clients;
		std::vector<Channel *> channels;
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
		int getClientsNumberInChannel(std::string channelName);
		bool clientAlreadyInChannel(int fd, std::string channelName);
		bool clientIsInvited(int fd);

		//****** IRC COMMANDS ******//
		void invite(std::string &msg, int fd);
		void topic(std::string &msg, int fd);
		void kick(std::string &msg, int fd);
		void mode(std::string &msg, int fd);
		void nick(std::string &msg, int fd);
		void pass(std::string &msg, int fd);
		void user(std::string &msg, int fd);
		void join(std::string &msg, int fd);
		void privmsg(std::string &msg, int fd);
		Channel* inviteErreurHandler(std::vector<std::string> cmd, int fd);
		Channel* topicErreurHandler(std::vector<std::string> cmd, int fd);
		Channel* handlerkickcommand(std::vector<std::string> cmd, int fd);
		Channel* handlermodecommand(std::vector<std::string> cmd, int fd);
		bool handlerpasscommand(std::vector<std::string> cmd, int fd);	
		bool handlernickcommand(std::vector<std::string> cmd, int fd);
		bool checkpass(std::string pass);
		void handleNonExistingChannel(std::vector<std::pair<std::string, std::string> >&token, int i, int fd);
		void createChannel(int fd, std::vector<std::pair<std::string, std::string> >&tokens, int x);
		//****** utils funciton ******//
		int splitJoinArgs(std::vector<std::pair<std::string, std::string> >& tokens, std::string msg, int fd);
		void sendError(int code, std::string clientName, std::string channelName, int fd, std::string msg);
		void sendError(int code, std::string clientname, int fd, std::string msg);
		void sendResponse(std::string response, int fd);
		int SearchForClients(std::string nickName);
		void quit(std::string &msg, int fd);
};

#endif