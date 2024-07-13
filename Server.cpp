/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/13 05:51:58 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"
// #include <sys/types.h>
#include <cstring>

Server::Server() : port(3000), password("1234"), fd(-1), clients(std::vector<Client>())
{
}

Server::Server(int port, std::string &password)
{
	this->port = port;
	this->password = password;
	this->clients = std::vector<Client>();
	this->fd = -1;
}
Server::Server(const Server &original) : port(original.port), password(original.password), fd(-1), clients(original.clients)
{
}
Server &Server::operator=(const Server &original)
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

void Server::init()
{
	std::cout << YELLOW <<"Initializing server..." << std::endl;
	std::cout << CYAN << "Server initialized" << std::endl;
	Client new_client;
	std::string buffer;
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cout << "Error: Couldn't create unbound socket!" << std::endl;
		return;
	}
	else
	{
		setFd(serverSocket);
		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(this->getPort());
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		int option_value = 1;
		if (fcntl(this->fd, F_SETFL, O_NONBLOCK) == -1)
		{
			std::cout << "Error: Couldn't set socket file descriptor mode to non-blocking!" << std::endl;
			return;
		}
		if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) == -1)
		{
			std::cout << "Error: Couldn't set the socket options!" << std::endl;
			return;
		}
		else if (bind(this->fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
		{
			std::cout << "Error: Couldn't bind a name to the socket!" << std::endl;
			return;
		}
		else if (listen(this->fd, SOMAXCONN) == -1)
		{
			std::cout << "Error: Couldn't listen for socket connections!" << std::endl;
			return;
		}
		struct pollfd pfd;
		pfd.fd = this->fd;
		pfd.events = POLLIN;
		this->fds.push_back(pfd);

		while (1)
		{
			if ((poll(&fds[0], fds.size(), POLLIN | POLLHUP) == -1)) //-> wait for an event
				throw(std::runtime_error("poll() faild"));
			for (unsigned int x = 0; x < this->fds.size(); x++)
			{
				if (fds[x].revents && POLLIN)
				{
					if (fds[x].fd == this->fd)
					{
						struct sockaddr_in client_addr;
						socklen_t addr_size;
						addr_size = sizeof(client_addr);
						int clientSocket = accept(this->fd, (sockaddr *)&client_addr, &addr_size);
						if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
						{
							std::cout << "Error: Couldn't set socket file descriptor mode to non-blocking!" << std::endl;
							return;
						}
						struct pollfd client_fd;
						client_fd.fd = clientSocket;
						client_fd.events = POLLIN;
						client_fd.revents = 0;
						new_client.setFd(clientSocket);
						new_client.setIpAddress(inet_ntoa(client_addr.sin_addr));
						AddToClients(new_client);
						this->fds.push_back(client_fd);
						std::cout << GREEN << "New connection! Socket fd: " << this->fd << ", client fd: " << clientSocket << RESET << std::endl;
					}
					else
					{
						char buff[1024];
						memset(buff, 0, sizeof(buff));
						Client *client = getClient(fds[x].fd);
						ssize_t receivedBytes = recv(fds[x].fd, buff, sizeof(buff), 0);
						if (receivedBytes <= 0)
						{
							std::cout << RED <<"closed connection by client <" << fds[x].fd << ">" << std::endl;
							removeClient(fds[x].fd);
							removeFd(fds[x].fd);
						}
						else
						{
							client->setBuffer(buff);
							if (client->getBuffer()[0] == 'p'
								&& client->getBuffer()[1] == 'a'
								&& client->getBuffer()[2] == 's'
								&& client->getBuffer()[3] == 's'
							)
							{
								std::cout << "enter password.." << std::endl;
								client->setIsLoggedIn();
							}
							// std::cout << "Client <" << fds[x].fd << ">: " << client->getBuffer();
							if (client)
							buffer = client->getBuffer();
							this->cmd_parser(buffer, fds[x].fd);
							// Add code to process the received data: parse, check, authenticate, handle the command, etc...
						}
					}

				}
			}
		}

		for (unsigned int x = 0; x < this->clients.size();  x++)
		{
			close(this->clients[x].getFd());
		}
	}
}



bool Server::passwordsMatch(std::string _password)
{
	return (this->password == _password);
}

Client *Server::getClient(int _fd)
{
	for (unsigned int x = 0; x < this->clients.size(); x++)
	{
		if (this->clients[x].getFd() == _fd)
			return &this->clients[x];
	}
	return NULL;
}

void Server::removeFd(int _fd)
{
	for (unsigned int x = 0; x < this->fds.size(); x++)
	{
		if (this->fds[x].fd == _fd)
		{
			this->fds.erase(this->fds.begin() + x);
			return ;
		}
	}
}

void Server::removeClient(int _fd)
{
	for (unsigned int x = 0; x < this->clients.size(); x++)
	{
		if (this->clients[x].getFd() == _fd)
		{
			this->clients.erase(this->clients.begin() + x);
			return ;
		}
	}
}

// GETTERS AND SETTERS
int Server::getPort()
{
	return this->port;
}
void Server::setPort(int _port)
{
	this->port = _port;
}
std::string Server::getPassword()
{
	return this->password;
}
void Server::setPassword(std::string _password)
{
	this->password = _password;
}

int Server::getFd()
{
	return this->fd;
}
void Server::setFd(int _fd)
{
	this->fd = _fd;
}

void Server::AddToClients(Client &client)
{
	this->clients.push_back(client);
}

std::vector<Client> Server::getClients()
{
	return this->clients;
}
