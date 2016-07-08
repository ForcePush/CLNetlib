#include "stdafx.h"
#include "UDPSocket.h"
#include "UDPConnection.h"
#include "CLNetlib_api.h"

namespace CLNetlib
{
    UDPSocket::UDPSocket(uint16_t port, unsigned long readTimeoutMs) :
        listenPort(port),
        AbstractSocket(readTimeoutMs)
    {
    }

    UDPSocket::UDPSocket() :
        listenPort(0),
        AbstractSocket(0)
    {
    }

    UDPSocket::~UDPSocket()
    {
    }

    int UDPSocket::send(const std::string & ipport, const char *msg, size_t msgLen) const
    {
        return UDPSocket::send(Addr(ipport), msg, msgLen);
    }

    int UDPSocket::send(const std::string & ip, uint16_t port, const char *msg, size_t msgLen) const
    {
        return UDPSocket::send(Addr(ip, port), msg, msgLen);
    }

    int UDPSocket::send(const Addr & addr, const char *msg, size_t msgLen) const
    {
        return ::sendto(this->sock, msg, msgLen, 0, addr, addr.getSockaddrLen());
    }

    int UDPSocket::send(const std::string & ipport, const std::string & msg) const
    {
        return UDPSocket::send(ipport, msg.c_str(), msg.length());
    }

    int UDPSocket::send(const std::string & ip, uint16_t port, const std::string & msg) const
    {
        return UDPSocket::send(ip, port, msg.c_str(), msg.length());
    }

    int UDPSocket::send(const Addr & addr, const std::string & msg) const
    {
        return UDPSocket::send(addr, msg.c_str(), msg.length());
    }

    std::shared_ptr<AbstractConnection> UDPSocket::recv(size_t maxLength)
    {
        std::string data;
        char *buffer = new char[maxLength];

        struct sockaddr saddr;
        memset(&saddr, 0, Addr::getSockaddrLen());
        
        int saddrLen = Addr::getSockaddrLen();
        int retLen = ::recvfrom(this->sock, buffer, maxLength, 0, &saddr, &saddrLen);

        if (retLen >= 0) {
            data = std::string(buffer, retLen);
        }

        return std::shared_ptr<AbstractConnection>(new UDPConnection(Addr(&saddr), data));
    }

    void UDPSocket::createSocket()
    {
#ifdef WIN32
        CLNetlib::win_WSAInitIfNeed();
#endif  // WIN32

        this->sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (this->sock == INVALID_SOCKET)
        {
            throw std::runtime_error("UDPServer: cannot create socket.");
            return;
        }

        if (this->listenPort != 0) {
            Addr localAddr = Addr("0.0.0.0", this->listenPort);
            if (bind(this->sock, localAddr, localAddr.getSockaddrLen()) == -1)
            {
                throw std::runtime_error("UDPServer: bind failed.");
                return;
            }
        }
    }

    void UDPSocket::closeSocket()
    {
#ifdef WIN32
        closesocket(this->sock);
#else  // WIN32
        close(this->sock);
#endif  // WIN32
    }
}
