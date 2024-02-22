/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponseTests.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:17:59 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 18:11:51 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <fcntl.h>

#include "../webserv/includes/HttpResponse.hpp"

TEST(HttpResponseTests, StatusCodeGeneration)
{
	HttpResponse response(0);

	ASSERT_EQ(response.getStatusCode(), 0);
        ASSERT_EQ(response.getReasonPhrase(), "No Status");
        response.setStatusCode(200);
        ASSERT_EQ(response.getStatusCode(), 200);
        ASSERT_EQ(response.getReasonPhrase(), "OK");
}

TEST(HttpResponseTests, BuildTest)
{
        HttpResponse response(0);

        response.setStatusCode(200);
        response.setHttpVersion("HTTP 1.1");
        response.setHeader("Hello", "hello");
        response.setMessageBody("Testing testing");
        ASSERT_EQ(response.build(), "HTTP 1.1 200 OK\nhello:hello\n\nTesting testing");
}