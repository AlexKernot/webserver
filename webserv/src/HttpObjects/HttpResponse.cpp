/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:49:50 by akernot           #+#    #+#             */
/*   Updated: 2024/02/15 17:33:45 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

#include "HttpFactory.hpp"
#include "itos.hpp"

HttpResponse::HttpResponse(int socketFD) : Ahttp(socketFD)
{
	statusCode = 0;
        reasonPhrase = "No Status";
}

HttpResponse::~HttpResponse()
{
	// All members are trivially destructible
}

int HttpResponse::getStatusCode() const
{
	return statusCode;
}

void HttpResponse::setStatusCode(int code)
{
	statusCode = code;
        reasonPhrase = HttpFactory::generateReasonPhrase(code);
}

std::string HttpResponse::getReasonPhrase() const
{
	return reasonPhrase;
}

std::string HttpResponse::build() const
{
	std::string retval = getHttpVersion() + " ";
        retval += itos(statusCode) + " " + reasonPhrase + getEndl();
        retval += constructHeaders() + getEndl();
        retval += getMessageBody();
        return retval;
}
