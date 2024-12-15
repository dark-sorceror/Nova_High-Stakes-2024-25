/**
 * \file globals.h
 *
 * \brief Contains global system definitions for globals.cpp
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#ifndef _UTILS_H_
#define _UTILS_H_

/**
 * @brief Get the sign of a value
 * 
 * @tparam T 
 * @param value 
 * @return constexpr T 
 */
template <typename T> constexpr T sgn(T value) { return value < 0 ? -1 : 1; }

#endif // _UTILS_H_