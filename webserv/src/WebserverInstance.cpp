/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebserverInstance.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:01:08 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 22:22:11 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebserverInstance.hpp"

#include "Socket.hpp"
#include "IServible.hpp"

#include <iostream>
#include <string>
#include <pair>

// Starts webserver with default settings
WebserverInstance::WebserverInstance()
{
	const std::string ip = "0.0.0.0";
	const int port = 80;
	logger = new Logger(Logger::level_debug);

	try {
		AConnections *connect = new Socket(ip, 80, *logger);
		listen.push_back(connect);
	} catch (const std::exception& ex) {
		std::string error = ex.what();
		logger->fatal(error + "\nTerminating.");
		throw std::runtime_error(error);
	}
}

// Reads config file and starts with those settings
// TODO Will be written after Feburary
// * WebserverInstance::WebserverInstance(std::string configPath) {	}

WebserverInstance::~WebserverInstance()
{
	for (std::size_t i = 0; i < listen.size(); ++i) {
		logger->debug("destroying connection "
                        + listen.at(i)->identify());
		delete listen.at(i);
	}
	delete logger;
}

void WebserverInstance::processRequests
        (int listener, std::vector<std::pair<int, IServible*> > *requests)
{
        for (std::size_t j = 0; j < requests->size(); ++j) {
                try {
                        Ahttp *response = requests->at(j)->serve(config);
                        // Transfers ownership to the AConnections class.
                        listen.at(listener)->send(response);
                } catch (const std::bad_alloc&) {
                        logger->error("Server " 
                                + listen.at(listener)->identify()
                                + " ran out of memory generating response. "
                                + "Replying with 504");
                        logger->flush();
                        listen.at(listener)->reject();
                }
                delete requests->at(j);
        }
}

void WebserverInstance::checkListeners()
{
        for (std::size_t i = 0; i < listen.size(); ++i) {
                std::vector<std::pair<int, IServible*> > *array
                        = listen.at(i)->sync();
                if (array == NULL)
                        continue;
                processRequests(i, array);
                delete array;
        }
}

void WebserverInstance::start()
{
        char *emergencyMemory = new char[1028];
        try {
                while (true)
		        checkListeners();
        } catch (const std::bad_alloc&) {
                delete[] emergencyMemory;
		std::cerr << "The webserver has run out of memory and is "
                        << "unable to continue. Terminating\n";
		return;
        }
        delete[] emergencyMemory;
}
