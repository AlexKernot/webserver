/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 21:15:26 by akernot           #+#    #+#             */
/*   Updated: 2024/03/05 21:17:06 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URI_HPP
# define URI_HPP

#include <string>

class URI {
public:
	URI(std::string url);
	~URI();
	std::string getScheme() const;
	std::string getUserInfo() const;
	std::string getHost() const;
	std::string getPath() const;
	std::string getQuery() const;
	std::string getFragment() const;
	int getPort() const;
private:
	std::string scheme;
	std::string userinfo;
	std::string host;
	int port;
	std::string path;
	std::string query;
	std::string fragment;

	URI(const URI&);
	URI& operator=(const URI&);
};

#endif // URI_HPP