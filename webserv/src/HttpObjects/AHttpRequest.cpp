/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:32:12 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 17:08:05 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AHttpRequest.hpp"

AHttpRequest::AHttpRequest(int socketFD) : Ahttp(socketFD) { }

AHttpRequest::~AHttpRequest()
{
        // All variables are trivially destructible. No actions needed.
}

std::string AHttpRequest::build() const
{
        std::string request = getMethodString() + " ";
        if (getURI() != "")
                request += getURI() + " ";
        else
                request += "/ ";
        request += getHttpVersion() + getEndl();
        request += constructHeaders() + getEndl();
        request += getMessageBody() + getEndl();
        return request;
}

std::string AHttpRequest::getURI() const
{
        return absoluteURI;
}

void AHttpRequest::setURI(std::string uri)
{
        absoluteURI = uri;
}
