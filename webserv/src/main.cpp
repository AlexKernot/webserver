/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:14:24 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 20:50:00 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "WebserverInstance.hpp"

int main()
{
	char *emergencyMemory = new char[1028];
	try {
		WebserverInstance webserver;
		webserver.start();
	} catch (std::bad_alloc&) {
		delete[] emergencyMemory;
		std::cerr << "Webserver did not have enough memory to start.\n";
		return 0;
	}
	delete[] emergencyMemory;
	return 0;
}
