/**
 * \file main.cpp
 *
 * Updated - 11/19/2024
 * Last Successful Test - 11/19/2024
 */

#include "main.h"

void initialize()
{
    lv_obj_t * img = lv_img_create(lv_scr_act());

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0), LV_PART_MAIN);

    lv_img_set_src(img, &logo);

    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {}