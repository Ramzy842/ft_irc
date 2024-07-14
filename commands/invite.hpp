/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassine <yassine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:25:55 by yassine           #+#    #+#             */
/*   Updated: 2024/07/14 12:41:43 by yassine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cmd.hpp"

#define ERR_NOTPARAMS "461 :Not enough parameters\n"
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel\n"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel\n"
#define ERR_USERALREADYINCHANNEL(channel) "443 " + channel + " :User is already on channel\n"
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator\n"
#define ERR_LOGIN "530 Please login with USER and PASS\n"