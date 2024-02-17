#include <gtest/gtest.h>

#include "../webserv/includes/HttpFactory.hpp"

// This is a little unessecary
TEST(HttpFactoryTests, CheckAllStatusMessages)
{
	ASSERT_EQ(HttpFactory::generateReasonPhrase(100), "Continue");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(101), "Switching Protocols");

	ASSERT_EQ(HttpFactory::generateReasonPhrase(200), "OK");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(201), "Created");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(202), "Accepted");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(203), "Non-Authoritative Information");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(204), "No Content");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(205), "Reset Content");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(206), "Partial Content");

	ASSERT_EQ(HttpFactory::generateReasonPhrase(300), "Multiple Choices");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(301), "Moved Permanently");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(302), "Found");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(303), "See Other");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(304), "Not Modified");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(305), "Use Proxy");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(306), "Unused");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(307), "Temporary Redirect");

	ASSERT_EQ(HttpFactory::generateReasonPhrase(400), "Bad Request");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(401), "Unauthorized");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(402), "Payment Required");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(403), "Forbidden");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(404), "Not Found");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(405), "Method Not Allowed");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(406), "Not Acceptable");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(407), "Proxy Authentication Required");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(408), "Request Timeout");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(409), "Conflict");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(410), "Gone");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(411), "Length Required");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(412), "Precondition Failed");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(413), "Request Entity Too Large");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(415), "Unsupported Media Type");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(416), "Range Not Satisfiable");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(417), "Expectation Failed");

	ASSERT_EQ(HttpFactory::generateReasonPhrase(500), "Internal Server Error");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(501), "Not Implemented");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(502), "Bad Gateway");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(503), "Service Unavailable");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(504), "Gateway Timeout");
	ASSERT_EQ(HttpFactory::generateReasonPhrase(505), "HTTP Version Not Supported");
}
