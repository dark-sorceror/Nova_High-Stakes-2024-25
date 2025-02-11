/**
 * \file ladyBrown.h
 *
 * \brief Contains definitions for ladyBrown.cpp
 * 
 * \date Updated - 1/20/2025
 */

#ifndef _LADYBROWN_H_
#define _LADYBROWN_H_

#include "pros/misc.h"
#include "pros/rtos.hpp"

#include "globals.h"

namespace Nova {
    class LadyBrown {
        public:
            void goToPosition(int position);
            void initialize();
            void run();
    };
} // namespace Nova

#endif // _LADYBROWN_H_