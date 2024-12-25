/**
 * \file clamp.h
 *
 * \brief Contains definitions for clamp.cpp
 * 
 * \date Updated - 12/25/2024
 */ 

#ifndef _CLAMP_H_
#define _CLAMP_H_

namespace Nova {
    class Clamp {
        public:
            void lock();
            void unlock();
            void run();
    };
} // namespace Nova

#endif // _CLAMP_H_