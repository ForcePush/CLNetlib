#pragma once
#include <stdint.h>
#include "CLSocket.h"
#include "Addr.h"
#include "AbstractSocket.h"

namespace CLNetlib
{
    class UDPSocket : public AbstractSocket
    {
    public:
        UDPSocket();
        UDPSocket(uint16_t port, unsigned long readTimeoutMs = 0);
        ~UDPSocket();

        int send(const std::string & ipport, const char *msg, size_t msgLen) const;
        int send(const std::string & ip, uint16_t port, const char *msg, size_t msgLen) const;
        int send(const Addr & addr, const char *msg, size_t msgLen) const;

        int send(const std::string & ipport, const std::string & msg) const;
        int send(const std::string & ip, uint16_t port, const std::string & msg) const;
        int send(const Addr & addr, const std::string & msg) const;

        std::shared_ptr<AbstractConnection> recv(size_t maxLength);

    private:
        void createSocket();
        void closeSocket();

        uint16_t listenPort;
    };
}

