/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:48:37 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 19:14:21 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json/JsonToken.hpp"
#include "json/JsonExceptions.hpp"

JsonToken::JsonToken()
{
	this->key = "";
}

JsonToken::JsonToken(std::string key)
{
	this->key = key;
}

std::string JsonToken::getKey() const
{
	return key;
}
