/**
 * \file auton.cpp
 *
 * \brief Contains autonomous paths
 * 
 * \date Updated - 1/6/2025
 */

#include "auton.h"

/**
 * @brief Construct a new Nova::Auton::Auton object
 *
 * @param chassis
 * @param intake
 * @param clamp
 */
Nova::Auton::Auton(
    Nova::Chassis chassis,
    Nova::Intake intake,
    Nova::Clamp clamp,
    Nova::LadyBrown ladyBrown
): 
    chassis(chassis),
    intake(intake),
    clamp(clamp),
    ladyBrown(ladyBrown)
{};

/*
pidConstants _180 {
    .p = 5.9,
    .i = 0.6,
    .d = 70,
    .tolerance = 0.05,
    .integralThreshold = 1.1,
    .maxIntegral = 20
};

pidConstants _135 {
    .p = 6.3,
    .i = 0.43,
    .d = 59,
    .tolerance = 0.01,
    .integralThreshold = 1,
    .maxIntegral = 100
};


pidConstants _90 {
    .p = 6.3,
    .i = 0.43,
    .d = 59,
    .tolerance = 0.01,
    .integralThreshold = 1,
    .maxIntegral = 100
};

pidConstants _45 {
    .p = 4.9,
    .i = 0.4,
    .d = 26,
    .tolerance = 0.01,
    .integralThreshold = 1.1,
    .maxIntegral = 100
};

pidConstants _30 {
    .p = 5.9,
    .i = 0.6,
    .d = 70,
    .tolerance = 0.05,
    .integralThreshold = 1.1,
    .maxIntegral = 20
};

pidConstants _15 {
    .p = 4.9,
    .i = 0.4,
    .d = 26,
    .tolerance = 0.01,
    .integralThreshold = 1.1,
    .maxIntegral = 100
};

pidConstants _5 {
    .p = 4.9,
    .i = 0.4,
    .d = 26,
    .tolerance = 0.01,
    .integralThreshold = 1.1,
    .maxIntegral = 100
};

pidConstants _arc {
    .p = 1.7,
    .i = 0.2,
    .d = 2,
    .tolerance = 0,
    .integralThreshold = 3,
    .maxIntegral = 100
};

pidConstants _eul {
    .p = 1,
    .i = 0,
    .d = 0,
    .tolerance = 0,
    .integralThreshold = 3,
    .maxIntegral = 100
};

pidConstants _eulF {
    .p = 1.5,
    .i = 0,
    .d = 0,
    .tolerance = 0,
    .integralThreshold = 3,
    .maxIntegral = 100
};


pidConstants _lin {
    .p = 0.13,
    .i = 0,
    .d = 0,
    .tolerance = 0,
    .integralThreshold = 0,
    .maxIntegral = 0
};

pidConstants _ang {
    .p = 1.4,
    .i = 0,
    .d = 0,
    .tolerance = 0,
    .integralThreshold = 0,
    .maxIntegral = 0
};

pidConstants _angBig {
    .p = 2.5,
    .i = 0,
    .d = 0,
    .tolerance = 0,
    .integralThreshold = 0,
    .maxIntegral = 0
};
 */

 /*
 4 SCORED rings 
 3 stakes on alliance side
  1 ring on aaliiNCE WALL stake
 */

void Nova::Auton::test() {
    chassis.translate(42);
    intake.start(9200);

    chassis.rotate(30);
    doinker.set_value(1);
    intake.stop();
    chassis.translate(-20);
    doinker.set_value(0);
    pros::delay(250);
    chassis.rotate(-170);
    chassis.translate(-25);
    clamp.lock();
    pros::delay(500);
    intake.start(9200);
    pros::delay(2500);
    intake.stop();
    clamp.unlock();
    pros::delay(250);
    chassis.translate(10);
    chassis.rotate(80);
    chassis.translate(-30);
    clamp.lock();
    pros::delay(500);
    chassis.rotate(-130);
    ladyBrown.goToPosition(174);
    intake.extendGoalRush();
    chassis.translate(35);
    intake.start(12700);
    intake.retractGoalRush();
    intake.stop();
    intake.start(12700);
    intake.stop();
    intake.start(12700);
    intake.stop();
    chassis.rotate(40);
    chassis.translate(15);
    pros::delay(250);
    ladyBrown.goToPosition(290);
    pros::delay(250);
    ladyBrown.goToPosition(350);
    pros::delay(250);
    ladyBrown.goToPosition(150);
    chassis.translate(-15);
    chassis.rotate(90);
    intake.start(9200);
    chassis.translate(72);
    intake.stop();
    chassis.rotate(-45);
    chassis.translate(25);
    doinker.set_value(1);
    chassis.rotate(-90);

}

void Nova::Auton::skills() {
    ladyBrown.goToPosition(290);
    pros::delay(250);
    ladyBrown.goToPosition(350);
    pros::delay(250);
    ladyBrown.goToPosition(150);
    chassis.translate(-18);
    clamp.lock();
    pros::delay(250);
    chassis.rotate(-145);
    intake.start(9200);
    chassis.translate(16);
    chassis.rotate(95);
    chassis.translate(10);
    chassis.rotate(-130);
    chassis.translate(10);
    chassis.rotate(-45);
    chassis.translate(45);
    ladyBrown.goToPosition(174);
    intake.stop();
    intake.start(12700);
    intake.stop();
    intake.start(12700);
    pros::delay(250);
    intake.stop();
    chassis.rotate(90);
    pros::delay(250);
    intake.stop();
    pros::delay(250);
    ladyBrown.goToPosition(250);
    pros::delay(250);
    ladyBrown.goToPosition(350);
    pros::delay(250);
    ladyBrown.goToPosition(150);




}