#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "common.h"

namespace resimutil
{
    inline bool Contains(const char *a, const char *b)
    {
        std::string tmpA = a;
        return tmpA.find(b) != std::string::npos;
    }
}

#endif // UTILITY_H_INCLUDED
