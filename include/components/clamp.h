/**
 * \file clamp.h
 *
 * \brief Contains definitions for clamp.cpp
 * 
 * \date Updated - 2/10/2025
 */ 

#ifndef _CLAMP_H_
#define _CLAMP_H_

#include "globals.h"

namespace Nova {
    class Clamp {
        public:
            void clamp();
            void unclamp();
            void run();
    };
} // namespace Nova

#endif // _CLAMP_H_