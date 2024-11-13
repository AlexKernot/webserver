/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonExceptions.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:22:24 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 18:25:10 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <string>

class JsonTypeException : public std::exception {
public:
	const char *what() const throw();
};
	
class JsonKeyNotFoundException : public std::exception {
public:
	const char *what() const throw();
};

class JsonSyntaxError : public std::exception {
public:
	JsonSyntaxError();
	~JsonSyntaxError() throw();
	JsonSyntaxError(std::string err);
	const char *what() const throw();
private:
	std::string error;
};
