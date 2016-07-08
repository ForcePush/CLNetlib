#pragma once

#include <vector>

#include "CLSocket.h"
#include "CLNetlib_api.h"
#include "Addr.h"
#include "TCPConnection.h"
#include "AbstractSocket.h"

namespace CLNetlib
{
    class TCPSocket : public AbstractSocket
    {
    public:
        TCPSocket(const Addr & endpoint, unsigned long readTimeoutMs = 0);
        TCPSocket(const TCPConnection & connection, unsigned long readTimeoutMs = 0);
        ~TCPSocket();

        bool connect();
        bool disconnect();
		bool safeDisconnect();

        int send(const char *data, size_t size);
        int send(const char *str);
        int send(const std::string & str);
        TCPSocket & operator << (const std::string & str);
        TCPSocket & operator << (const char *str);
        std::shared_ptr<AbstractConnection> recv(size_t maxLength);
        TCPConnection TCPSocket::accept();

        int bind();
        int listen(int backlog);

        bool isSockOpened() const;
        bool isConnected() const;

        const Addr & getAddr() const;

        void createSocket();
        void closeSocket();
        
    private:
        Addr address;
        bool connected;
    };
}  // namespace CLNetlib
