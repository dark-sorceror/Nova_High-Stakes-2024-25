/**
 * \file clamp.h
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#ifndef __CLAMP
#define __CLAMP

namespace Nova {
    class Clamp {
        public:
            void open();

            void close();

            void toggle();

            void run();
        private:           
            bool active = false;
    };
}

#endif