/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonContainer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:08:45 by akernot           #+#    #+#             */
/*   Updated: 2024/06/11 16:24:33 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONCONTAINER_HPP
# define JSONCONTAINER_HPP

# include <JsonArray.hpp>
# include <JsonObject.hpp>
# include <JsonValue.hpp>

class JsonContainer {
public:
	enum type {object, array, value};
	JsonContainer(JsonObject* object);
	JsonContainer(JsonArray* array);
	JsonContainer(JsonValue* value);
	~JsonContainer();
	type getType();
	JsonObject& getObject();
	JsonArray& getArray();
	JsonValue& getValue();
public:
	type dataType;
	union json
	{
		JsonObject* object;
		JsonArray* array;
		JsonValue* value;
	};
};

#endif // JSONCONTAINER_HPP