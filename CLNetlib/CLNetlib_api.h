#pragma once

namespace CLNetlib
{
#ifdef WIN32
    void win_WSAInitIfNeed();
    extern bool win_isInitialized;
#endif  // WIN32
}  // namespace CLNetlibApi
