/**
 * \file odom.h
 *
 * Updated - 11/30/2024
 * Last Successful Test - 
 */ 

#include "main.h"

namespace Nova
{
	extern void updateOdometry();
    extern void moveToPos(double target_x, double target_y, double target_theta);
}