/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenConnection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:54:52 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 22:15:01 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenConnection.hpp"

#include "HttpFactory.hpp"

#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

OpenConnection::OpenConnection(int fd) : FdStream(fd) {  }

void OpenConnection::sendResponse(Ahttp* response)
{
	try {
		std::string toSend = response->build();
		send(fd, toSend.c_str(), toSend.size(), 0);
	} catch (const std::bad_alloc&) {
		// If the response is too big or there isnt enough memory for it
		// return the default server error response. This shouldn't use much
		// extra memory, only needing a function call and pointer
		std::string *serverError = HttpFactory::outOfMemory();
		send(fd, serverError->c_str(), serverError->size(), 0);
		return;
	}
}

AHttpRequest* OpenConnection::receiveRequest()
{
	std::string line = readLine();
	AHttpRequest *request;
	request = HttpFactory::constructRequest(line);
	while(true) {
		line = readLine();
		if (line == "\n")
			break;
		std::size_t seperator = line.find(':');
		std::string name = line.substr(0, seperator - 1);
		std::string value = line.substr(seperator + 1);
		request->setHeader(name, value);
		name.pop_back();
	}
	request->setMessageBody(readLine());
	request->readBody(fd);
	return request;
}

void OpenConnection::reject() {
	send(fd, HttpFactory::outOfMemory()->c_str(), HttpFactory::outOfMemory()->size(), 0);
}

OpenConnection::~OpenConnection() {
	close(fd);
}