// C library headers
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <bits/stdint-uintn.h>
#include <errno.h>

// C++ library headers
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>

// 
#include "Logger.hpp"
#include "Webserv.h"

static std::string IPtoString(const in_addr address)
{
        std::string retval;
        uint32_t num = address.s_addr;

        retval += itos((num >> 24)&0xFF);
        retval += ".";
        retval += itos((num >> 16)&0xFF);
        retval += ".";
        retval += itos((num >> 8)&0xFF);
        retval += ".";
        retval += itos(num & 0xFF);
        return retval;
}

/**
 * Rewrite in my own style. Temp function mostly copied from stack
 * overflow.
*/
static in_addr StringToIP(std::string string) {
        uint32_t ip = 0;
        int num = 0;
        std::string dump;
        std::istringstream stream(string);

        for (size_t i = 0; i < 4; ++i) {
                stream >> num;
                ip |= (num << (8 * (3 - i)));
                if (i != 3)
                        stream >> dump;
        }
        in_addr retval = {ip};
        return retval;
}

int main(int ac, char *av[])
{
        (void)av;
        (void)ac;
        const int port = 2554;
        const std::string ip = "0.0.0.0";
        const in_addr addr = StringToIP(ip);
        Logger logger(std::cout, Logger::level_debug);
        int socketFD = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
        if (socketFD == -1) {
                std::string error = strerror(errno);
                logger.fatal("Socket: " + error + ". Terminating.");
                return 1;
        }
        logger.info("Created socket with FD " + itos(socketFD));
        sockaddr_in listenAddress;
        std::memset(&listenAddress, 0, sizeof(listenAddress));
        listenAddress.sin_family = AF_INET;
        listenAddress.sin_port = htons(port);
        listenAddress.sin_addr = addr;

        if (bind(socketFD, (const sockaddr *)&listenAddress, sizeof(listenAddress)) == -1) {
                std::string error = strerror(errno);
                logger.fatal("Bind: " + error + " Terminating.");
                return 1;
        }
        logger.info("bound socket to address " + IPtoString(addr) + "/" + itos(port));
        static const int maxQueue = 5;
        if (listen(socketFD, maxQueue) == -1) {
                std::string error = strerror(errno);
                logger.fatal("Listen: " + error + ". Terminating.");
                return 1;
        }
        logger.info("Socket now listening for incoming requests.");

        pollfd checkReady;
        checkReady.fd = socketFD;
        checkReady.events = POLLIN | POLLPRI | POLLOUT | POLLRDHUP;
        checkReady.revents = 0;

        std::vector<int> fds;

        while (true) {
                int pollReturn = poll(&checkReady, 1, 0);
                if (pollReturn == 0)
                        continue;
                if (pollReturn == -1) {
                        std::string error = strerror(errno);
                        logger.fatal("Poll: " + error + " Terminating.");
                        return 1;
                }
                socklen_t size = sizeof(listenAddress);
                if ((checkReady.revents&POLLIN) == true) {
                        int acceptedFD = accept(socketFD, reinterpret_cast<sockaddr*>(&listenAddress), &size);
                        fcntl(acceptedFD, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
                        fds.push_back(acceptedFD);
                }
        }
}
