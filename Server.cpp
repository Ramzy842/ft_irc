/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/07 07:05:05 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"
#include <sys/types.h>

Server::Server() : port(3000), password("1234"), fd(-1), clients(std::vector<Client>())
{
	std::cout << "Server constructor called" << std::endl;
}

Server::Server(int port, std::string& password)
{
	this->port = port;
	this->password = password;
	this->clients = std::vector<Client>();
	this->fd = -1;
	std::cout << "Server parametrized constructor called" << std::endl;
}
Server::Server(const Server& original) : port(original.port), password(original.password), fd(-1), clients(original.clients)
{
	std::cout << "Server copy constructor called" << std::endl;
}
Server& Server::operator=(const Server& original)
{
	if (this != &original)
	{
		this->port = original.port;
		this->password = original.password;
		this->fd = original.fd;
		this->clients = original.clients;
	}
	std::cout << "Server copy assignment operator called" << std::endl;
	return *this;
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

// void performSocketOps()
// {	
// }

void Server::init() {
	std::cout << "Initializing server..." << std::endl;
	std::cout << "Server initialized" << std::endl;
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		std::cout << "Error: Couldn't create unbound socket!" << std::endl;
		return ;
	}
	else
	{
		setFd(serverSocket);
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(this->getPort());
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		int option_value = 1;
		if(fcntl(this->fd, F_SETFL, O_NONBLOCK) == -1)
		{
			std::cout << "Error: Couldn't set socket file descriptor mode to non-blocking!" << std::endl;
			return ;
		}
		if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) == -1)
		{
			std::cout << "Error: Couldn't set the socket options!" << std::endl;
			return ;
		}
		else if (bind(this->fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		{
			std::cout << "Error: Couldn't bind a name to the socket!" << std::endl;
			return ;
		}
		else if (listen(this->fd, SOMAXCONN) == -1)
		{
			std::cout << "Error: Couldn't listen for socket connections!" << std::endl;
			return ;
		}
		struct pollfd pfd;
		pfd.fd = this->fd;
		pfd.events = POLLIN;
		this->fds.push_back(pfd);
		while(1) {
			int clientSocket = accept(this->fd, NULL, NULL);
			char buffer[1024] = {0};
			int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (bytesReceived <= 0)
			{
				std::cout << "Client disconnected." << std::endl;
				return;
			}
			buffer[bytesReceived] = '\0';
			std::cout << buffer;
			close(clientSocket);
		}	
		close(this->fd);
	}
}


// GETTERS AND SETTERS
int Server::getPort() {
	return this->port;
}
void Server::setPort(int _port) {
	this->port = _port;
}
std::string Server::getPassword() {
	return this->password;
}
void Server::setPassword(std::string _password) {
	this->password = _password;
}
std::vector<Client> Server::getClients() {
	return this->clients;
}
void Server::setClients(std::vector<Client> _clients) {
	this->clients = _clients;
}

int Server::getFd() {
	return this->fd;
}
void Server::setFd(int _fd) {
	this->fd = _fd;
}