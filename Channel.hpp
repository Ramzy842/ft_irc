/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:49 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/17 22:03:54 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "Client.hpp"

class Client;

class Channel {
	private:
		bool is_invite_only;
		int limit;
		int id;
		std::string name;
		std::string password;
		std::string topic;
		std::string init_time;
		std::vector<Client> operators;
		std::vector<Client> members;
		std::string created_at;
		
	public:
		Channel();
		Channel(std::string& name);
		~Channel();
		Channel(const Channel& original);
		Channel& operator=(const Channel& original);

		//******GETTERS AND SETTERS ******//
		void setId(int _id);
		int getId();
		std::string getName();
		void setName(std::string _name);
		std::string getPassword();
		void setPassword(std::string _password);
		std::string getTopic();
		void setTopic(std::string _topic);
		std::vector<Client> getOperators();
		void setOperators(std::vector<Client> _operators);
		std::vector<Client> getMembers();
		void setMembers(std::vector<Client> _members);
		std::string getCreatedAt();
		void setCreatedAt(std::string _created_at);
		bool getIsInviteOnly();
		void setIsInviteOnly(bool _is_invite_only);
		//***** METHODS *****//
		void addOperator(Client& client);
		void removeOperator(Client& client);
		void addMember(Client& client);
		void removeMember(Client& client);
		void sendToMembers(std::string msg);
		void sendToOperators(std::string msg);
		void sendToAll(std::string msg);
		void sendToAllExcept(std::string msg, int fd);
		void sendToAllExcept(std::string msg, Client client);
		void sendToAllExcept(std::string msg, std::vector<Client> clients);
		void sendToAllExcept(std::string msg, std::vector<int> fds);
		Client * getMemberByName(std::string name);
		Client * getOperatorByName(std::string name);
		Client * getClientInChannel(std::string name);
		std::string clientChannel_list();
		void removeChannel(Channel& channel);
		
};

#endif