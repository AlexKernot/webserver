/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:08:47 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 21:57:13 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <vector>

# include <arpa/inet.h>

class Config {
public:
	Config();
	Config(std::string fileName);
	~Config();
	enum methods {
		GET = 1,
		HEAD = 2,
		POST = 4,
		PUT = 8,
		DELETE = 16,
		CONNECT = 32,
		OPTIONS = 64,
		TRACE = 128
	};

	bool checkExists(std::string uri);
	bool checkAllowedMethod(std::string uri, methods method);
	int getAllowedMethods(std::string uri);
	std::string createPath(std::string uri);
	bool getAutoIndex(std::string uri);
private:
	struct location {
		std::string path;
		std::string root;
		std::string rewrite;
		enum rewriteType {off, temporary, permanant};
		rewriteType type;
		bool autoIndex;
		bool allowUploads;
		std::string uploadPath;
		std::string cgiPath;
	};
	struct server {
		long maxBodySize;
		in_addr host;
		int port;
		std::vector<std::string> serverNames;
		unsigned char allowedMethods;
		std::vector<location> locations;
	};
	std::vector<server> servers;
};

#endif // CONFIG_HPP
