#include "stdafx.h"
#include "AbstractConnection.h"

namespace CLNetlib
{
    AbstractConnection::AbstractConnection() :
        address(),
        sock(CL_INVALID_SOCKET),
        data("")
    {
    }

    AbstractConnection::AbstractConnection(const Addr & addr, CLSocket sock) :
        address(addr),
        sock(sock),
        data("")
    {
    }

    AbstractConnection::AbstractConnection(const Addr & addr, const std::string & data) :
        address(addr),
        sock(CL_INVALID_SOCKET),
        data(data)
    {
    }

    AbstractConnection::AbstractConnection(const Addr & addr, CLSocket sock, const std::string & data) :
        address(addr),
        sock(sock),
        data(data)
    {
    }

    AbstractConnection::~AbstractConnection()
    {
    }

    Addr AbstractConnection::getAddress() const
    {
        return this->address;
    }
}
