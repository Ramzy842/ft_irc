/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:52:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/05/29 21:20:58 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_serv.hpp"

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
	std::cout << port << std::endl;
	std::cout << password << std::endl;
	return (0);
}