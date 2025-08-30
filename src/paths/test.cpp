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
/*
    ladyBrown.goToPosition(355);
    pros::delay(500);
    chassis.translate(-16);
    clamp.clamp();
    ladyBrown.goToPosition(184);
    intake.start(-9200);
    chassis.rotate(-129);
    chassis.translate(25);
    chassis.rotate(-29);
    //pros::delay(5000);
    chassis.translate(75);
    //pros::delay(5000);
    pros::delay(350);
    ladyBrown.goToPosition(200);
    chassis.translate(-38);
    chassis.rotate(25);
   // pros::delay(5000);
    chassis.translate(-12);
    intake.stop();
    chassis.rotate(-80);
    chassis.translate(18);
    chassis.translate(-3);
    */
   /*
   ladyBrown.goToPosition(200);
    intake.start(3500);
    pros::delay(50);
    intake.stop();
    pros::delay(500);
    ladyBrown.goToPosition(350);
    pros::delay(100);
    intake.start(-9200);
    pros::delay(600);
    ladyBrown.goToPosition(200);
    intake.stop();
    pros::delay(1000);
    intake.start(3500);
    pros::delay(50);
    intake.stop();
    pros::delay(500);
    ladyBrown.goToPosition(350);
    pros::delay(600);
    ladyBrown.goToPosition(184);
    */
    clamp.clamp();
    chassis.translate(-10);
    chassis.rotate(-90);
    intake.start(-10550);
    chassis.translate(60, 100);
    pros::delay(1000);
    chassis.rotate(135);
    chassis.translate(12);
    chassis.rotate(90);
    chassis.translate(-10);
    intake.stop();
    clamp.unclamp();
    chassis.translate(12);
    chassis.rotate(-132);
    chassis.translate(-55);
    clamp.clamp();
    
   /*
    chassis.rotate(45);
    intake.start(-9200);
    chassis.translate(48);
    pros::delay(5000);
    chassis.rotate(-74);
    pros::delay(5000);
    chassis.translate(75);
    //pros::delay(5000);
    pros::delay(350);
    ladyBrown.goToPosition(200);
    chassis.translate(-38);
    chassis.rotate(-25);
   // pros::delay(5000);
    chassis.translate(-12);
    intake.stop();
    chassis.rotate(80);
    chassis.translate(18);
    chassis.translate(-3);
    //
    intake.start(12000);
    pros::delay(50);
    intake.stop();
    ladyBrown.goToPosition(350);
    pros::delay(100);
    intake.start(-9200);
    pros::delay(900);
    ladyBrown.goToPosition(200);
    intake.stop();
    pros::delay(1000);
    intake.start(12000);
    pros::delay(50);
    intake.stop();
    ladyBrown.goToPosition(350);
    pros::delay(1000);
    ladyBrown.goToPosition(184);
    */
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
    intake.start(10000);
    intake.stop();
    intake.start(10000);
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