/**
 * \file utils.h
 *
 * \brief Contains miscellaneous functions
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
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
template <typename T> constexpr T sgn(T value) { 
    return value < 0 ? -1 : 1; 
}

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