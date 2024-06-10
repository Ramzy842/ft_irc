/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:52:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/10 18:16:43 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_serv.hpp"
#include "./Server.hpp"

int	main (int argc, char **argv)
{
	
	if (argc != 3)
	{
		std::cout << "\e[1;31mUsage: ./ircserv <port> <password>\e[0m" << std::endl;
		return (1);
	}
	int port;
	std::string password;
	port = static_cast<int>(std::strtod(argv[1], NULL));
	password = argv[2];
	Server ser(port, password);
	// std::cout << "Server Port: " << ser.getPort() << std::endl;
	// std::cout << "Server Password: " << ser.getPassword() << std::endl;
	ser.init();
	return (0);
}