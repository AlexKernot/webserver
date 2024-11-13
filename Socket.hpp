#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <string>
# include <exception>

# include "Logger.hpp"
# include "AConnections.hpp"

class Socket : public AConnections {
public:
	Socket();
	Socket(std::string ip, int port, Logger& logger);
	Socket(int ip, int port, Logger& logger);
	~Socket();

    std::vector<Ahttp&> sync();
	std::string indentify();

	class SocketCreationException : public std::exception {
		const char *what() const throw();
	};
	class InvalidBindException : public std::exception {
		const char *what() const throw();
	};
	class InvalidListenException : public std::exception {
		const char *what() const throw();
	};

private:
	int ipAddr;
	int port;
	Logger& logger;
};

#endif