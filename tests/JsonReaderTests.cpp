/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonReaderTests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:48:01 by akernot           #+#    #+#             */
/*   Updated: 2024/06/11 20:06:48 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

#include <sstream>
#include <fstream>
#include <cstdio>

#include "../webserv/includes/json/JsonReader.hpp"
#include "../webserv/includes/json/JsonToken.hpp"
#include "../webserv/includes/json/JsonValue.hpp"
#include "../webserv/includes/json/JsonExceptions.hpp"
#include "../webserv/includes/json/JsonArray.hpp"
#include "../webserv/includes/json/JsonObject.hpp"

TEST(JsonReaderTests, jsonReaderCreation)
{
	// Try read from invalid file
	std::ifstream a;
	JsonReader jsonReader(a);
	JsonObject* res = jsonReader.read();
	ASSERT_EQ(res, nullptr);

	// Try read from closed file
	std::string tmp = std::tmpnam(nullptr);
	std::ifstream b;
	b.open(tmp);
	b.close();
	std::remove(tmp.c_str());
	JsonReader jsonReader2(b);
	res = jsonReader2.read();
	ASSERT_EQ(res, nullptr);

	// Try read nothing
	std::stringstream c;
	JsonReader jsonReader3(c);
	res = jsonReader3.read();
	ASSERT_EQ(res, nullptr);
}

TEST(JsonReaderTests, emptyObject)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{}";
	JsonObject* result = jsonReader.read();
	ASSERT_EQ(result->getKey(), "");
	ASSERT_TRUE(result->empty());
	delete result;
}

TEST(JsonReaderTests, basicKeyPairs)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"key\": \"value\"}";
	JsonObject* result = jsonReader.read();
	ASSERT_FALSE(result->empty());
	ASSERT_TRUE(result->has("key"));
	std::string* value = nullptr;
	ASSERT_NO_THROW({value = &result->getValue("key");});
	ASSERT_NE(value, nullptr);
	ASSERT_EQ(*value, "value");
	delete result;
	
	fakeFile << "{\"numTest\": 24}";
	ASSERT_NO_THROW({result = jsonReader.read();});
	ASSERT_FALSE(result->empty());
	ASSERT_TRUE(result->has("numTest"));
	ASSERT_EQ(result->getValue("numTest"), "24");
	delete result;

	fakeFile << "{\"trueTest\": true}";
	ASSERT_NO_THROW({result = jsonReader.read();});
	ASSERT_FALSE(result->empty());
	ASSERT_TRUE(result->has("trueTest"));
	ASSERT_EQ(result->getValue("trueTest"), "true");
	delete result;

	fakeFile << "{\"falseTest\": false}";
	ASSERT_NO_THROW({result = jsonReader.read();});
	ASSERT_FALSE(result->empty());
	ASSERT_TRUE(result->has("falseTest"));
	ASSERT_EQ(result->getValue("falseTest"), "false");
	delete result;

	fakeFile << "{\"nullTest\": null}";
	ASSERT_NO_THROW({result = jsonReader.read();});
	ASSERT_FALSE(result->empty());
	ASSERT_TRUE(result->has("nullTest"));
	ASSERT_EQ(result->getValue("nullTest"), "null");
	delete result;
}

TEST(JsonReaderTests, multipleKeyPairs)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"key\": \"value\",\n\"key2\" : \"value2\",\"key3\":\"value4\"}";
	JsonObject* result = jsonReader.read();
	ASSERT_FALSE(result->empty());
	ASSERT_TRUE(result->has("key"));
	ASSERT_TRUE(result->has("key2"));
	ASSERT_TRUE(result->has("key3"));
	
	std::string* value = nullptr;
	ASSERT_NO_THROW({value = &result->getValue("key");});
	ASSERT_NE(value, nullptr);
	ASSERT_EQ(*value, "value");

	value = nullptr;
	ASSERT_NO_THROW({value = &result->getValue("key2");});
	ASSERT_NE(value, nullptr);
	ASSERT_EQ(*value, "value2");

	value = nullptr;
	ASSERT_NO_THROW({value = &result->getValue("key3");});
	ASSERT_NE(value, nullptr);
	ASSERT_EQ(*value, "value3");
	
	delete result;
}

TEST(JsonReaderTests, invalidKeyPairs)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	
	fakeFile << "\"key\" : \"value\"";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"key\":}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\n\"key\": \"value\"\n";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\n\"key\": \"value\",\n}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\n\"key\": tru\n}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\n\"key\": 123abc\n}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\n123: null\n}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\n null: null\n}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"key\": true, false}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"key\": truefalse}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"key\": notnull}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();
}

TEST(JsonReaderTests, emptyArray)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"array\": []}";
	JsonObject* res = nullptr;
	ASSERT_NO_THROW({res = jsonReader.read();});
	ASSERT_NE(res, nullptr);
	ASSERT_FALSE(res->empty());
	JsonArray& arr = res->getArray("array");
	ASSERT_TRUE(arr.empty());
	ASSERT_EQ(arr.size(), 0);
	ASSERT_THROW(arr.getValue(0), std::out_of_range);
}

TEST(JsonReaderTests, basicArray)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"array\": [1, 2, 3, 4]}";
	JsonObject* res = nullptr;
	ASSERT_NO_THROW({res = jsonReader.read();});
	ASSERT_NE(res, nullptr);
	ASSERT_FALSE(res->empty());
	ASSERT_TRUE(res->has("array"));
	JsonArray& arr = res->getArray("array");
	ASSERT_FALSE(arr.empty());
	ASSERT_EQ(arr.size(), 4);
	ASSERT_EQ(arr.getValue(0), "1");
	ASSERT_EQ(arr.getValue(1), "2");
	ASSERT_EQ(arr.getValue(2), "3");
	ASSERT_EQ(arr.getValue(3), "4");
	ASSERT_THROW(arr.getValue(4), std::out_of_range);
	ASSERT_THROW(arr.getValue(-1), std::out_of_range);
	ASSERT_THROW(arr.getArray(0), JsonTypeException);
	ASSERT_THROW(arr.getObject(0), JsonTypeException);
}

TEST(JsonReaderTests, nestedArrays)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"array\": [[[[1, 2, 3, 4]]]]}";
	JsonObject* res = nullptr;
	ASSERT_NO_THROW({res = jsonReader.read();});
	ASSERT_NE(res, nullptr);
	JsonArray& level1 = res->getArray("array");
	ASSERT_EQ(level1.size(), 1);
	JsonArray& level2 = level1.getArray(0);
	ASSERT_EQ(level2.size(), 1);
	JsonArray& level3 = level2.getArray(0);
	ASSERT_EQ(level3.size(), 1);
	JsonArray& level4 = level3.getArray(0);
	ASSERT_EQ(level4.size(), 4);

	ASSERT_EQ(level4.getValue(0), "1");
	ASSERT_EQ(level4.getValue(1), "2");
	ASSERT_EQ(level4.getValue(2), "3");
	ASSERT_EQ(level4.getValue(3), "4");
}

TEST(JsonReaderTests, objectsInArray)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"array\": [{\"name\": 1}, {\"name\": 2}, {\"name\": 3}, {\"name\": 4}]}";
	JsonObject* res = nullptr;
	ASSERT_NO_THROW({res = jsonReader.read();});
	ASSERT_NE(res, nullptr);
	JsonArray& arr = res->getArray("array");
	
	for (std::size_t i = 0; i < arr.size(); ++i)
	{
		JsonObject& obj = arr.getObject(i);
		std::string& name = obj.getValue("name");
		std::size_t cmp = std::stoi(name);
		ASSERT_EQ(i + 1, cmp);
	}
}

TEST(JsonReaderTests, multipleTypeArrays)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"array\": [1, true, null, \"test\", [1, 2, 3, 4], {}]}";
	JsonObject* res = nullptr;
	ASSERT_NO_THROW({res = jsonReader.read();});
	ASSERT_NE(res, nullptr);
}

TEST(JsonReaderTests, invalidArrays)
{
	std::stringstream fakeFile;
	JsonReader jsonReader(fakeFile);
	fakeFile << "{\"array\": [1, 2, 3}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"array\": [1, 2,]}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"array\": [1,,3]}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{[1, 2, 3]}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"array\": [1, 2, 3]";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"array\": ]}";
	ASSERT_THROW(jsonReader.read(), JsonSyntaxError);
	fakeFile.clear();
}

TEST(JsonReaderTests, nestedObject)
{
	std::stringstream fakeFile;
	JsonReader reader(fakeFile);
	fakeFile << "{\"key\": {\"object1\": {\"object2\": true}}}";
	JsonObject* res = nullptr;
	ASSERT_NO_THROW({res = reader.read();});
	ASSERT_NE(res, nullptr);
	JsonObject& level1 = res->getObject("key");
	JsonObject& level2 = level1.getObject("object1");
	std::string level3 = level2.getValue("object2");
	ASSERT_EQ(level3, true);
}

TEST(JsonReaderTests, invalidObject)
{
	std::stringstream fakeFile;
	JsonReader reader(fakeFile);
	fakeFile << "}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{{}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{,}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();
	
	fakeFile << "{:}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\"}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{\\}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();

	fakeFile << "{@}";
	ASSERT_THROW(reader.read(), JsonSyntaxError);
	fakeFile.clear();
}

// reverse expect to only accept rather than decline
// very strict validation

// use docker with certain memory

// restrict memory space
// check valgrind mem space

// constantly alloc memory until fails

// check available memory and close if less than threshold

// docker with limited memory

// set bytes read threshold

// user defined upload limits
