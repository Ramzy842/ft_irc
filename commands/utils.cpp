/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:07:22 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/14 04:55:53 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"

std::vector<std::string> split_command(std::string& msg)
{
	std::vector<std::string> cmd;
	std::string word = "";
	for (size_t i = 0; i < msg.size(); i++)
	{
		if (msg[i] == ' ')
		{
			cmd.push_back(word);
			word = "";
		}
		else
			word += msg[i];
	}
	cmd.push_back(word);
	return cmd;
}

void senderreur(int fd, std::string msg)
{
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
		std::cerr << "Failed to send message" << std::endl;
}

void sendMsg(int fd, std::string msg)
{
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
		std::cerr << "Failed to send message" << std::endl;
}