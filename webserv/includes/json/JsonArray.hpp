/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:43:09 by akernot           #+#    #+#             */
/*   Updated: 2024/06/11 23:36:42 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONARRAY_HPP
# define JSONARRAY_HPP

#include <vector>
#include <string>

#include "JsonToken.hpp"

class JsonArray : public JsonToken {
public:
	JsonArray(std::string key);
	~JsonArray();

	JsonArray(JsonArray& copy);
	JsonArray& operator=(JsonArray& copy);

	std::string& getValue(const std::size_t index) const;
	JsonArray& getArray(const std::size_t index) const;
	JsonObject& getObject(const std::size_t index) const;
	
	void push_back(const std::string& val);
	void push_back(JsonObject* obj);
	void push_back(JsonArray* arr);

	std::size_t size() const;
	bool empty() const;
private:
	std::vector<JsonContainer> data;
};

#endif // JSONARRAY_HPP
