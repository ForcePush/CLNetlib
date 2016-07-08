#pragma once

#include <string>
#include <inttypes.h>

#include "CLSocket.h"

namespace CLNetlib
{
    class Addr
    {
    public:
        Addr();
        Addr(const char *ipport);
        Addr(const char *host, uint16_t port);
        Addr(const std::string & ipport);
        Addr(const std::string & host, uint16_t port);
        Addr(const Addr & other);
        Addr(const struct sockaddr *other);
        Addr(const struct sockaddr_in *other);

        operator const struct sockaddr_in & () const;
        operator const struct sockaddr_in * () const;
        operator const struct sockaddr * () const;
        operator std::string() const;

        // make Addr usable as a key in std::map
        bool operator < (const Addr & other) const;
        bool operator <= (const Addr & other) const;
        bool operator > (const Addr & other) const;
        bool operator >= (const Addr & other) const;
        bool operator == (const Addr & other) const;
        bool operator != (const Addr & other) const;

        void setPort(uint16_t newPort);
        void setIP(const char *ipport);
        void setIP(const char *host, uint16_t port);
        void setIP(const std::string & ipport);
        void setIP(const std::string & host, uint16_t port);
        void setIP(const struct sockaddr *other);
        void setIP(const struct sockaddr_in *other);

        u_long getRawIP() const;
        u_short getRawPort() const;

        std::string getHost() const;
        u_short getPort() const;

        static int getSockaddrLen();

        ~Addr();

    private:
        void init(const char *ipport);
        void init(const char *host, uint16_t port);
        sockaddr_in sockaddr;
    };
}  // namespace CLNetlib
