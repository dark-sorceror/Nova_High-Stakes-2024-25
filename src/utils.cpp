#include "globals.h"

#include "utils.h"

float inchesToTicks(float value) {
    // Formula: Number of ticks in one inch = drive RPM / circumference of drive wheel
    return (Nova::driveRPM / (M_PI * Nova::wheelDiameter));
}

float ticksToInches(float ticks) {
    // Formula: Number of inches in one tick = circumference of drive wheel / drive RPM
    return ((M_PI * Nova::wheelDiameter) / Nova::driveRPM);
}
