/**
 * \file clamp.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#include "main.h"

bool clampToggle = false;

void Nova::Clamp::run()
{
     if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
    	clampToggle = !clampToggle;
        
		clamp.set_value(clampToggle);
    }
}