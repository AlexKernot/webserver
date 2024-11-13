/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ahttp.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:04:46 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 17:34:38 by akernot          ###   ########.fr       */
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

int Ahttp::getBodySize() const
{
        return messageBody.size();
}

void Ahttp::readBody(const int fd)
{
        static const int bufferSize = 1028;
        char *buffer = new char[bufferSize];

        while (true) {
                int bytesRead = read(fd, buffer, bufferSize);
                if (bytesRead == -1)
                        break;
                messageBody += buffer;
                if (bytesRead < bufferSize)
                        break;
        }
        delete[] buffer;
}

void Ahttp::readBody(std::istream& file)
{
        while (file.eof() == false) {
                std::string line;
                file >> line;
                messageBody += line;
        }
}
