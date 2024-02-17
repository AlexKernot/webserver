#include <gtest/gtest.h>

#include "../webserv/includes/Ahttp.hpp"
#include "../webserv/includes/HttpRequest.hpp"
#include "../webserv/includes/HttpResponse.hpp"

/*class MockAhttp : public Ahttp {
public:
	MOCK_METHOD(std::string, build, (), (const override));
};

using namespace ::testing;*/

TEST(HttpHeaderTests, ToLower)
{
	HttpHeaders headers;

	// toLower
	std::string str = "ABZza";
	str = headers.toLower(str);
	ASSERT_EQ(str, "abzza");
	str = "@don't TOUCH-the***Symbols\n";
	str = headers.toLower(str);
	ASSERT_EQ(str, "@don't touch-the***symbols\n");
}

TEST(HttpHeaderTests, ValidateName)
{
	HttpHeaders headers;
	
	// validateName
	ASSERT_TRUE(headers.validateName("valid-name"));
	ASSERT_TRUE(headers.validateName("validname"));
	ASSERT_FALSE(headers.validateName("Not-Valid"));
	ASSERT_FALSE(headers.validateName("NotValid"));
	ASSERT_FALSE(headers.validateName("not valid"));
	ASSERT_FALSE(headers.validateName("not@valid"));
	ASSERT_FALSE(headers.validateName(""));
	ASSERT_FALSE(headers.validateName("......."));
}

TEST(HttpHeaderTests, Construction)
{
	HttpHeaders headers;

	// Check no values
	ASSERT_EQ(headers.getHeader("empty"), "");
	ASSERT_EQ(headers.getHeader(""), "");
	ASSERT_EQ(headers.constructHeaders(), "");
}

TEST(HttpHeaderTests, BasicInsertFind)
{
	HttpHeaders headers;

	// Basic insert and check
	headers.setHeader("a", "b");
	ASSERT_EQ(headers.getHeader("a"), "b");
	// Headers should be case insensitive
	headers.setHeader("B", "c");
	ASSERT_EQ(headers.getHeader("b"), "c");
	ASSERT_EQ(headers.getHeader("B"), "c");
	// Check headers overwrite
	headers.setHeader("A", "c");
	ASSERT_EQ(headers.getHeader("a"), "c");
	// Check non-existing header
	ASSERT_EQ(headers.getHeader("C"), "");
	// Check header construction
	std::string result = headers.constructHeaders();
	ASSERT_EQ(result, "a:c\nb:c\n");
}

TEST(HttpHeaderTests, InvalidName)
{
	HttpHeaders headers;

	// Check exception on invalid name
	ASSERT_THROW(headers.setHeader("", "a"), HttpHeaders::InvalidHeaderException);
	ASSERT_THROW(headers.setHeader("a&a", "a"), HttpHeaders::InvalidHeaderException);
	ASSERT_THROW(headers.setHeader("aA:", "a"), HttpHeaders::InvalidHeaderException);
	ASSERT_THROW(headers.setHeader("$$@", "a"), HttpHeaders::InvalidHeaderException);
	ASSERT_NO_THROW(headers.setHeader("Valid", "@Still-Valid@"));
}

TEST(HttpHeaderTests, TooLong)
{
	HttpHeaders headers;

	// Value too long
	std::string value;
	value.resize(8191, 'a');
	ASSERT_THROW(headers.setHeader(value, "a"), HttpHeaders::HeaderTooLongException);
	ASSERT_THROW(headers.setHeader("$$@", value), HttpHeaders::HeaderTooLongException);
	value.resize(8189, 'a');
	ASSERT_NO_THROW(headers.setHeader(value, "a"));
	ASSERT_NO_THROW(headers.setHeader("a", value));
}

TEST(HttpHeaderTests, TooMany)
{
	HttpHeaders headers;

	// Too many values
	std::string insert = "a";
	for (int i = 0; i < 100; ++i) {
		ASSERT_NO_THROW(headers.setHeader(insert, "a"));
		insert += "a";
	}
	ASSERT_THROW(headers.setHeader("Too-many", "a"), HttpHeaders::TooManyHeadersException);
}
