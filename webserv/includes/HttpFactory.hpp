/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:53:05 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 17:55:24 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPFACTORY_HPP
# define HTTPFACTORY_HPP

# include "Ahttp.hpp"
# include "HttpResponse.hpp"
# include "AHttpRequest.hpp"

# include <string>

class HttpFactory {
public:
        static std::string getWebserverVersion();
        
	static std::string generateReasonPhrase(int statusCode);

        static std::string *outOfMemory();
        static void initEmergencyMemory();
        
        // TODO: implement
        static Ahttp *constructHttp(std::string message);
        static AHttpRequest *constructRequest(std::string message);
        
        static Ahttp *create404(int fd);
        static Ahttp *create405(int fd, int allowedMethods);
        static Ahttp *create403(int fd);
private:
        static HttpResponse *createError(int fd, int code);

        static std::string *emergencyErrorString;
};

#endif // HTTPFACTORY_HPP
