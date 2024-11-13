/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:16:20 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 21:35:10 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Methods/Get.hpp"

#include "HttpFactory.hpp"
#include "HttpResponse.hpp"
#include "itos.hpp"

#include <fstream>
#include <sstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

Ahttp *Get::autoIndex(std::string directoryPath) const
{
        std::string relativePath = uri.relativePath();
        std::stringstream body;
        body << "<H1>Index of " << relativePath << "</H1>\n";
	DIR *directory = opendir(directoryPath.c_str());
        dirent *file = readdir(directory);
        HttpResponse *retval = new HttpResponse(getRecipient());
        while (file != NULL) {
                body << "<a href";
                file = readdir(directory);
        }
        retval->readBody(body);
        return retval;
}

Ahttp *Get::serve(Config &config)
{
	std::string uri = getURI();
	if (config.checkExists(uri) == false)
		return HttpFactory::create404(getRecipient()); // Not Found
	if (config.checkAllowedMethod(uri, Config::GET) == false)
		return HttpFactory::create405(
			getRecipient(), 
			config.getAllowedMethods(uri)
		); // Method not Allowed
	std::string fullPath = config.createPath(uri);
	struct stat info;
	if (stat(fullPath.c_str(), &info) == -1)
		return HttpFactory::create404(getRecipient()); // Not Found
	// check if its a directory
	if (info.st_mode & S_IFDIR) {
		if (config.getAutoIndex(uri) == false)
			return HttpFactory::create403(getRecipient()); // Forbidden
		return autoIndex(fullPath);
	}
	// Not a file
	if ((info.st_mode & S_IFREG) == false)
		return HttpFactory::create404(getRecipient()); // Not found
	int file = open(fullPath.c_str(), O_RDONLY);
	if (file == -1) {
		return HttpFactory::create404(getRecipient());
	}
	HttpResponse *response = new HttpResponse(getRecipient());

	// send default headers
	response->setHeader("Accept-Ranges", "none");
	response->setHeader("Server", HttpFactory::getWebserverVersion());
	response->setStatusCode(200);
	response->readBody(file);
	response->setHeader("content-length", itos(response->getBodySize()));
	return response;
}

std::string Get::getMethodString() const
{
	return "GET";
}


Config::methods Get::getMethod() const
{
	return Config::GET;
}

