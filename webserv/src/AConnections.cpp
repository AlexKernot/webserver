#include "AConnections.hpp"

#include "unistd.h"

AConnections::AConnections() {	}

AConnections::~AConnections() {
	for (int i = 0; i < openConnections.size(); ++i) {
		int fd = openConnections.at(i).fd;
		if (fd != -1)
			close(fd);
	}
}

void AConnections::send(Ahttp& response) {
	pendingOutgoing.push_back(response);
}

bool AConnections::areConnectionsWaiting() const
{
	return connectionsWaiting;
}

bool AConnections::areOutgoingPending() const
{
	return (pendingOutgoing.size() > 0);
}


std::vector<Ahttp&> AConnections::getPendingOutgoing() const
{
	return pendingOutgoing;
}


std::vector<pollfd> AConnections::getOpenConnections()
{
	return openConnections;
}

