/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:25:19 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/13 01:38:38 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

void Server::topic(std::string &msj, int fd)
{
	std::string channel = msj.substr(6);
	if (channel.empty())
	{
		send(fd, "461 Not enough parameters.\n", 27, 0);
		return;
	}
	if (channel.find(" ") != std::string::npos)
	{
		send(fd, "461 Not enough parameters.\n", 27, 0);
		return;
	}
	if (channel[0] != '#')
	{
		send(fd, "403 No such channel.\n", 21, 0);
		return;
	}
	// if (this->clients[fd].getIsLoggedIn() == false)
	// {
	// 	send(fd, "530 Please login with USER and PASS.\n", 37, 0);
	// 	return;
	// }
}