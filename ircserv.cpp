/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:52:18 by rchahban          #+#    #+#             */
/*   Updated: 2024/07/20 20:53:17 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "irc_serv.hpp"
#include "./Server.hpp"

bool isPortValid(std::string Port){
	return (Port.find_first_not_of("0123456789") == std::string::npos && \
	std::atoi(Port.c_str()) >= 1024 && std::atoi(Port.c_str()) <= 65535);
}

int	main (int argc, char **argv)
{
	
	if (argc != 3)
	{
		std::cout << "\e[1;31mUsage: ./ircserv <port> <password>\e[0m" << std::endl;
		return (1);
	}
	int port;
	std::string password;
	if(!isPortValid(argv[1]) || std::strlen(argv[2]) > 10)
	{
		std::cout << "\e[1;31minvalid Port number / Password!\e[0m" << std::endl;
		return 1;
	}
	port = static_cast<int>(std::strtod(argv[1], NULL));
	password = argv[2];
	Server ser(port, password);
	try {
		// signal(SIGINT, Server::handleSignal);
		// signal(SIGQUIT, Server::handleSignal);
		ser.init();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Server Shut Down!" << std::endl;
	return (0);
}