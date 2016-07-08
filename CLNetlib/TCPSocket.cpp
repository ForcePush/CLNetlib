#include "stdafx.h"
#include <string.h>  // strlen
#include "TCPSocket.h"

namespace CLNetlib
{
    TCPSocket::TCPSocket(const Addr & endpoint, unsigned long readTimeoutMs) :
        address(endpoint),
        AbstractSocket(readTimeoutMs)
    {
    }

    TCPSocket::TCPSocket(const TCPConnection & connection, unsigned long readTimeoutMs) :
        address(connection.getAddress()),
        AbstractSocket(connection.getSocket(), readTimeoutMs)
    {
        this->sockOpened = true;
        this->connected = true;
    }

    TCPSocket::~TCPSocket()
    {
    }

    bool TCPSocket::connect()
    {
        if (this->connected) {
            this->disconnect();
        }

        ::connect(this->sock, this->address, this->address.getSockaddrLen());
        this->connected = true;

        return true;
    }

    bool TCPSocket::disconnect()
    {
        if (!this->sockOpened || !this->connected) {
            return false;
        }

        // no more data will be sent/received after this
        ::shutdown(this->sock, CL_SHUTDOWN_BOTH);
        this->connected = false;

        return true;
    }

	bool TCPSocket::safeDisconnect()
	{
		::shutdown(this->sock, CL_SHUTDOWN_BOTH);
		// wait until server's FIN
		char unused[2];
		::recv(this->sock, unused, sizeof(unused), 0);

		return this->disconnect();
	}

    int TCPSocket::send(const char *data, size_t size)
    {
        return ::send(this->sock, data, size, 0);
    }

    int TCPSocket::send(const char *str)
    {
        size_t len = strlen(str);
        return this->send(str, len);
    }

    int TCPSocket::send(const std::string & str)
    {
        const char *data = str.c_str();
        size_t len = str.length();

        return this->send(data, len);
    }

    TCPSocket & TCPSocket::operator<<(const std::string & str)
    {
        this->send(str);
        return *this;
    }

    TCPSocket & TCPSocket::operator<<(const char *str)
    {
        this->send(str);
        return *this;
    }

    std::shared_ptr<AbstractConnection> TCPSocket::recv(size_t)
    {
        struct sockaddr_in tempSockaddr;
        socklen_t sockaddrLen = sizeof(struct sockaddr_in);
        memset(&tempSockaddr, 0, sockaddrLen);

        CLSocket ret = ::accept(this->sock, (sockaddr *)&tempSockaddr, &sockaddrLen);

        return std::shared_ptr<AbstractConnection>(new TCPConnection(Addr(&tempSockaddr), ret));
    }

    int TCPSocket::bind()
    {
        return ::bind(this->sock, this->address, this->address.getSockaddrLen());
    }

    int TCPSocket::listen(int backlog)
    {
        return ::listen(this->sock, backlog);
    }

    TCPConnection TCPSocket::accept()
    {
        struct sockaddr_in tempSockaddr;
        socklen_t sockaddrLen = sizeof(struct sockaddr_in);
        memset(&tempSockaddr, 0, sockaddrLen);

        CLSocket ret = ::accept(this->sock, (sockaddr *)&tempSockaddr, &sockaddrLen);

        return{ Addr(&tempSockaddr), ret };
    }

    bool TCPSocket::isSockOpened() const
    {
        return this->sockOpened;
    }

    bool TCPSocket::isConnected() const
    {
        return this->connected;
    }

    const Addr & TCPSocket::getAddr() const
    {
        return this->address;
    }
    
    void TCPSocket::createSocket()
    {
#ifdef WIN32
        CLNetlib::win_WSAInitIfNeed();
#endif  // WIN32

        this->connected = false;
        this->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        this->sockOpened = true;
    }

    void TCPSocket::closeSocket()
    {
        if (this->connected) {
            shutdown(this->sock, CL_SHUTDOWN_BOTH);  // no more data will be sent/received
        }

#ifdef WIN32
        closesocket(this->sock);
#else  // WIN32
        close(this->sock);
#endif  // WIN32
    }
    
}  // namespace CLNetlib
