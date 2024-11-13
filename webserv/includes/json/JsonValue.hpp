/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonValue.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:09:48 by akernot           #+#    #+#             */
/*   Updated: 2024/06/08 19:13:33 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONVALUE_HPP
# define JSONVALUE_HPP

#include <JsonToken.hpp>

class JsonValue : public JsonToken {
public:
	JsonValue(std::string key, std::string value);
	void setValue(std::string newValue);
	std::string getValue() const;
private:
	std::string value;
};

#endif // JSONVALUE_HPP