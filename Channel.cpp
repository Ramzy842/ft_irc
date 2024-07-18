/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:51 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/19 00:27:52 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Channel.hpp"

Channel::Channel() : name("Default")
{
	std::cout << "Channel constructor called" << std::endl;
}

Channel::Channel(std::string& name) : name(name)
{
	std::cout << "Channel parametrized constructor called" << std::endl;
}
Channel::~Channel()
{
	std::cout << "Channel destructor called" << std::endl;
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

std::vector <Client> Channel::getMembers() {
	return this->members;
}

std::vector <Client> Channel::getOperators() {
	return this->operators;
}

void Channel::addMember(Client& client) {
	this->members.push_back(client);
}

void Channel::addOperator(Client& client) {
	this->operators.push_back(client);
}

void Channel::removeMember(Client& client) {
	for (size_t i = 0; i < this->members.size(); i++) {
		if (this->members[i].getFd() == client.getFd()) {
			this->members.erase(this->members.begin() + i);
			return;
		}
	}
}

void Channel::removeOperator(Client& client) {
	for (size_t i = 0; i < this->operators.size(); i++) {
		if (this->operators[i].getFd() == client.getFd()) {
			this->operators.erase(this->operators.begin() + i);
			return;
		}
	}
}


void Channel::sendToMembers(std::string msg) {
	for (size_t i = 0; i < this->members.size(); i++) {
		this->members[i].sendMsgClient(msg);
	}
}

void Channel::sendToOperators(std::string msg) {
	for (size_t i = 0; i < this->operators.size(); i++) {
		this->operators[i].sendMsgClient(msg);
	}
}

void Channel::sendToAll(std::string msg) {
	this->sendToMembers(msg);
	this->sendToOperators(msg);
}


// void Channel::sendToAllExcept(std::string msg, int fd) {
// 	for (size_t i = 0; i < this->members.size(); i++) {
// 		if (this->members[i].getFd() != fd) {
// 			this->members[i].sendMsgClient(msg);
// 		}
// 	}
// 	for (size_t i = 0; i < this->operators.size(); i++) {
// 		if (this->operators[i].getFd() != fd) {
// 			this->operators[i].sendMsgClient(msg);
// 		}
// 	}
// }

// void Channel::sendToAllExcept(std::string msg, Client* client) {
// 	for (size_t i = 0; i < this->members.size(); i++) {
// 		if (this->members[i].getFd() != client->getFd()) {
// 			this->members[i].sendMsgClient(msg);
// 		}
// 	}
// 	for (size_t i = 0; i < this->operators.size(); i++) {
// 		if (this->operators[i].getFd() != client->getFd()) {
// 			this->operators[i].sendMsgClient(msg);
// 		}
// 	}
// }


// void Channel::sendToAllExcept(std::string msg, std::vector<Client*> clients) {
// 	for (size_t i = 0; i < this->members.size(); i++) {
// 		if (std::find(clients.begin(), clients.end(), this->members[i]) == clients.end()) {
// 			this->members[i].sendMsgClient(msg);
// 		}
// 	}
// 	for (size_t i = 0; i < this->operators.size(); i++) {
// 		if (std::find(clients.begin(), clients.end(), this->operators[i]) == clients.end()) {
// 			this->operators[i].sendMsgClient(msg);
// 		}
// 	}
// }

// void Channel::sendToAllExcept(std::string msg, std::vector<int> fds) {
// 	for (size_t i = 0; i < this->members.size(); i++) {
// 		if (std::find(fds.begin(), fds.end(), this->members[i].getFd()) == fds.end()) {
// 			this->members[i]->sendMsgClient(msg);
// 		}
// 	}
// 	for (size_t i = 0; i < this->operators.size(); i++) {
// 		if (std::find(fds.begin(), fds.end(), this->operators[i]->getFd()) == fds.end()) {
// 			this->operators[i]->sendMsgClient(msg);
// 		}
// 	}
// }


void Channel::setIsInviteOnly(bool _is_invite_only) {
	this->is_invite_only = _is_invite_only;
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

void Channel::setTopic(std::string _topic) {
	this->topic = _topic;
}


std::string Channel::getTopic() {
	return this->topic;
}



void Channel::setCreatedAt(std::string _created_at) {
	this->created_at = _created_at;
}


std::string Channel::getCreatedAt() {
	return this->created_at;
}

void Channel::setName(std::string _name) {
	this->name = _name;
}

Client * Channel::getMemberByName(std::string name) {
    for (size_t i = 0; i < this->members.size(); i++) {
        if (this->members[i].getNickname() == name) {
            return &this->members[i];
        }
    }
	return (NULL);
}
Client * Channel::getOperatorByName(std::string name) {
	for (size_t i = 0; i < this->operators.size(); i++) {
		if (this->operators[i].getNickname() == name) {
			return &this->operators[i];
		}
	}
	return NULL;
}

int Channel::getId()
{
	return this->id;
}

void Channel::setId(int _id)
{
	this->id = _id;
}

Client * Channel::getClientInChannel(std::string name)
{
	for (std::vector<Client>::iterator it = this-> members.begin(); it != this->members.end(); ++it){
		if (it->getNickname() == name)
			return &(*it);
	}
	for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it){
		if (it->getNickname() == name)
			return &(*it);
	}
	return NULL;
}

std::string Channel::clientChannel_list(){
	std::string list;
	for(size_t i = 0; i < operators.size(); i++){
		list += "@" + operators[i].getNickname();
		if((i + 1) < operators.size())
			list += " ";
	}
	if(this->members.size())
		list += " ";
	for(size_t i = 0; i < this->members.size(); i++){
		list += this->members[i].getNickname();
		if((i + 1) < this->members.size())
			list += " ";
	}
	return list;
}

int Channel::getLimit()
{
	return this->limit;
}