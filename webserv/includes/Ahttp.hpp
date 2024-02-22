/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ahttp.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:04:31 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 18:16:45 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AHTTP_HPP
# define AHTTP_HPP

# include "HttpHeaders.hpp"

# include <string>

class Ahttp : public HttpHeaders {
public:
	Ahttp(int FD);
	virtual ~Ahttp();

        void setHttpVersion(std::string);
        std::string getHttpVersion() const;
	void setMessageBody(const std::string body);
	std::string getMessageBody() const;
        std::string getEndl() const;
        void setEndl(std::string endl);
        int getRecipient() const;
        
	virtual std::string build() const = 0;

private:
	HttpHeaders messageHeaders;
	std::string httpVersion;
	std::string messageBody;
        std::string encoding;
	int socketFD;

	Ahttp();
	Ahttp(const Ahttp&);
	Ahttp& operator=(const Ahttp&);
};

#endif // AHTTP_HPP
