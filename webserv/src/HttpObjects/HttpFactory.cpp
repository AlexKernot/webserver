/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpFactory.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:55:41 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 22:17:52 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpFactory.hpp"

#include "HttpResponse.hpp"
#include "Config.hpp"

std::string *HttpFactory::emergencyErrorString = NULL;

std::string HttpFactory::getWebserverVersion()
{
        return "Webserv/0.1";
}

std::string *HttpFactory::outOfMemory()
{
	return emergencyErrorString;
}

void HttpFactory::initEmergencyMemory()
{
	emergencyErrorString = new std::string();
	*emergencyErrorString = "Http/1.1 503 Service Unavailable\n";
	*emergencyErrorString += "Retry-After: 120\n";
	*emergencyErrorString += "Server: " + getWebserverVersion() + "\n";
}

HttpResponse *HttpFactory::createError(int fd, int code)
{
	HttpResponse *retval = new HttpResponse(fd);
        retval->setStatusCode(404);
	retval->setHeader("Server", getWebserverVersion());
	return retval;
}

Ahttp *HttpFactory::create404(int fd)
{
        return createError(fd, 404);
}

Ahttp *HttpFactory::create405(int fd, int allowedMethods)
{
        HttpResponse *retval = createError(fd, 405);
        std::string allowed;
        if (allowedMethods & Config::GET)
                allowed += "GET, ";
        if (allowedMethods & Config::HEAD)
                allowed += "HEAD, ";
        if (allowedMethods & Config::POST)
                allowed += "POST, ";
        if (allowedMethods & Config::DELETE)
                allowed += "DELETE, ";
        if (allowedMethods & Config::CONNECT)
                allowed += "CONNECT, ";
        if (allowedMethods & Config::OPTIONS)
                allowed += "OPTIONS, ";
        if (allowedMethods & Config::TRACE)
                allowed += "TRACE, ";
        allowed.resize(allowed.size() - 2);
        
        retval->setHeader("Allow", allowed);
        return retval;
}

Ahttp *HttpFactory::create403(int fd)
{
	return createError(fd, 403);
}

// * If somebody knows an alternative to an 80 line switch statement
// * please please please reach out and let me know. I don't like this
// * solution and I feel there has to be something better....
std::string HttpFactory::generateReasonPhrase(int statusCode)
{
	switch(statusCode) {
	case 100:
		return "Continue";
	case 101:
		return "Switching Protocols";
	case 200:
		return "OK";
	case 201:
		return "Created";
	case 202:
		return "Accepted";
	case 203:
		return "Non-Authoritative Information";
	case 204:
		return "No Content";
	case 205:
		return "Reset Content";
	case 206:
		return "Partial Content";
	case 300:
		return "Multiple Choices";
	case 301:
		return "Moved Permanently";
	case 302:
		return "Found";
	case 303:
		return "See Other";
	case 304:
		return "Not Modified";
	case 305:
		return "Use Proxy";
	case 306:
		return "Unused";
	case 307:
		return "Temporary Redirect";
	case 400:
		return "Bad Request";
	case 401:
		return "Unauthorized";
	case 402:
		return "Payment Required";
	case 403:
		return "Forbidden";
	case 404:
		return "Not Found";
	case 405:
		return "Method Not Allowed";
	case 406:
		return "Not Acceptable";
	case 407:
		return "Proxy Authentication Required";
	case 408:
		return "Request Timeout";
	case 409:
		return "Conflict";
	case 410:
		return "Gone";
	case 411:
		return "Length Required";
	case 412:
		return "Precondition Failed";
	case 413:
		return "Request Entity Too Large";
	case 414:
		return "Request-URI Too Large";
	case 415:
		return "Unsupported Media Type";
	case 416:
		return "Range Not Satisfiable";
	case 417:
		return "Expectation Failed";
	case 500:
		return "Internal Server Error";
	case 501:
		return "Not Implemented";
	case 502:
		return "Bad Gateway";
	case 503:
		return "Service Unavailable";
	case 504:
		return "Gateway Timeout";
	case 505:
		return "HTTP Version Not Supported";
	default:
		return "Unknown Status";
	}
}
