/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonToken.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:21:00 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 19:10:58 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONTOKEN_HPP
# define JSONTOKEN_HPP

#include <istream>
#include <vector>
#include <string>

class JsonToken {
public:
	JsonToken(std::string key);
	JsonToken();
	
	JsonToken(JsonToken& copy);
	JsonToken& operator=(JsonToken& copy);
	
	virtual ~JsonToken();

	std::string getKey() const;
private:
	std::string key;
};

#endif // JSONTOKEN_HPP
