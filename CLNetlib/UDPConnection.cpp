#include "stdafx.h"
#include "UDPConnection.h"


namespace CLNetlib
{
    UDPConnection::UDPConnection() :
        AbstractConnection()
    {
    }

    UDPConnection::UDPConnection(Addr address, const std::string data) :
        AbstractConnection(address, data)
    {
    }

    UDPConnection::UDPConnection(const UDPConnection & other) :
        AbstractConnection(other.address, other.sock, other.data)
    {
    }


    UDPConnection::~UDPConnection()
    {
    }

    std::string UDPConnection::getData(size_t)
    {
        return this->data;
    }

    bool UDPConnection::operator==(const UDPConnection & other)
    {
        return this->address == other.address && this->data == other.data;
    }

    bool UDPConnection::isValid() const
    {
        return true;
    }
}
