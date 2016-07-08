#include "stdafx.h"
#include "CLNetlib_api.h"
#include "CLSocket.h"

namespace CLNetlib
{
#ifdef WIN32
    void win_WSAInitIfNeed()
    {
        if (win_isInitialized) {
            return;
        }

        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            return;
        }

        win_isInitialized = true;
    }

    bool win_isInitialized = false;
#endif  // WIN32
}  // namespace CLNetlibApi
