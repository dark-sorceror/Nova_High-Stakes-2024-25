/**
 * \file odom.h
 *
 * \brief Contains odometry definitions for odom.cpp
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#ifndef _ODOM_H_
#define _ODOM_H_

#include "main.h"

namespace Nova {
    /**
     * @brief Get the Pose object
     * 
     * @param radians 
     * @return Pose 
     */
    Pose getPose(bool radians = false);

    /**
     * @brief Set the Pose object
     * 
     * @param pose 
     * @param radians 
     */
    void setPose(Pose pose, bool radians = false);
    
    /**
     * @brief Tracking Algorithm Loop
     * 
     */
    void update();
}; // namespace Nova

#endif // _ODOM_H_