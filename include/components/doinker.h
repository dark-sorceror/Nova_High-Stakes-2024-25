/**
 * \file doinker.h
 *
 * \brief Contains definitions for doinker.cpp
 * 
 * \date Updated - 9/1/2025
 */

#ifndef _DOINKER_H_
#define _DOINKER_H_

#include "globals.h"

namespace Nova {
    class Doinker {
        public:
            void extend();
            void retract();

            void run();
    };
} // namespace Nova

#endif // _DOINKER_H_