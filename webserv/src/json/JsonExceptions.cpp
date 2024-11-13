/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonExceptions.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:08:31 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 18:25:55 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json/JsonExceptions.hpp"

#include <string>

const char *JsonTypeException::what() const throw()
{
	return "Data requested is in a different format";
}

const char *JsonKeyNotFoundException::what() const throw()
{
	return "Could not find data with key";
}

JsonSyntaxError::JsonSyntaxError()
{
	error = "Unkown syntax error in schema";
}

JsonSyntaxError::~JsonSyntaxError() throw()
{	}

JsonSyntaxError::JsonSyntaxError(std::string err)
{
	error = err;
}

const char *JsonSyntaxError::what() const throw()
{
	return error.c_str();
}
