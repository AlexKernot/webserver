/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:48:57 by akernot           #+#    #+#             */
/*   Updated: 2024/03/06 16:33:17 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "URI.hpp"
#include "itos.hpp"

#include <iostream>
#include <cstdlib>

URI::URI(std::string url)
{
	if (url.substr(0, 8) == "http://")
		url = url.substr(8);
	std::cout << url << "\n";
	const std::size_t userinfoPos = url.find('@');
	if (userinfoPos != std::string::npos) {
		userinfo = url.substr(0, userinfoPos);
		url = url.substr(userinfoPos + 1);
	}
	std::cout << url << "\n";
	std::size_t portDeliminator = url.find(':');
	std::size_t pathPos = url.find('/');
	if (portDeliminator != std::string::npos) {
		port = std::atoi(
			url.substr(
				portDeliminator + 1, 
				pathPos - portDeliminator)
			.c_str());
		url = url.substr(pathPos + 1);
	}
	std::cout << url << "\n";
	std::size_t queryPos = url.find('?');
	std::size_t fragmentPos = url.find('#');
	if (queryPos != std::string::npos) {
		query = url.substr(queryPos + 1, fragmentPos - queryPos);
		url = url.substr(fragmentPos + 1);
	}
	std::cout << url << "\n";
}

URI::~URI()
{

}

std::string URI::getScheme() const
{
	return scheme;
}

std::string URI::getUserInfo() const
{
	return userinfo;	
}

std::string URI::getHost() const
{
	return host;
}

std::string URI::getPath() const
{
	return path;
}

std::string URI::getQuery() const
{
	return query;
}

std::string URI::getFragment() const
{
	return fragment;
}

int URI::getPort() const
{
	return port;
}