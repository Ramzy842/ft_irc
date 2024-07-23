/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:51 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/23 06:42:17 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Channel.hpp"

Channel::Channel()
{
	is_invite_only = false;
	limit = 0,
	name = "";
	password = "";
	topic = "";
	init_time = "";
	created_at = "";
	std::cout << "Channel constructor called" << std::endl;
}

Channel::Channel(std::string name)
{
	is_invite_only = false;
	limit = 0,
	this->name = name;
	password = "";
	topic = "";
	init_time = "";
	created_at = "";
}
Channel::~Channel()
{

}
Channel::Channel(const Channel& original) {
	(void) original;
	std::cout << "Channel copy constructor called" << std::endl;
}

Channel& Channel::operator=(const Channel& original) {
	(void) original;
	std::cout << "Channel copy assignment operator called" << std::endl;
	return *this;
}

std::string Channel::getName() {
	return this->name;
}


std::vector <Client *> Channel::getMembers() {
	return this->members;
}

std::vector <Client *> Channel::getOperators() {
	return this->operators;
}

void Channel::addMember(Client& client) {
	this->members.push_back(&client);
}

void Channel::addOperator(Client& client) {
	this->operators.push_back(&client);
}

void Channel::removeMember(Client& client) {
	for (size_t i = 0; i < this->members.size(); i++) {
		if (this->members[i]->getFd() == client.getFd()) {
			this->members.erase(this->members.begin() + i);
			return;
		}
	}
}

void Channel::removeOperator(Client& client) {
	for (size_t i = 0; i < this->operators.size(); i++) {
		if (this->operators[i]->getFd() == client.getFd()) {
			this->operators.erase(this->operators.begin() + i);
			return;
		}
	}
}


void Channel::sendToMembers(std::string msg) {
	for (size_t i = 0; i < this->members.size(); i++) {
		this->members[i]->sendMsgClient(msg);
	}
}

void Channel::sendToOperators(std::string msg) {
	for (size_t i = 0; i < this->operators.size(); i++) {
		this->operators[i]->sendMsgClient(msg);
	}
}

void Channel::sendToAll(std::string msg) {
	this->sendToMembers(msg);
	this->sendToOperators(msg);
}


size_t Channel::getLimit() {
	return this->limit;
}
void Channel::setLimit(size_t value) {
	this->limit = value;
}

void Channel::setIsInviteOnly(bool is_invite_only) {
	this->is_invite_only = is_invite_only;
}

bool Channel::getIsInviteOnly() {
	return this->is_invite_only;
}

void Channel::setPassword(std::string _password) {
	this->password = _password;
}

std::string Channel::getPassword() {
	return this->password;
}

void Channel::setTopic(std::string topic) {
	this->topic = topic;
}


std::string Channel::getTopic() {
	return this->topic;
}


void Channel::setCreatedAt(std::string created_at) {
	this->created_at = created_at;
}


std::string Channel::getCreatedAt() {
	return this->created_at;
}

void Channel::setName(const std::string& newName) {
	this->name = newName;
}

Client * Channel::getMemberByName(std::string name) {
    for (size_t i = 0; i < this->members.size(); i++) {
        if (this->members[i]->getNickname() == name) {
            return this->members[i];
        }
    }
	return (NULL);
}
Client * Channel::getOperatorByName(std::string name) {
	for (size_t i = 0; i < this->operators.size(); i++) {
		if (this->operators[i]->getNickname() == name) {
			return this->operators[i];
		}
	}
	return NULL;
}


Client * Channel::getClientInChannel(std::string name)
{
	for (std::vector<Client *>::iterator it = this->members.begin(); it != this->members.end(); ++it){
		if ((*it)->getNickname() == name)
			return (*it);
	}
	for (std::vector<Client *>::iterator it = operators.begin(); it != operators.end(); ++it){
		if ((*it)->getNickname() == name)
			return (*it);
	}
	return NULL;
}



std::string Channel::clientChannel_list(){
	std::string list;
	for(size_t i = 0; i < operators.size(); i++){
		list += "@" + operators[i]->getNickname();
		if((i + 1) < operators.size())
			list += " ";
	}
	if(this->members.size())
		list += " ";
	for(size_t i = 0; i < this->members.size(); i++){
		list += this->members[i]->getNickname();
		if((i + 1) < this->members.size())
			list += " ";
	}
	return list;
}

void Channel::setIsTopic(bool is_topic) {
	this->is_topic = is_topic;
}

bool Channel::getIsTopic() {
	return this->is_topic;
}