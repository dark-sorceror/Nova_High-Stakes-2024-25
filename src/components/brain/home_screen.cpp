#include "components/brain.h"

/**
 * @brief Home screen
 * 
 */
static void home_screen(void) {
    s_home_screen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(s_home_screen, lv_color_hex(0), LV_PART_MAIN);

    image(s_home_screen, &logo_2, LV_ALIGN_LEFT_MID, {35, 0});

    button(s_home_screen, 180, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-37, -60}, "Match", lv_color_hex(0xFFFFFFF), BTN_MATCH);
    button(s_home_screen, 180, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-37, 0}, "Testing", lv_color_hex(0xFFFFFFF), BTN_TESTING);
    button(s_home_screen, 180, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-37, 60}, "Default", lv_color_hex(0xFFFFFFF), BTN_DEFAULT);

    version(s_home_screen);
}