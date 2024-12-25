/**
 * \file pose.h
 *
 * \brief Contains definitions for pose.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _POSE_H_
#define _POSE_H_

namespace Nova {
    class Pose {
        public:
            float x;
            float y;
            float theta;
            
            /**
             * @brief Construct a new Pose object
             * 
             * @param x 
             * @param y 
             * @param theta 
             */
            Pose(
                float x, 
                float y, 
                float theta = 0
            );

            /**
             * @brief Matrix addition logic when adding Pose objects
             * 
             * @param other 
             * @return Nova::Pose 
             */
            Pose operator+ (const Pose& other) const;

            /**
             * @brief Matrix subtraction logic when adding Pose objects
             * 
             * @param other 
             * @return Nova::Pose 
             */
            Pose operator- (const Pose& other) const;

            /**
             * @brief Matrix multiplication logic when adding Pose objects
             * 
             * @param other 
             * @return Nova::Pose 
             */
            Pose operator* (const float& other) const;

            /**
             * @brief Matrix division logic when adding Pose objects
             * 
             * @param other 
             * @return Nova::Pose 
             */
            Pose operator/ (const float& other) const;

            /**
             * @brief Matrix dot product logic when multiplying Pose objects
             * 
             * @param other 
             * @return float 
             */
            float operator* (const Pose& other) const;

            /**
             * @brief Euclidean distance of two Pose objects
             * 
             * @param other 
             * @return float 
             */
            float distance(Pose other) const;

            /**
             * @brief Angle of two Pose objects
             * 
             * @param other 
             * @return float 
             */
            float angle(Pose other) const;

            /**
             * @brief A linear interpolation (lerp) of two Pose objects
             * 
             * @param other 
             * @param t 
             * @return Nova::Pose 
             */
            Pose lerp(Pose other, float t) const;

            /**
             * @brief Rotation of a Pose object
             * 
             * @param angle 
             * @return Nova::Pose 
             */
            Pose rotate(float angle) const;
    };
}; // namespace Nova

#endif // _POSE_H_