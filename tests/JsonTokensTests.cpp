/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonTokensTests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:02:40 by akernot           #+#    #+#             */
/*   Updated: 2024/06/12 18:41:14 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include "../webserv/includes/json/JsonArray.hpp"
#include "../webserv/includes/json/JsonObject.hpp"
#include "../webserv/includes/json/JsonValue.hpp"
#include "../webserv/includes/json/JsonToken.hpp"
#include "../webserv/includes/json/JsonExceptions.hpp"

TEST(JsonTokenTests, jsonToken)
{
	JsonToken nothing;
	ASSERT_EQ(nothing.getKey(), "");
	
	JsonToken token("key");
	ASSERT_EQ(token.getKey(), "key");
	JsonToken token2(token);
	ASSERT_EQ(token.getKey(), token2.getKey());
	JsonToken token3 = token;
	ASSERT_EQ(token.getKey(), token3.getKey());
}

TEST(JsonTokensTests, jsonValue)
{
	JsonValue value("key", "pair");
	ASSERT_EQ(value.getKey(), "key");
	ASSERT_EQ(value.getValue(), "pair");
	JsonValue value2(value);
	ASSERT_EQ(value.getKey(), value2.getKey());
	ASSERT_EQ(value.getValue(), value2.getKey());
	
	JsonValue value3 = value;
	ASSERT_EQ(value.getKey(), value3.getKey());
	ASSERT_EQ(value.getValue(), value3.getValue());
}

TEST(JsonTokenTests, jsonArray)
{
	JsonArray arr("array");
	ASSERT_EQ(arr.getKey(), "array");
	ASSERT_THROW(arr.getValue(0), std::out_of_range);
	ASSERT_TRUE(arr.empty());
	ASSERT_EQ(arr.size(), 0);
	arr.push_back("one");
	ASSERT_EQ(arr.getValue(0), "one");
	ASSERT_THROW(arr.getArray(0), JsonTypeException);
	ASSERT_THROW(arr.getObject(0), JsonTypeException);
	arr.push_back("two");
	arr.push_back("three");
	arr.push_back("four");
	arr.push_back("five");
	ASSERT_EQ(arr.size(), 5);
	ASSERT_EQ(arr.getValue(1), "two");
	ASSERT_EQ(arr.getValue(2), "three");
	ASSERT_EQ(arr.getValue(3), "four");
	ASSERT_EQ(arr.getValue(4), "five");
	ASSERT_THROW(arr.getValue(5), std::out_of_range);
	ASSERT_THROW(arr.getValue(10000000), std::out_of_range);
	ASSERT_THROW(arr.getValue((std::size_t)-1), std::out_of_range);

	// copy constructor
	JsonArray arrCopy(arr);
	ASSERT_EQ(arr.size(), arrCopy.size());
	// checks for deep copies by asserting the return addresses aren't equal
	// but the values of the strings are.
	for (std::size_t i = 0; i < arr.size(); ++i)
	{
		ASSERT_NE(&arr.getValue(i), &arrCopy.getValue(i));
		ASSERT_EQ(arr.getValue(i), arrCopy.getValue(i));
	}

	// operator=
	JsonArray arrCopy2 = arr;
	ASSERT_EQ(arr.size(), arrCopy2.size());
	for (std::size_t i = 0; i < arr.size(); ++i)
	{
		ASSERT_NE(&arr.getValue(i), &arrCopy2.getValue(i));
		ASSERT_EQ(arr.getValue(i), arrCopy2.getValue(i));
	}

	JsonObject* obj = new JsonObject("obj");
	arr.push_back(obj);
	ASSERT_EQ(arr.size(), 6);
	ASSERT_NO_THROW(arr.getObject(5));
	ASSERT_THROW(arr.getValue(5), JsonTypeException);
	ASSERT_THROW(arr.getArray(5), JsonTypeException);
}

TEST(JsonTokenTests, jsonObject)
{
	JsonObject noKey;
	ASSERT_EQ(noKey.getKey(), "");
	ASSERT_TRUE(noKey.empty());
	
	JsonObject obj("obj");
	ASSERT_TRUE(obj.empty());
	JsonValue* val1 = new JsonValue("one", "valOne");
	JsonValue* val2 = new JsonValue("two", "valTwo");
	JsonValue* val3 = new JsonValue("three", "valThree");
	JsonValue* val4 = new JsonValue("four", "valFour");
	
	JsonValue* val5 = new JsonValue("inner", "a");
	JsonObject* val6 = new JsonObject("outer");
	{
		JsonObject obj2;
		val6->addChild(val5);
		obj2.addChild(val6);
	}
	// make sure the values are freed.
	ASSERT_DEATH(val6->empty(), 0);
	ASSERT_DEATH(val5->getKey(), 0);
}
