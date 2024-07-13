/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:49 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/13 21:08:14 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "./Client.hpp"

class Channel {
	private:
		bool is_invite_only;
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