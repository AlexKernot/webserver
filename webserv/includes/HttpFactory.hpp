/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:53:05 by akernot           #+#    #+#             */
/*   Updated: 2024/02/15 17:16:00 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPFACTORY_HPP
# define HTTPFACTORY_HPP

# include "Ahttp.hpp"

# include <string>

class HttpFactory {
public:
	static std::string generateReasonPhrase(int statusCode);
        // TODO: implement
        static Ahttp *constructHttp(std::string message);
private:
};

#endif // HTTPFACTORY_HPP
