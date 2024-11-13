/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AhttpTests.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:37:50 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 17:40:58 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include "../webserv/includes/Ahttp.hpp"

#include <stdio.h>

class ConcreteHttp : public Ahttp {
public:
	ConcreteHttp(int socketFD) : Ahttp(socketFD) {}
	ConcreteHttp() : Ahttp(0) {}
	~ConcreteHttp() {}
	
	
	std::string build() const override
	{
		return "build called";
	}
};

TEST(AhttpTests, BasicTests)
{
	Ahttp *http = new ConcreteHttp();
	Ahttp *http2 = new ConcreteHttp(10);
	ASSERT_NE(http, nullptr);
	ASSERT_NE(http2, nullptr);
	
	// Check socketFD set correctly
	ASSERT_EQ(http->getRecipient(), 0);	
	ASSERT_EQ(http2->getRecipient(), 10);

	// Check for proper overloading
	ASSERT_EQ(http->build(), "build called");

	// Check correct http versions
	ASSERT_EQ(http->getHttpVersion(), "");
	http->setHttpVersion("HTTP 1.1");
	ASSERT_EQ(http->getHttpVersion(), "HTTP 1.1");

	// Check message body
	ASSERT_EQ(http->getMessageBody(), "");
	http->setMessageBody("Hello");
	ASSERT_EQ(http->getMessageBody(), "Hello");

	// Check newline property
	ASSERT_EQ(http->getEndl(), "\n");
	// Set newline to just carriage return
	http->setEndl("\r");
	ASSERT_EQ(http->getEndl(), "\r");

	delete http;
	delete http2;
}

TEST(AhttpTests, ReadBodyFromFD)
{
	Ahttp *http = new ConcreteHttp();
	FILE *file = tmpfile();
	// Ensure file is actually open
	ASSERT_NE((void *)file, (void *)0);
	
	// Make sure body is empty
	ASSERT_EQ(http->getBodySize(), 0);
	ASSERT_EQ(http->getMessageBody(), "");
	std::string message = "Testing";
	ASSERT_EQ(write(file->_fileno, message.c_str(), message.size()), message.size());
	fclose(file);

	// Set file position pointer to beginning of temp file
	rewind(file);
	// Try reading into body
	http->readBody(file->_fileno);
	ASSERT_EQ(http->getBodySize(), message.size());
	ASSERT_EQ(http->getMessageBody(), message);

	http->setMessageBody("");
	// Try reading from an invalid fd
	ASSERT_NO_FATAL_FAILURE(http->readBody(100));
	ASSERT_EQ(http->getMessageBody(), "");
	int fds[2];
	ASSERT_EQ(pipe(fds), 0);
	// Try reading from the write end of a pipe
	ASSERT_NO_FATAL_FAILURE(http->readBody(fds[1]));
	ASSERT_EQ(http->getMessageBody(), "");
	close(fds[0]);
	close(fds[1]);
	// Try reading from a closed fd
	ASSERT_NO_FATAL_FAILURE(http->readBody(fds[0]));
	ASSERT_EQ(http->getMessageBody(), "");
	delete http;
}
