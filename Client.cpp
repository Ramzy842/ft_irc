/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:26 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/04 16:52:27 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Client.hpp"

Client::Client() : ip_address("")
{
	std::cout << "Client constructor called" << std::endl;
}
Client::Client(const Client& original) : ip_address(original.ip_address)
{
	std::cout << "Client copy constructor called" << std::endl;
}
Client& Client::operator=(const Client& original) {
	if (this != &original)
		this->ip_address = original.ip_address;
	return *this;
	std::cout << "Client copy assignment operator called" << std::endl;
}

Client::~Client() {
	std::cout << "Client destructor called" << std::endl;
}

int getFd();
void setFd();
std::string getIpAddress();
void setIpAddress();