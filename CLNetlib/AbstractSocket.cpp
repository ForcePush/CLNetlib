#include "stdafx.h"
#include "AbstractSocket.h"


namespace CLNetlib
{
    AbstractSocket::AbstractSocket()
    {
        this->createSocket();
    }

    AbstractSocket::AbstractSocket(unsigned long readTimeoutMs)
    {
        this->createSocket();
        this->setReadTimeout(readTimeoutMs);
    }

    AbstractSocket::AbstractSocket(CLSocket sock, unsigned long readTimeoutMs) :
        sock(sock),
        readTimeoutMs(readTimeoutMs)
    {
        this->setReadTimeout(readTimeoutMs);
    }


    AbstractSocket::~AbstractSocket()
    {
        this->closeSocket();
    }

    int AbstractSocket::setReadTimeout(unsigned long msec)
    {
#ifdef WIN32
        return setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&msec, sizeof(unsigned long));
#else  // WIN32
        struct timeval tv;
        tv.tv_sec = msec / 1000;
        tv.tv_usec = long(msec % 1000) * 1000L;
        return setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));
#endif  // WIN32
    }
}
