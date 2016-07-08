#pragma once
#include <string>
#include <stdint.h>
#include "CLSocket.h"
#include "Addr.h"

namespace CLNetlib
{
    class AbstractConnection
    {
    public:
        AbstractConnection();
        AbstractConnection(const Addr & addr, CLSocket sock);
        AbstractConnection(const Addr & addr, const std::string & data);
        AbstractConnection(const Addr & addr, CLSocket sock, const std::string & data);

        virtual ~AbstractConnection();

        Addr getAddress() const;

        virtual bool isValid() const = 0;
        virtual std::string getData(size_t maxLength) = 0;

    protected:
        Addr address;
        CLSocket sock;
        std::string data;
    };
}
