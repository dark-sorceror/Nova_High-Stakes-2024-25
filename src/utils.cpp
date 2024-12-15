/**
 * \file utils.cpp
 *
 * \brief Contains position operations and logic
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include "main.h"
#include <variant>

using Num = std::variant<int, float>;

/**
 * @brief Calculate average of a vector
 * 
 * @param v Temporary type @typedef 'Num' to accept both @typedef int and @typedef float
 * @return float 
 */
float average(std::vector<Num> const& v) {
    if (v.empty()) return 0;

    float sum = 0.0;
    
    for (const auto& value : v) sum += std::visit([](auto&& arg) { return static_cast<float>(arg); }, value);

    return sum / v.size();
}