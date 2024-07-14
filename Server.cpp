/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/14 04:48:19 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"
// #include <sys/types.h>

Server::Server() : port(3000), password("1234"), fd(-1), clients(std::vector<Client>())
{
}

Server::Server(int port, std::string& password)
{
	this->port = port;
	this->password = password;
	this->clients = std::vector<Client>();
	this->fd = -1;
}
Server::Server(const Server& original) : port(original.port), password(original.password), fd(-1), clients(original.clients)
{
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
	return *this;
}

Server::~Server()
{
}


void Server::init() {
	std::cout << "Initializing server..." << std::endl;
	std::cout << "Server initialized" << std::endl;
	Client client;
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
			if((poll(&fds[0],fds.size(),-1) == -1)) //-> wait for an event
				throw(std::runtime_error("poll() faild"));
			for (unsigned int x = 0; x < this->fds.size(); x++)
			{
				if (fds[x].revents && fds[x].revents == POLLIN)
				{
					if (fds[x].fd == this->fd)
					{
						std::cout << "New Clients wants to connect" << std::endl;
						
						struct sockaddr_in client_addr;
    					socklen_t addr_size;
						addr_size = sizeof(client_addr);
						int clientSocket = accept(this->fd, (sockaddr *)&client_addr, &addr_size);
						if(fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
						{
							std::cout << "Error: Couldn't set socket file descriptor mode to non-blocking!" << std::endl;
							return ;
						}
						struct pollfd client_fd;
						client_fd.fd = clientSocket;
						client_fd.events = POLLIN;
						client_fd.revents = 0;
						client.setFd(clientSocket);
						client.setIpAddress(inet_ntoa(client_addr.sin_addr));
						AddToClients(client);
						this->fds.push_back(client_fd);
						std::cout << "New connection! Socket fd: " << this->fd << ", client fd: " << clientSocket << std::endl;
					}
					else
					{
						char buff[1024];
						memset(buff, 0, sizeof(buff));
					
						ssize_t receivedBytes = recv(fds[x].fd, buff, sizeof(buff) , 0);
					
						if(receivedBytes <= 0) {
							std::cout << "Client disconnected." << std::endl;
							// ClearClients(fd); //-> clear the client
							close(fd); //-> close the client socket
						}
					
						else {
							buff[receivedBytes] = '\0';
							std::cout << "Client <" << fds[x].fd << "> and ip address <" << client.getIpAddress() << "> Data: " << buff;
							// Add code to process the received data: parse, check, authenticate, handle the command, etc...
						}
					}
				}
			}
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
// std::vector<Client> Server::getClients() {
// 	return this->clients;
// }
// void Server::setClients(std::vector<Client> _clients) {
// 	this->clients = _clients;
// }

int Server::getFd() {
	return this->fd;
}
void Server::setFd(int _fd) {
	this->fd = _fd;
}

void Server::AddToClients(Client& client) {
	this->clients.push_back(client);
}

Channel* Server::getChannelByName(std::string name) {
	for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if (it->getName() == name)
			return &(*it);
	}
	return NULL;
}

Client* Server::getClientByName(std::string name) {
	for (std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (it->getNickname() == name)
			return &(*it);
	}
	return NULL;
}