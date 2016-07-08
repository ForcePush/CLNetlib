#pragma once

// fuck you, Microsoft

#ifdef WIN32
#include <WS2tcpip.h>

#define CL_SHUTDOWN_SEND SD_SEND
#define CL_SHUTDOWN_RECEIVE SD_RECEIVE
#define CL_SHUTDOWN_BOTH SD_BOTH

#define CL_INVALID_SOCKET INVALID_SOCKET

namespace CLNetlib
{
    typedef SOCKET CLSocket;
    typedef int socklen_t;
}
#else   // linux
#include <unistd.h>   // close
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>    // addrinfo

#define IN_ADDR sockaddr_in
namespace CLNetlib
{
    typedef int CLSocket;
}
#define CL_SHUTDOWN_SEND SHUT_WR
#define CL_SHUTDOWN_RECEIVE SHUT_RD
#define CL_SHUTDOWN_BOTH SHUT_RDWR

#define CL_INVALID_SOCKET -1
#endif
