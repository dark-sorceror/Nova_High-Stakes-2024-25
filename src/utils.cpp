/**
 * \file utils.cpp
 *
 * \brief Contains utility functions
 * 
 * \date Updated - 1/6/2025
 */

#include "utils.h"

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

/**
 * @brief Convert from degree to radians
 *
 * @param value
 * @return float
 */
float Nova::degToRad(float degrees) {
    return degrees * M_PI / 180;
}

/**
 * @brief Convert from radians to degrees
 *
 * @param value
 * @return float
 */
float Nova::radToDeg(float radians) {
    return radians * 180 / M_PI;
}

/**
 * @brief Convert from inches to ticks
 * 
 * @param inches 
 * @return float 
 */
float Nova::inchesToTicks(float inches) {
    // Formula: Number of ticks in one inch = drive RPM / circumference of drive wheel
    return (Nova::driveRPM / (M_PI * Nova::wheelDiameter));
}

/**
 * @brief Convert from ticks to inches
 * 
 * @param ticks 
 * @return float 
 */
float Nova::ticksToInches(float ticks) {
    // Formula: Number of inches in one tick = circumference of drive wheel / drive RPM
    return ((M_PI * Nova::wheelDiameter) / Nova::driveRPM);
}

/**
 * @brief Get the Vertical Distance Traveled object
 * 
 * @return float 
 */
float Nova::getVerticalDistanceTraveled() {
    return (
        (Nova::backLeft.get_position() + Nova::backRight.get_position() + \
            Nova::middleLeft.get_position() + Nova::middleRight.get_position() + \
            Nova::frontLeft.get_position() + Nova::frontRight.get_position()) / 6) * 3.25 * M_PI * (450 / 600);
}

/**
 * @brief Get average of a vector
 * 
 * @param vec 
 * @return double 
 */
double Nova::average(const std::vector<double> &vec) {
    if (vec.empty()) {
        return 0.0;
    }

    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}

/**
 * @brief Calculate average of a vector
 *
 * @param vector Temporary type @typedef 'T' to accept both @typedef int and @typedef float
 * @return float
 */
template <typename T>
constexpr T Nova::average(T vector) {
    if (vector.empty())
        return 0;

    float sum = 0.0;

    for (const auto &value : vector)
        sum += std::visit([](auto &&arg) { return static_cast<float>(arg); }, value);

    return sum / vector.size();
}

/**
 * @brief Get the sign of a value
 *
 * @tparam T
 * @param value
 * @return constexpr T
 */
template <typename T>
constexpr T sgn(T value) {
    return value < 0 ? -1 : 1;
}