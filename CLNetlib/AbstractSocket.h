#pragma once
#include <memory>
#include <stdint.h>
#include "CLSocket.h"
#include "Addr.h"
#include "AbstractConnection.h"

namespace CLNetlib
{
    class AbstractSocket
    {
    public:
        AbstractSocket();
        AbstractSocket(unsigned long readTimeoutMs);
        AbstractSocket(CLSocket sock, unsigned long readTimeoutMs);

        virtual ~AbstractSocket();
        virtual int setReadTimeout(unsigned long msec);

        virtual int send(const char *data, size_t size) = 0;
        virtual std::shared_ptr<AbstractConnection> recv(size_t maxLength) = 0;

    protected:
        virtual void createSocket() = 0;
        virtual void closeSocket() = 0;

        unsigned long readTimeoutMs;
        bool sockOpened;
        CLSocket sock;
    };
}
