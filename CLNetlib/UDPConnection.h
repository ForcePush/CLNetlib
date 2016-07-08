#pragma once

#include "CLSocket.h"
#include "Addr.h"
#include "AbstractConnection.h"

namespace CLNetlib
{
    class UDPConnection : public AbstractConnection
    {
    public:
        UDPConnection();
        UDPConnection(Addr address, const std::string data);
        UDPConnection(const UDPConnection & other);
        ~UDPConnection();

        std::string getData(size_t maxLength);
        bool operator == (const UDPConnection & other);
        bool isValid() const;
    };
}
