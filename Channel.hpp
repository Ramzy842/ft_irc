/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:49 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/07 19:47:48 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include "./Client.hpp"

class Channel {
	private:
		int is_invite_only;
		std::string name;
		std::string password;
		std::string topic;
		// std::vector<Client*> operators;
		// std::vector<Client*> members;
		std::string created_at;
		
	public:
		Channel();
		Channel(std::string& name);
		~Channel();
		Channel(const Channel& original);
		Channel& operator=(const Channel& original);

		// GETTERS AND SETTERS
		void setId();
		int getId();
		std::string getName();
		void setName();
};

#endif