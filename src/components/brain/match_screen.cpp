#include "components/brain.h"

/**
 * @brief Match screen
 * 
 */
static void match_screen(void) {
    s_match_screen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(s_match_screen, lv_color_hex(0), LV_PART_MAIN);

    image(s_match_screen, &field, LV_ALIGN_CENTER, {0, 0});
    
    //redo later
    static lv_point_t line_points_1[] = {
        {320, 80},
        {340, 55},
        {400, 55},
    };

    static lv_point_t line_points_2[] = {
        {160, 80},
        {140, 55},
        {100, 55},
    };

    static lv_point_t line_points_3[] = {
        {320, 160},
        {340, 185},
        {400, 185},
    };

    static lv_point_t line_points_4[] = {
        {160, 160},
        {140, 185},
        {100, 185},
    };

    lv_obj_t * line = lv_line_create(s_match_screen);

    lv_line_set_points(line, line_points_1, 3);
    lv_obj_set_style_line_width(line, 2, LV_PART_MAIN);

    lv_obj_t * line2 = lv_line_create(s_match_screen);

    lv_line_set_points(line2, line_points_2, 3);
    lv_obj_set_style_line_width(line2, 2, LV_PART_MAIN);

    lv_obj_t * line3 = lv_line_create(s_match_screen);

    lv_line_set_points(line3, line_points_3, 3);
    lv_obj_set_style_line_width(line3, 2, LV_PART_MAIN);

    lv_obj_t * line4 = lv_line_create(s_match_screen);

    lv_line_set_points(line4, line_points_4, 3);
    lv_obj_set_style_line_width(line4, 2, LV_PART_MAIN);

    back_btn(s_match_screen, LV_ALIGN_LEFT_MID, {25, 0}, lv_color_hex(0xFFFFFF));

    button(s_match_screen, 95, 60, 2, lv_color_hex(0x0096FF), lv_color_hex(0), LV_ALIGN_TOP_RIGHT, {-25, 25}, NULL, lv_color_hex(0xFFFFFFF), BTN_BLUE_1);
    button(s_match_screen, 95, 60, 2, lv_color_hex(0x0096FF), lv_color_hex(0), LV_ALIGN_BOTTOM_RIGHT, {-25, -25}, NULL, lv_color_hex(0xFFFFFFF), BTN_BLUE_2);
    button(s_match_screen, 95, 60, 2, lv_color_hex(0xEE4B2B), lv_color_hex(0), LV_ALIGN_TOP_LEFT, {25, 25}, NULL, lv_color_hex(0xFFFFFFF), BTN_RED_1);
    button(s_match_screen, 95, 60, 2, lv_color_hex(0xEE4B2B), lv_color_hex(0), LV_ALIGN_BOTTOM_LEFT, {25, -25}, NULL, lv_color_hex(0xFFFFFFF), BTN_RED_2);
}
