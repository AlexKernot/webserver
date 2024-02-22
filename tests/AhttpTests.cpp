/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AhttpTests.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:37:50 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 18:00:47 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include "../webserv/includes/Ahttp.hpp"

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