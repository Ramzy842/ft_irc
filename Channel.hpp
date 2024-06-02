/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:49 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/02 20:05:40 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>

class Channel {
	private:
		std::string name;
	public:
		Channel();
		Channel(std::string& name);
		~Channel();
		Channel(const Channel& original);
		Channel& operator=(const Channel& original);
};

#endif