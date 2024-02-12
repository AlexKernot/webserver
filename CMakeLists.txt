cmake_minimum_required(VERSION 3.14)
project(Webserver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

project(webserv)
add_library(webserv
./webserv/src/Logger.cpp)
target_include_directories(webserv PRIVATE ./webserv/includes/)

enable_testing()

add_executable(WebTests ./tests/LoggerTests.cpp)
target_link_libraries(WebTests webserv gtest gtest_main)
add_dependencies(WebTests webserv)

include(GoogleTest)
gtest_discover_tests(WebTests)