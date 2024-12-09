/**
 * \file pose.h
 *
 * \brief Contains pose object definitions for pose.cpp
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#ifndef _POSE_H_
#define _POSE_H_

namespace Nova {
    class Pose {
        public:
            float x;
            float y;
            float theta;

            Pose(
                float x, 
                float y, 
                float theta = 0
            );

            Pose operator+ (const Pose& other) const;
            Pose operator- (const Pose& other) const;
            Pose operator* (const float& other) const;
            Pose operator/ (const float& other) const;
            float operator* (const Pose& other) const;

            float distance(Pose other) const;
            float angle(Pose other) const;

            Pose lerp(Pose other, float t) const;
            Pose rotate(float angle) const;
    };
}; // namespace Nova

#endif // _POSE_H_