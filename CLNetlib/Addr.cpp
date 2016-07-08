#include "stdafx.h"
#include <sstream>
#include "string.h"  // memset, memcpy, memcmp
//#include <iostream>

#include "Addr.h"

namespace CLNetlib
{
    Addr::Addr()
    {
        memset(&this->sockaddr, 0, this->getSockaddrLen());
    }

    Addr::Addr(const char *ipport)
    {
        this->init(ipport);
    }

    Addr::Addr(const char *host, uint16_t port)
    {
        this->init(host, port);
    }

    Addr::Addr(const std::string & ipport)
    {
        this->init(ipport.c_str());
    }

    Addr::Addr(const std::string & host, uint16_t port)
    {
        this->init(host.c_str(), port);
    }

    Addr::Addr(const Addr & other)
    {
        memcpy(&this->sockaddr, &other.sockaddr, Addr::getSockaddrLen());
    }

    Addr::Addr(const struct sockaddr *other)
    {
        memset(&this->sockaddr, 0, Addr::getSockaddrLen());
        memcpy(&this->sockaddr, other, Addr::getSockaddrLen());
    }

    Addr::Addr(const sockaddr_in *other)
    {
        memset(&this->sockaddr, 0, Addr::getSockaddrLen());
        memcpy(&this->sockaddr, other, Addr::getSockaddrLen());
    }

    void Addr::setIP(const char *ipport)
    {
        this->init(ipport);
    }

    void Addr::setIP(const char *host, uint16_t port)
    {
        this->init(host, port);
    }

    void Addr::setIP(const std::string & ipport)
    {
        this->init(ipport.c_str());
    }

    void Addr::setIP(const std::string & host, uint16_t port)
    {
        this->init(host.c_str(), port);
    }

    void Addr::setIP(const struct sockaddr *other)
    {
        memset(&this->sockaddr, 0, Addr::getSockaddrLen());
        memcpy(&this->sockaddr, other, Addr::getSockaddrLen());
    }

    void Addr::setIP(const struct sockaddr_in *other)
    {
        memset(&this->sockaddr, 0, Addr::getSockaddrLen());
        memcpy(&this->sockaddr, other, Addr::getSockaddrLen());
    }

    Addr::operator const struct sockaddr_in&() const
    {
        return *(const sockaddr_in *)&this->sockaddr;
    }

    Addr::operator const struct sockaddr_in*() const
    {
        return (const sockaddr_in *)&this->sockaddr;
    }

    Addr::operator const struct sockaddr*() const
    {
        return (const struct sockaddr *)&this->sockaddr;
    }

    Addr::operator std::string() const
    {
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, (IN_ADDR *)&(this->sockaddr.sin_addr), str, INET_ADDRSTRLEN);

        return std::string(str) + ":" + std::to_string(ntohs(this->sockaddr.sin_port));
    }

    bool Addr::operator<(const Addr & other) const
    {
        u_long thisIp = htonl(this->sockaddr.sin_addr.s_addr);
        u_long otherIp = htonl(other.sockaddr.sin_addr.s_addr);
        u_short thisPort = htons(this->sockaddr.sin_port);
        u_short otherPort = htons(other.sockaddr.sin_port);

        if (thisIp == otherIp)
        {
            return thisPort < otherPort;
        }

        return thisIp < otherIp;
    }

    bool Addr::operator<=(const Addr & other) const
    {
        return (this->operator<(other)) || (this->operator==(other));;
    }

    bool Addr::operator>(const Addr & other) const
    {
        return !(this->operator<(other)) && !(this->operator==(other));
    }

    bool Addr::operator>=(const Addr & other) const
    {
        return !(this->operator<(other));
    }

    bool Addr::operator==(const Addr & other) const
    {
        return this->sockaddr.sin_addr.s_addr == other.sockaddr.sin_addr.s_addr &&
            this->sockaddr.sin_port == other.sockaddr.sin_port;
    }

    bool Addr::operator!=(const Addr & other) const
    {
        return !(this->operator==(other));;
    }

    void Addr::setPort(uint16_t newPort)
    {
        this->sockaddr.sin_port = htons(newPort);
    }

    u_long Addr::getRawIP() const
    {
        return this->sockaddr.sin_addr.s_addr;
    }

    u_short Addr::getRawPort() const
    {
        return this->sockaddr.sin_port;
    }

    std::string Addr::getHost() const
    {
        char buffer[INET_ADDRSTRLEN * 2];
        IN_ADDR addrBuf;
        memcpy(&addrBuf, &this->sockaddr.sin_addr, sizeof(IN_ADDR));
        inet_ntop(AF_INET, &addrBuf, buffer, sizeof(buffer));

        return std::string(buffer);
    }

    u_short Addr::getPort() const
    {
        return ntohs(this->sockaddr.sin_port);
    }

    int Addr::getSockaddrLen()
    {
        return sizeof(struct sockaddr_in);
    }

    Addr::~Addr()
    {
    }

    void Addr::init(const char *host, uint16_t port)
    {
        memset(&this->sockaddr, 0, Addr::getSockaddrLen());

        this->sockaddr.sin_family = AF_INET;
        this->sockaddr.sin_port = htons(port);

        if (!host) {
            return;
        }

        // try to interpret host as an IPv4 address
        this->sockaddr.sin_addr.s_addr = inet_addr(host);
        if (this->sockaddr.sin_addr.s_addr != 0) {
            return;
        }
        else if (strcmp(host, "0.0.0.0") == 0) {
            return;
        }

        // no luck, get IP for host through DNS
        struct addrinfo *result = NULL, hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        getaddrinfo(host, std::to_string(port).c_str(),
            &hints, &result);

        if (result != NULL) {
            memcpy(&this->sockaddr, result->ai_addr, result->ai_addrlen);
        }
        else {
            memset(&this->sockaddr.sin_addr, 0, sizeof(IN_ADDR));
        }

        freeaddrinfo(result);
    }

    void Addr::init(const char *ipport)
    {
        if (!ipport) {
            return;
        }

        char *buffer = new char[strlen(ipport) + 1];
        strcpy(buffer, ipport);

        char *host = strtok(buffer, ":");
        char *port = strtok(NULL, ":");

        this->init(host, (uint16_t)atoi(port ? port : "0"));
        delete[] buffer;
    }

}  // namespace CLNetlib
