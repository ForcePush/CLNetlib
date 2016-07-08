#pragma once

#include "CLSocket.h"
#include "Addr.h"
#include "AbstractConnection.h"

namespace CLNetlib
{
    class TCPConnection : public AbstractConnection
    {
    public:
        TCPConnection();
        TCPConnection(Addr address, CLSocket sock);
        TCPConnection(const TCPConnection & other);
        ~TCPConnection();

        std::string getData(size_t maxLength);
        CLSocket getSocket() const;
        bool operator == (const TCPConnection & other);
        bool isValid() const;
    };
}  // namespace CLNetlib
