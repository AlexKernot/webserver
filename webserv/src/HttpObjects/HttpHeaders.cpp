/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaders.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:57:02 by akernot           #+#    #+#             */
/*   Updated: 2024/02/17 17:34:03 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpHeaders.hpp"

std::string& HttpHeaders::toLower(std::string& str) const
{
        for (std::size_t i = 0; i < str.size(); ++i) {
                if (str.at(i) >= 'A' && str.at(i) <= 'Z')
                        str.at(i) -= 'A' - 'a';
        }
        return str;
}

bool HttpHeaders::validateName(const std::string& str) const
{
        if (str == "")
                return false;
        for (std::size_t i = 0; i < str.size(); ++i) {
                if (str.at(i) != '-' && (str.at(i) < 'a' || str.at(i) > 'z'))
                        return false;
        }
        return true;
}

HttpHeaders::HttpHeaders()
{
        // No preprocessing needed
}

HttpHeaders::HttpHeaders(const HttpHeaders& copy)
{
        *this = copy;
}

HttpHeaders& HttpHeaders::operator=(const HttpHeaders& copy)
{
        if (this == &copy)
                return *this;
        for (std::size_t i = 0; i < copy.headers.size(); ++i) {
                // Using emplace to ensure it's copied not moved in c++11
                headers.push_back(copy.headers.at(i));
        }
        return *this;
}

HttpHeaders::~HttpHeaders()
{
        // All elements trivially destructible
}

std::string HttpHeaders::getHeader(std::string name) const
{
        name = toLower(name);
        for (std::size_t i = 0; i < headers.size(); ++i) {
                if (headers.at(i).first == name)
                        return headers.at(i).second;
        }
        return "";
}

void HttpHeaders::setHeader(std::string name, std::string value)
{
        if (name == "" || value == "")
                throw InvalidHeaderException();
        if (name.size() > 8190 || value.size() > 8190)
                throw HeaderTooLongException();
        name = toLower(name);
        value = toLower(value);
        if (validateName(name) == false)
                throw InvalidHeaderException();
        for (std::size_t i = 0; i < headers.size(); ++i) {
                if (headers.at(i).first == name) {
                        headers.at(i).second = value;
                        return;
                }
        }
        if (headers.size() >= 100)
                throw TooManyHeadersException();
        std::pair<std::string, std::string> keyPair(name, value);
        headers.push_back(keyPair);
}

std::string HttpHeaders::constructHeaders() const
{
        std::string retval;

        // If we somehow added more than 100 headers, stop at the 100th.
        for (std::size_t i = 0; i < headers.size() && i < 100; ++i) {
                retval += headers.at(i).first + ":" + headers.at(i).second + "\n";
        }
        return retval;
}

const char *HttpHeaders::HeaderTooLongException::what() const throw() {
        return "Header more than 8190 characters";
}

const char *HttpHeaders::TooManyHeadersException::what() const throw() {
        return "Attempting to add more than 100 headers";
}

const char *HttpHeaders::InvalidHeaderException::what() const throw() {
        return "Invalid header received";
}

const char *HttpHeaders::AHeaderException::what() const throw() {
        return "A basic header exception occured";
}
