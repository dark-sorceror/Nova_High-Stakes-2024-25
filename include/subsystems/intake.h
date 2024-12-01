/**
 * \file intake.h
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#ifndef __INTAKE
#define __INTAKE

namespace Nova {
    class Intake {
        public:
            void initialize();
            void spinRevolutions(int revolutions);
            void run();
        private:
            bool intakeActive = false;
    };
}

#endif