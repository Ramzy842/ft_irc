/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topoic.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:21:19 by yassine           #+#    #+#             */
/*   Updated: 2024/07/14 14:34:17 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cmd.hpp"

#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"
