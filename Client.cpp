/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:26 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/05 21:20:39 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Client.hpp"

Client::Client() : ip_address(""),  fd(-1), isOperator(false)
{
	std::cout << "Client constructor called" << std::endl;
}
Client::Client(const Client& original) : ip_address(original.ip_address),  fd(original.fd), isOperator(original.isOperator)
{
	std::cout << "Client copy constructor called" << std::endl;
}
Client& Client::operator=(const Client& original) {
	if (this != &original)
	{  
		this->ip_address = original.ip_address;
		this->fd = original.fd;
		this->isOperator = original.isOperator;
	}
	return *this;
	std::cout << "Client copy assignment operator called" << std::endl;
}

Client::~Client() {
	std::cout << "Client destructor called" << std::endl;
}

int Client::getFd() {
	return this->fd;
}
void Client::setFd(int _fd) {
	this->fd = _fd;
}
std::string Client::getIpAddress() {
	return this->ip_address;
}
void Client::setIpAddress(std::string _ipAddress) {
	this->ip_address = _ipAddress;
}