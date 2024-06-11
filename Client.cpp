/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:26 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Client.hpp"

Client::Client() : ip_address(""),  fd(-1), isOperator(false)
{
}
Client::Client(const Client& original) : ip_address(original.ip_address),  fd(original.fd), isOperator(original.isOperator)
{
}
Client& Client::operator=(const Client& original) {
	if (this != &original)
	{  
		this->ip_address = original.ip_address;
		this->fd = original.fd;
		this->isOperator = original.isOperator;
	}
	return *this;
}

Client::~Client() {
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

void Client::setBuffer(std::string str) {
	this->buffer = str;
}
std::string Client::getBuffer() {
	return this->buffer;
}

void Client::clearBuffer() {
	this->buffer.clear();
}