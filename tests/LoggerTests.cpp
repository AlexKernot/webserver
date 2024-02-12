#include <gtest/gtest.h>

#include "../webserv/includes/Logger.hpp"

#include <iostream>

static std::string removeTimestamp(std::string in)
{
	int half = in.find(' ', 0);
	int pos = in.find(' ', half + 1);
	return in.substr(pos + 1);
}

TEST(LoggerTests, Default)
{
	Logger logger;

	// Capture stdout into a string stream for processing
	std::streambuf *tempCout = std::cout.rdbuf();
	std::stringstream capture;
	std::cout.rdbuf(capture.rdbuf());

	// Check if stdout was correctly replaced
	capture.peek();
	EXPECT_FALSE(std::cout.fail());
	EXPECT_FALSE(capture.fail());
	EXPECT_TRUE(capture.eof());

	// Check if default ignores debug
	logger.debug("This should be empty");
	capture.peek();
	EXPECT_TRUE(capture.eof());

	// Checks if default reports info
	logger.info("Hello");
	EXPECT_FALSE(capture.bad());
	capture.peek();
	std::string cmp = removeTimestamp(capture.str());
	EXPECT_EQ(cmp, "\x1B[0m   [Info]: Hello\x1B[0m\n");

	// Empties capture stream
	capture.str(std::string());
	capture.clear();
	// Checks if default adds colours to error
	logger.error("Error");
	cmp = removeTimestamp(capture.str());
	EXPECT_EQ(cmp, "\x1b[0;31m  [Error]: Error\x1b[0m\n");

	// Make sure Fatal doesn't also write to stderr if writing to stdout
	std::streambuf *tempCerr = std::cerr.rdbuf();
	std::stringstream captureCerr;
	std::cerr.rdbuf(captureCerr.rdbuf());
	logger.fatal("Fatal");
	captureCerr.peek();
	EXPECT_TRUE(captureCerr.eof());

	// Return stdout and cerr back to the terminal
	std::cout.rdbuf(tempCout);
	std::cerr.rdbuf(tempCerr);
}

TEST(LoggerTests, Files)
{
	std::stringstream output;
	Logger logger(output, Logger::level_debug);

	output.str(std::string());
	output.clear();
	logger.debug("debug");
	EXPECT_FALSE(output.fail());
	std::string res;
	getline(output, res);
	res = removeTimestamp(res);
	EXPECT_EQ(res, "  [Debug]: debug");

	output.str(std::string());
	output.clear();
	logger.error("error");
	EXPECT_FALSE(output.fail());
	getline(output, res);
	res = removeTimestamp(res);
	EXPECT_EQ(res, "  [Error]: error");

	output.str(std::string());
	output.clear();
	Logger logger2(output, Logger::level_error);
	logger2.warning("warning");
	output.peek();
	EXPECT_TRUE(output.eof());

	output.clear();
	logger2.error("error");
	EXPECT_FALSE(output.fail());
	getline(output, res);
	res = removeTimestamp(res);
	EXPECT_EQ(res, "  [Error]: error");
	
}

// Manual colour test and cerr test
/*
TEST(LoggerTests, Manual)
{
	Logger logger(Logger::level_debug);

	logger.debug("debug");
	logger.info("info");
	logger.warning("warning");
	logger.error("error");
	logger.fatal("fatal");

	std::stringstream out;
	Logger logger2(out, Logger::level_info);
	logger2.info("Nothing should show");
	logger2.fatal("Should output to cerr");
	__builtin_trap();
}*/
