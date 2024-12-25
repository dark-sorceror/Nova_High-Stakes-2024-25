/**
 * \file odom.h
 *
 * \brief Contains definitions for odom.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _ODOM_H_
#define _ODOM_H_

#include "pose.h"

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