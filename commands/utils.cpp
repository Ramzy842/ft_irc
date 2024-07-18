/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:07:22 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/18 03:33:24 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
//! ADD other parammetres number of params to set last words in one string 
std::vector<std::string> split_command(std::string& msg) // , int parm )
{
	std::vector<std::string> cmd;
	std::string word = "";
	for (size_t i = 0; i < msg.size(); i++)
	{
		if (msg[i] == ' ') //* && parm > i);
		{
			cmd.push_back(word);
			word = "";
		}
		else
			word += msg[i];
	}
	word = word.substr(0, word.size() - 1);
	cmd.push_back(word);
	return cmd;
}

Channel *senderreur(int fd, std::string msg)
{
	msg = RED + msg + RESET + "\n";
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
		std::cerr << RED << "Failed to send message" << RESET << std::endl;
	return (NULL);
}

void sendMsg(int fd, std::string msg)
{
	msg = GREEN + msg + RESET + "\n";
	int failedsend = send(fd, msg.c_str(), msg.size(), 0);
	if (failedsend == -1)
		std::cerr << RED << "Failed to send message" << RESET << std::endl;
}


bool isEmpyCmd(std::vector<std::string> cmd)
{
	for (size_t i = 1; i < cmd.size(); i++)
	{
		if (!cmd[i].empty())
			return false;
	}
	return true;
}