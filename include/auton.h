/**
 * \file auton.h
 *
 * Updated - 11/30/2024
 * Last Successful Test -
 */ 

#ifndef __AUTON
#define __AUTON

#include "chassis/drive.h"
#include "subsystems/intake.h"
#include "PID.h"
#include <iostream>
#include <map>
#include <list>

namespace Nova {
    class Auton {
        public: 
            Auton(Drive drive, Intake intake);

            void test();
        private:
            Drive drive;
            Intake intake;

            //void trackPosition(int left, int right);
            void translate(float dist);
            void setPath(std::list < std::pair < std::string, float > > path);
            void rotate(float angle);
            void rotateAbsolute(float angle);
            void swerveLeft(float dist, float angle);
            void swerveRight(float dist, float angle);
    };
}

#endif