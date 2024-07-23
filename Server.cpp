/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/23 01:28:59 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

Server::Server() : port(3000), password("1234"), fd(-1)
{
}

Server::Server(int port, std::string& password)
{
	this->port = port;
	this->password = password;
	this->fd = -1;
}
Server::Server(const Server& original) : port(original.port), password(original.password), fd(-1), clients(original.clients)
{
	signal = original.signal;
}
Server& Server::operator=(const Server& original)
{
	if (this != &original)
	{
		this->port = original.port;
		this->password = original.password;
		this->fd = original.fd;
		this->clients = original.clients;
		this->signal = false;
	}
	return *this;
}

Server::~Server()
{
}
bool Server::signal = false;
void Server::handleSignal(int signum)
{
	(void)signum;
	std::cout << "Signal Received!" << std::endl;
	signal = true;
}

void Server::displayChannels() 
{
	if (!this->channels.size())
	{
		std::cout << "No channels yet." << std::endl;
		return ;
	}
	std::cout << "Channels:" << std::endl;
	for (size_t x = 0; x < this->channels.size(); x++)
	{
		for (size_t y = 0; y < this->channels[x]->getMembers().size(); y++)
		{
			std::vector<Client *> members_ = this->channels[x]->getMembers();
			std::cout << "Channel: " << this->channels[x]->getName() << " has user (" << members_[y]->getFd() << ")" << std::endl;
		}
	}
}

void Server::displayInvitedChannels() 
{
	if (!this->channels.size())
		return ;
	std::cout << "Invited Channels:" << std::endl;
	for (size_t x = 0; x < this->clients.size(); x++)
	{
		for (size_t y = 0; y < this->clients[x]->getInvitedChannels().size(); y++)
		{
			std::vector<Channel *> invitedChannels = this->clients[x]->getInvitedChannels();
			std::cout << "Client <" << this->clients[x]->getNickname() << "> is invited to Channel <" << invitedChannels[y]->getName() << ">" << std::endl;
		}
	}
}


std::string trim(std::string &str)
{
    std::string whitespace = " \t";
    size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";

    size_t strEnd = str.find_last_not_of(whitespace);
    size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

void Server::init() {
	std::cout << CYAN << "Initializing server..." << std::endl;
	std::cout << GREEN <<"Server initialized" << RESET << std::endl;
	
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		std::cout << RED << "Error: Couldn't create unbound socket!" << std::endl;
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
			std::cout << RED << "Error: Couldn't set socket file descriptor mode to non-blocking!" << std::endl;
			return ;
		}
		if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) == -1)
		{
			std::cout << RED << "Error: Couldn't set the socket options!" << std::endl;
			return ;
		}
		else if (bind(this->fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		{
			std::cout << RED << "Error: Couldn't bind a name to the socket!" << std::endl;
			return ;
		}
		else if (listen(this->fd, SOMAXCONN) == -1)
		{
			std::cout << RED << "Error: Couldn't listen for socket connections!" << std::endl;
			return ;
		}
		struct pollfd pfd;
		pfd.fd = this->fd;
		pfd.events = POLLIN;
		this->fds.push_back(pfd);
		
		while(!signal)
		{
			if((poll(&fds[0],fds.size(),-1) == -1))
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
						if (clientSocket == -1)
						{
							std::cout << "accept() failed" << std::endl;
							return;
						}
						if(fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
						{
							std::cout << RED << "Error: Couldn't set socket file descriptor mode to non-blocking!" << std::endl;
							return ;
						}
						struct pollfd client_fd;
						client_fd.fd = clientSocket;
						client_fd.events = POLLIN;
						client_fd.revents = 0;
						Client *client = new Client();
						client->setFd(clientSocket);
						client->setIpAddress(inet_ntoa(client_addr.sin_addr));
						AddToClients(*client);
						this->fds.push_back(client_fd);
						std::cout << YELLOW <<"New connection! " << "Client fd <" << clientSocket << ">" << std::endl;
					}
					else
					{
						char buff[1024] = {0};
						memset(buff, 0, sizeof(buff));
						ssize_t receivedBytes = recv(fds[x].fd, buff, sizeof(buff), 0);
						if(receivedBytes <= 0)
						{
							removeClient(fds[x].fd);
							removeFd(fds[x].fd);
						}
						else
						{
							std::string buff_str(buff);
							cmd_parser(buff_str, fds[x].fd);
							displayChannels();
							std::cout << "------------------------------------------------" <<std::endl;
							displayInvitedChannels();
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


Client* Server::getClient(int _fd) {
	for (std::vector<Client *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if ((*it)->getFd() == _fd)
			return (*it);
	}
	return NULL;
}

int Server::getFd() {
	return this->fd;
}
void Server::setFd(int _fd) {
	this->fd = _fd;
}

void Server::AddToClients(Client& client) {
	this->clients.push_back(&client);
}

Channel* Server::getChannelByName(std::string name) {
	for (std::vector<Channel *>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if ((*it)->getName() == name)
			return *it;
	}
	return NULL;
}

Client* Server::getClientByName(std::string name) {
	for (std::vector<Client *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if ((*it)->getNickname() == name)
			return (*it);
	}
	return NULL;
}

void Server::removeClient(int _fd) {
	for (std::vector<Client *>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if ((*it)->getFd() == _fd)
		{
			this->clients.erase(it);
			break;
		}
	}
}

bool Server::checkpass(std::string _pass)
{
	if (_pass == this->getPassword())
		return true;
	return false;
}

void Server::sendResponse(std::string response, int fd)
{
	if(send(fd, response.c_str(), response.size(), 0) == -1)
		std::cerr << "Response send() failed" << std::endl;
}

void Server::removeFd(int _fd)
{
	for (std::vector<struct pollfd>::iterator it = this->fds.begin(); it != this->fds.end(); ++it)
	{
		if ((*it).fd == _fd)
		{
			this->fds.erase(it);
			break;
		}
	}
}