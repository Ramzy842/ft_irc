/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/05/31 19:43:57 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

Server::Server() : port(3000), password("1234")
{
	std::cout << "Server constructor called" << std::endl;
}

Server::Server(int port, std::string& password)
{
	this->port = port;
	this->password = password;
	this->clients = std::vector<Client>();
	std::cout << "Server parametrized constructor called" << std::endl;
}
Server::Server(const Server& original) : port(original.port), password(original.password), clients(original.clients)
{
	std::cout << "Server copy constructor called" << std::endl;
}
Server& Server::operator=(const Server& original)
{
	if (this != &original)
	{
		this->port = original.port;
		this->password = original.password;
		this->clients = original.clients;
	}
	std::cout << "Server copy assignment operator called" << std::endl;
	return *this;
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

void Server::init() {
	std::cout << "Initializing server..." << std::endl;
	std::cout << "Server initialized" << std::endl;
} 