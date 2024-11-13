#ifndef CONNECTIONS_HPP
# define CONNECTIONS_HPP

# include <vector>

# include <poll.h>

# include "HttpResponse.hpp"
# include "AHttpRequest.hpp"
# include "OpenConnection.hpp"

class AConnections {
public:
	AConnections();
	virtual ~AConnections();

	void send(Ahttp *response);
	bool areConnectionsWaiting() const;
	bool areOutgoingPending() const;
	std::vector<Ahttp*> getPendingOutgoing() const;
	std::vector<pollfd> getOpenConnections();

	virtual std::vector<std::pair<int, IServible*> > *sync() = 0;
	virtual std::string identify() = 0;

private:
	std::vector<Ahttp *> pendingOutgoing;
	std::vector<OpenConnection *> openConnections;
	bool connectionsWaiting;
};

#endif // CONNECTIONS_HPP
