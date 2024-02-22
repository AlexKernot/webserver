/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ahttp.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:04:46 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 18:02:18 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ahttp.hpp"

#include <unistd.h>
#include <string>

Ahttp::Ahttp(int FD)
{
	this->socketFD = FD;
        encoding = "\n";
}

Ahttp::~Ahttp() 
{
        close(socketFD);
}

int Ahttp::getRecipient() const
{
        return socketFD;
}

void Ahttp::setHttpVersion(std::string version)
{
        httpVersion = version;
}

std::string Ahttp::getHttpVersion() const
{
        return httpVersion;
}

void Ahttp::setMessageBody(const std::string body)
{
	messageBody = body;
}

std::string Ahttp::getMessageBody() const
{
	return messageBody;
}

std::string Ahttp::getEndl() const
{
        return encoding;
}

void Ahttp::setEndl(std::string endl)
{
        encoding = endl;
}
