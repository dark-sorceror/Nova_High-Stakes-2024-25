/**
 * \file utility.h
 *
 * \brief Contains definitions for utility.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include "api.h"

#include <numeric>

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

/**
 * @brief Get the sign of a value
 * 
 * @tparam T 
 * @param value 
 * @return constexpr T 
 */
template <typename T> constexpr T sgn(T value) { 
    return value < 0 ? -1 : 1; 
}

constexpr double average(const std::vector<double>& vec) {
    if (vec.empty()) {
        return 0.0;
    }

    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}

float ticksToInches(float ticks);
float inchesToTicks(float inches);

/**
 * @brief Calculate average of a vector
 * 
 * @param vector Temporary type @typedef 'T' to accept both @typedef int and @typedef float
 * @return float 
 */
template <typename T> constexpr T average(T vector) {
    if (vector.empty()) return 0;

    float sum = 0.0;
    
    for (const auto& value : vector) sum += std::visit([](auto&& arg) { return static_cast<float>(arg); }, value);

    return sum / vector.size();
}

#endif // _UTILS_H_