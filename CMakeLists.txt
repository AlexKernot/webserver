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

project(json)
add_library(json
./webserv/src/Logger.cpp ./webserv/src/json/AJsonToken.cpp ./webserv/src/json/JsonExceptions.cpp
./webserv/src/json/JsonReader.cpp ./webserv/src/json/JsonValue.cpp ./webserv/src/json/JsonArray.cpp
./webserv/src/json/JsonObject.cpp)
target_include_directories(json PRIVATE ./webserv/includes/)
target_compile_options(json PRIVATE -Wall -Wextra -Wpedantic -std=c++98 -g)

project(webserv)
add_library(webserv
./webserv/src/Logger.cpp ./webserv/src/itos.cpp ./webserv/src/HttpFactory.cpp 
./webserv/src/Ahttp.cpp ./webserv/src/AHttpRequest.cpp
./webserv/src/HttpResponse.cpp ./webserv/src/HttpHeaders.cpp)
add_dependencies(webserv, json)
target_include_directories(webserv PRIVATE ./webserv/includes/)
target_compile_options(webserv PRIVATE -Wall -Wextra -Wpedantic -std=c++98 -g)

enable_testing()

add_executable(WebTests ./tests/LoggerTests.cpp)
target_link_libraries(WebTests webserv gtest gtest_main)
add_dependencies(WebTests webserv)
target_compile_options(WebTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(headerTests ./tests/HttpHeaderTests.cpp)
target_link_libraries(headerTests webserv gtest gtest_main)
add_dependencies(headerTests webserv)
target_compile_options(headerTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(httpFactoryTests ./tests/HttpFactoryTests.cpp)
target_link_libraries(httpFactoryTests webserv gtest gtest_main)
add_dependencies(httpFactoryTests webserv)
target_compile_options(httpFactoryTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(AhttpTests ./tests/AhttpTests.cpp)
target_link_libraries(AhttpTests webserv gtest gtest_main)
add_dependencies(AhttpTests webserv)
target_compile_options(AhttpTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(itosTests ./tests/itosTests.cpp)
target_link_libraries(itosTests webserv gtest gtest_main)
add_dependencies(itosTests webserv)
target_compile_options(itosTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(HttpResponseTests ./tests/HttpResponseTests.cpp)
target_link_libraries(HttpResponseTests webserv gtest gtest_main)
add_dependencies(HttpResponseTests webserv)
target_compile_options(HttpResponseTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(JsonTokensTests ./tests/JsonTokensTests.cpp)
target_link_libraries(JsonTokensTests webserv gtest gtest_main)
add_dependencies(JsonTokensTests json)
target_compile_options(JsonTokensTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)

add_executable(JsonReaderTests ./tests/JsonReaderTests.cpp)
target_link_libraries(JsonReaderTests webserv gtest gtest_main)
add_dependencies(JsonReaderTests json)
target_compile_options(JsonReaderTests PRIVATE -Wall -Wextra -Wpedantic -std=c++20 -g)


include(GoogleTest)
gtest_discover_tests(WebTests)
gtest_discover_tests(headerTests)
gtest_discover_tests(httpFactoryTests)
gtest_discover_tests(AhttpTests)
gtest_discover_tests(itosTests)
gtest_discover_tests(HttpResponseTests)
gtest_discover_tests(JsonTokensTests)
gtest_discover_tests(JsonReaderTests)