/**
 * \file pose.cpp
 *
 * \brief Contains position operations and logic
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include <cmath>

#include "pose.h"

/**
 * @brief Construct a new Nova::Pose::Pose object
 * 
 * @param x 
 * @param y 
 * @param theta 
 */
Nova::Pose::Pose(float x, float y, float theta) {
    this -> x = x;
    this -> y = y;
    this -> theta = theta;
}

/**
 * @brief Matrix addition logic when adding Pose objects
 * 
 * @param other 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Pose::operator+ (const Nova::Pose& other) const {
    return Nova::Pose(
        this -> x + other.x, 
        this -> y + other.y, 
        this -> theta
    );
}

/**
 * @brief Matrix subtraction logic when subtracting Pose objects
 * 
 * @param other 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Pose::operator- (const Nova::Pose& other) const {
    return Nova::Pose(
        this -> x - other.x, 
        this -> y - other.y, 
        this -> theta
    );
}

/**
 * @brief Matrix multiplication logic when multiplying Pose objects
 * 
 * @param other 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Pose::operator* (const float& other) const {
    return Nova::Pose(
        this -> x * other, 
        this -> y * other, 
        this -> theta
    );
}

/**
 * @brief Matrix division logic when dividing Pose objects
 * 
 * @param other 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Pose::operator/ (const float& other) const {
    return Nova::Pose(
        this -> x / other, 
        this -> y / other, 
        this -> theta
    );
}

/**
 * @brief Matrix dot product logic when multiplying Pose objects
 * 
 * @param other 
 * @return float 
 */
float Nova::Pose::operator* (const Nova::Pose& other) const { 
    return this -> x * other.x + this -> y * other.y; 
}

/**
 * @brief Euclidean distance of two Pose objects
 * 
 * @param other 
 * @return float 
 */
float Nova::Pose::distance(Nova::Pose other) const { 
    return std::hypot(
        this -> x - other.x, 
        this -> y - other.y
    ); 
}

/**
 * @brief Angle of two Pose objects
 * 
 * @param other 
 * @return float 
 */
float Nova::Pose::angle(Nova::Pose other) const { 
    return std::atan2(other.y - this -> y, other.x - this -> x); 
}

/**
 * @brief A linear interpolation (lerp) of two Pose objects
 * 
 * @param other 
 * @param t 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Pose::lerp(Nova::Pose other, float t) const {
    return Nova::Pose(
        this -> x + (other.x - this -> x) * t, 
        this -> y + (other.y - this -> y) * t, 
        this -> theta
    );
}

/**
 * @brief Rotation of a Pose object
 * 
 * @param angle 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Pose::rotate(float angle) const {
    return Nova::Pose(
        this -> x * std::cos(angle) - this -> y * std::sin(angle), 
        this -> x * std::sin(angle) + this -> y * std::cos(angle), 
        this -> theta
    );
}