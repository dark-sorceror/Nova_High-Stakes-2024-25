/**
 * \file auton.cpp
 *
 * \brief Contains autonomous paths
 * 
 * \date Updated - 2/10/2025
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
    clamp.clamp();
    pros::delay(500);
    intake.start(9200);
    pros::delay(2500);
    intake.stop();
    clamp.unclamp();
    pros::delay(250);
    chassis.translate(10);
    chassis.rotate(80);
    chassis.translate(-30);
    clamp.clamp();
    pros::delay(500);
    chassis.rotate(-130);
    ladyBrown.goToPosition(174);
    intake.raiseIntake();
    chassis.translate(35);
    intake.start(12700);
    intake.lowerIntake();
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
    clamp.clamp();
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