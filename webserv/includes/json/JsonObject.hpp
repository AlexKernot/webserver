/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:27:22 by akernot           #+#    #+#             */
/*   Updated: 2024/06/12 18:22:15 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONOBJECT_HPP
# define JSONOBJECT_HPP

#include "JsonToken.hpp"
#include "JsonContainer.hpp"

class JsonObject : public JsonToken {
public:
	JsonObject();
	JsonObject(std::string key);
	JsonObject(const JsonObject& copy);
	JsonObject& operator=(const JsonObject& copy);
	~JsonObject();

	
	void addChild(JsonValue* token);
	void addChild(JsonArray* token);
	void addChild(JsonObject* token);
	
	bool has(std::string key) const;
	
	std::string& getValue(std::string key);
	JsonArray& getArray(std::string key);
	JsonObject& getObject(std::string key);
	
	bool empty();
	
private:
	std::vector<JsonContainer> data;

};

#endif // JSONOBJECT_HPP
