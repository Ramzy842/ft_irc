/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 00:21:00 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/13 01:42:59 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

void cmd::invite(std::string &msg, int fd)
{
	std::string channel = msg.substr(6);
	if (channel.empty())
	{
		send(fd, "461 Not enough parameters.\n", 27, 0);
		// return;
	}
	if (channel.find(" ") != std::string::npos)
	{
		send(fd, "461 Not enough parameters.\n", 27, 0);
		// return;
	}
	if (channel[0] != '#')
	{
		send(fd, "403 No such channel.\n", 21, 0);
		// return;
	}
	// if (this->users[fd].is_logged == false)
	// {
	// 	send(fd, "530 Please login with USER and PASS.\n", 37, 0);
	// 	return;
	// }
	// if (this->channels.find(channel) == this->channels.end())
	// {
	// 	send(fd, "403 No such channel.\n", 21, 0);
	// 	return;
	// }
	// if (this->channels[channel].users.find(this->users[fd].username) == this->channels[channel].users.end())
	// {
	// 	send(fd, "442 You're not on that channel.\n", 31, 0);
	// 	return;
	// }
	// std::string user = msg.substr(msg.find(" ", 7) + 1);
	// if (user.empty())
	// {
	// 	send(fd, "461 Not enough parameters.\n", 27, 0);
	// 	return;
	// }
	// if (user.find(" ") != std::string::npos)
	// {
	// 	send(fd, "461 Not enough parameters.\n", 27, 0);
	// 	return;
	// }
	// if (this->users.find(user) == this->users.end())
	// {
	// 	send(fd, "401 No such nick.\n", 18, 0);
	// 	return;
	// }
	// if (this->channels[channel].users.find(user) != this->channels[channel].users.end())
	// {
	// 	send(fd, "443 User is already on channel.\n", 31, 0);
	// 	return;
	// }
	// this->channels[channel].users.insert(user);
	// send(fd, "341 User has been invited.\n", 27, 0);
}