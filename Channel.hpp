/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:49 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/07 06:15:57 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>

class Channel {
	private:
		int is_invite_only;
		std::string name;
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