/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:08:41 by rchahban          #+#    #+#             */
/*   Updated: 2024/05/29 22:15:06 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "./irc_serv.hpp"

class Client {
	private:
		std::string ip_address;
	public:
		Client();
		Client(const Client& original);
		Client& operator=(const Client& original);
		~Client();
};

#endif