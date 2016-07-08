#include "stdafx.h"
#include "TCPConnection.h"

namespace CLNetlib
{
    TCPConnection::TCPConnection() :
        AbstractConnection()
    {
    }

    TCPConnection::TCPConnection(Addr address, CLSocket sock) :
        AbstractConnection(address, sock)
    {
    }

    TCPConnection::TCPConnection(const TCPConnection & other) :
        AbstractConnection(other.address, other.sock, other.data)
    {
    }

    TCPConnection::~TCPConnection()
    {
    }

    std::string TCPConnection::getData(size_t maxLength)
    {
        std::string ret;
        char *buffer = new char[maxLength];

        int retSize = ::recv(this->sock, buffer, maxLength, 0);
        if (retSize >= 0) {
            ret = std::string(buffer, retSize);
        }

        delete[] buffer;
        return ret;
    }

    bool TCPConnection::operator==(const TCPConnection & other)
    {
        return this->address == other.address && this->sock == other.sock;
    }

    bool TCPConnection::isValid() const
    {
#ifdef WIN32
        return this->sock != CL_INVALID_SOCKET;
#else
        return this->sock >= 0;
#endif  // WIN32
    }

    CLSocket TCPConnection::getSocket() const
    {
        return this->sock;
    }
}
