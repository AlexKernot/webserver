/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaders.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:48:21 by akernot           #+#    #+#             */
/*   Updated: 2024/02/17 17:24:07 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADERS_HPP
# define HTTPHEADERS_HPP

# include <exception>
# include <vector>
# include <string>
# include <utility>

class HttpHeaders {
public:
        HttpHeaders();
        HttpHeaders(const HttpHeaders& copy);
        HttpHeaders& operator=(const HttpHeaders& copy);
        ~HttpHeaders();

        std::string& toLower(std::string& str) const;
        bool validateName(const std::string& str) const;

        std::string getHeader(std::string name) const;
        void setHeader(std::string name, std::string value);

        std::string constructHeaders() const;
        
        class AHeaderException : public std::exception {
                virtual const char *what() const throw();
        };
        class HeaderTooLongException : public AHeaderException {
                const char *what() const throw();
        };
        class TooManyHeadersException : public AHeaderException {
                const char *what() const throw();
        };
        class InvalidHeaderException : public AHeaderException {
                const char *what() const throw();
        };
private:
        std::vector<std::pair<std::string, std::string> > headers;
};

#endif
