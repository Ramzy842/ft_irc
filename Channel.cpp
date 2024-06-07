/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:52:51 by rchahban          #+#    #+#             */
/*   Updated: 2024/06/07 06:55:28 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Channel.hpp"

Channel::Channel() : name("Default")
{
	std::cout << "Channel constructor called" << std::endl;
}

Channel::Channel(std::string& name) : name(name)
{
	std::cout << "Channel parametrized constructor called" << std::endl;
}
Channel::~Channel()
{
	std::cout << "Channel destructor called" << std::endl;
}
Channel::Channel(const Channel& original) {
	(void) original;
	std::cout << "Channel copy constructor called" << std::endl;
}

Channel& Channel::operator=(const Channel& original) {
	(void) original;
	std::cout << "Channel copy assignment operator called" << std::endl;
	return *this;
}