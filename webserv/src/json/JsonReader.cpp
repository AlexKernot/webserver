/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonReader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:12:23 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 20:35:25 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonReader.hpp"

#include <stack>

JsonObject* JsonReader::read() const
{
	JsonObject* object = nullptr;
	std::string line;
	while (in.eof() == false) {
		std::getline(in, line);
	}
	if (in.rdstate() == in.bad()) {
		std::string error = "File stream encountered error while reading. ";
		error += "Server configuration may not be valid.";
		logger.warning(error);
	}
	return object;
}