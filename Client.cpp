/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:17:26 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/18 03:26:32 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Client.hpp"

Client::Client() : ip_address(""),  fd(-1), isOperator(false), isRegistered(false), isLoggedin(false), isNickSet(false)
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

void Client::setIsLoggedIn() {
	this->isLoggedin = true;
}

bool Client::getIsLoggedIn() {
	return this->isLoggedin;
}

std::string Client::getUsername() {
	return this->username;
}

void Client::setUsername(std::string _username) {
	this->username = _username;
}

std::string Client::getNickname() {
	return this->nickname;
}

void Client::setNickname(std::string _nickname) {
	this->nickname = _nickname;
}

bool Client::getIsOperator() {
	return this->isOperator;
}

void Client::setIsOperator(bool _isOperator) {
	this->isOperator = _isOperator;
}

bool Client::getIsRegistered() {
	return this->isRegistered;
}

void Client::setIsRegistered(bool _isRegistered) {
	this->isRegistered = _isRegistered;
}

void Client::sendMsgClient(std::string msg) {
	send(this->fd, msg.c_str(), msg.length(), 0);
}

//! comment because Channel is not used yet 
std::vector<Channel>& Client::getChannels() {
	return this->channels;
}


void Client::setChannels(std::vector<Channel>& _channels) {
	this->channels = _channels;
}


void Client::addChannel(Channel& channel) {
	this->channels.push_back(channel);
}

void Client::removeChannel(Channel& channel) {
	for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if (it->getName() == channel.getName())
		{
			this->channels.erase(it);
			break;
		}
	}
}

void Client::setHostname(std::string _hostname) {
	this->hostname = _hostname;
}

void Client::setServername(std::string _servername) {
	this->servername = _servername;
}

void Client::setRealname(std::string _realname) {
	this->realname = _realname;
}

std::string Client::getHostname(){
	return this->hostname;
}

bool Client::getIsNickSet() {
	return this->isNickSet;
}

void Client::setIsNickSet(bool _isNickSet) {
	this->isNickSet = _isNickSet;
}