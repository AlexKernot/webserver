/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:30:59 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 20:12:40 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONREADER_HPP
# define JSONREADER_HPP

# include <fstream>

# include "json/JsonObject.hpp"
# include "Logger.hpp"

class JsonReader {
public:
	JsonReader(std::istream& readFrom);
	JsonReader(std::istream& readFrom, Logger& logger);

	JsonObject* read() const;
private:
	std::istream& in;
	Logger& logger;
};

#endif // JSONREADER_HPP