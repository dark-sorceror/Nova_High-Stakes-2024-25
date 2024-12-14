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

#include <variant>
#include <vector>

using Num = std::variant<int, float>;

float average(std::vector<Num> const& v) {

#endif // _UTILS_H_