/**
 * \file utils.h
 *
 * \brief Contains definitions for utils.cpp
 *
 * \date Updated - 1/6/2025
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include "api.h"

#include "globals.h"

#include <numeric>

namespace Nova {
    float ticksToInches(float ticks);
    float inchesToTicks(float inches);
    
    float degToRad(float degrees);
    float radToDeg(float radians);

    float getVerticalDistanceTraveled();

    template <typename T> constexpr T average(T vector);

    double Nova::average(const std::vector<double> &vec);
} // namespace Nova

#endif // _UTILS_H_