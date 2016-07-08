#pragma once

#include "targetver.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN

#ifdef _MSC_VER
#pragma warning(disable: 4996)  // strcpy/memcpy/memset may be unsafe
#endif
#endif
