/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:07:22 by yaidriss          #+#    #+#             */
/*   Updated: 2024/07/13 21:16:36 by yaidriss         ###   ########.fr       */
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
