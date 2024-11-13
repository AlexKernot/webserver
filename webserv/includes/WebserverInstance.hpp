#ifndef WEBSERVERINSTANCE_HPP
# define WEBSERVERINSTANCE_HPP

# include "AConnections.hpp"

# include "Logger.hpp"

# include <vector>

class WebserverInstance {
public:
	// Starts webserver with default settings
	WebserverInstance();
	// Reads config file and starts with those settings
	WebserverInstance(std::string configPath);
	~WebserverInstance();

	void start();
private:
	void checkListeners();
	void processRequests(int listener, std::vector<std::pair<int, IServible*>> *requests);

	std::vector<AConnections*> listen;
	Logger *logger;
	bool listening;
	// Class should not be copied
	WebserverInstance(const WebserverInstance&);
	WebserverInstance& operator=(const WebserverInstance&);
};

#endif // WEBSERVERINSTANCE_HPP
