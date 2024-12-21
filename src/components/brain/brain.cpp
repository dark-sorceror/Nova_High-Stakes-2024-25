/**
 * \file brain.cpp
 *
 * \brief Contains lvgl implementation for auton planner logic on brain
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include "components/brain.h"

static void btn_event_handler(lv_event_t * e);

/**
 * @brief Create back button
 * 
 * @param screen 
 * @param align 
 * @param offset 
 * @param label_color 
 */
static void back_btn(
    lv_obj_t * screen,
    lv_align_t align,
    Coordinates offset,
    lv_color_t
    label_color
) {
    lv_obj_t * back_btn = lv_btn_create(screen);
    lv_obj_t * back_text = lv_label_create(back_btn);

    lv_obj_add_event_cb(back_btn, btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0), LV_PART_MAIN);
    lv_obj_align(back_btn, align, offset.x, offset.y);
    lv_obj_set_user_data(back_btn, (lv_obj_user_data_t)(intptr_t)BTN_BACK);

    lv_label_set_text(back_text, "Back");
    lv_obj_set_style_text_color(back_text, label_color, LV_PART_MAIN);
}

/**
 * @brief Create back button 2
 * 
 * @param screen 
 * @param align 
 * @param offset 
 * @param label_color 
 */
static void back_btn_2(
    lv_obj_t * screen,
    lv_align_t align,
    Coordinates offset,
    lv_color_t
    label_color
) {
    lv_obj_t * back_btn = lv_btn_create(screen);
    lv_obj_t * back_text = lv_label_create(back_btn);

    lv_obj_add_event_cb(back_btn, btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0), LV_PART_MAIN);
    lv_obj_align(back_btn, align, offset.x, offset.y);
    lv_obj_set_user_data(back_btn, (lv_obj_user_data_t)(intptr_t)BTN_BACK_2);

    lv_label_set_text(back_text, "Back");
    lv_obj_set_style_text_color(back_text, label_color, LV_PART_MAIN);
}

/**
 * @brief Display version
 * 
 * @param screen 
 */
static void version(lv_obj_t * screen) {
    lv_obj_t * text = lv_label_create(screen);
    lv_label_set_text(text, Nova::VERSION);
    lv_obj_align(text, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
}

/**
 * @brief Create Button
 * 
 * @param screen 
 * @param width 
 * @param height 
 * @param border_width 
 * @param border_color 
 * @param bg_color 
 * @param align 
 * @param offset 
 * @param label 
 * @param label_color 
 * @param btn_id 
 */
static void button(
    lv_obj_t * screen,
    int width,
    int height,
    int border_width,
    lv_color_t border_color,
    lv_color_t bg_color,
    lv_align_t align,
    Coordinates offset,
    const char * label,
    lv_color_t label_color,
    ButtonType btn_id
) {
    lv_obj_t * btn = lv_btn_create(screen);

    lv_obj_set_width(btn, width);
    lv_obj_set_height(btn, height);

    lv_obj_set_style_border_width(btn, border_width, LV_PART_MAIN);
    lv_obj_set_style_border_color(btn, border_color, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, bg_color, LV_PART_MAIN);
    lv_obj_align(btn, align, offset.x, offset.y);
    lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_user_data(btn, (lv_obj_user_data_t)(intptr_t)btn_id);

    if (label) {
        lv_obj_t * label_match = lv_label_create(btn);
        lv_label_set_text(label_match, label);
        lv_obj_align(label_match, LV_ALIGN_CENTER, 0, 0);
    }
}

/**
 * @brief Create text
 * 
 * @param screen 
 * @param text 
 * @param color 
 * @param align 
 * @param offset 
 */
static void text(
    lv_obj_t * screen,
    const char * text,
    lv_color_t color,
    lv_align_t align,
    Coordinates offset
) {
    lv_obj_t * textLabel = lv_label_create(screen);

    lv_label_set_text(textLabel, text);

    if (color.full != lv_color_hex(0).full) {
        lv_obj_set_style_text_color(textLabel, color, LV_PART_MAIN);
    }

    lv_obj_align(textLabel, align, offset.x, offset.y);
}

/**
 * @brief Determine text color
 * 
 * @param value 
 * @param sign 
 * @param green 
 * @param yellow 
 * @return lv_color_t 
 */
static lv_color_t determine_text_color(
    int value, 
    int sign, 
    int green, 
    int yellow
) {
    if (value >= 1) return lv_color_hex(0x32CD32); // green
    else if (value == 0) return lv_color_hex(0xD22B2B); // red
    else if (value == -1) return lv_color_hex(0x353935); // grey
    
    if (sign > 0 ? value >= green : value <= green) return lv_color_hex(0x32CD32); // green
    else if (sign > 0 ? value >= yellow : value <= yellow) return lv_color_hex(0xFFEA00); // yellow
    else return lv_color_hex(0xD22B2B); // red
}

/**
 * @brief Create image
 * 
 * @param screen 
 * @param ptr_img 
 * @param align 
 * @param offset 
 */
static void image(
    lv_obj_t * screen,
    const lv_img_dsc_t * ptr_img,
    lv_align_t align,
    Coordinates offset
) {
    lv_obj_t * img = lv_img_create(screen);

    lv_img_set_src(img, ptr_img);

    lv_obj_align(img, align, offset.x, offset.y);
}

/**
 * @brief Button event handler
 * 
 * @param e 
 */
static void btn_event_handler(lv_event_t * e) {
    lv_obj_t * btn = lv_event_get_target(e);

    ButtonType btn_type = (ButtonType)(intptr_t)lv_obj_get_user_data(btn); 

    switch (btn_type) {
        case BTN_MATCH:
            match_screen();
            lv_scr_load(s_match_screen);

            break;

        case BTN_BACK:
            home_screen();
            lv_scr_load(s_home_screen);

            break;

        case BTN_BACK_2:
            testing_screen();
            lv_scr_load(s_testing_screen);

            break;

        case BTN_TESTING:
            testing_screen();
            lv_scr_load(s_testing_screen);

            break;

        case BTN_ROBOT:
            robot_screen();
            lv_scr_load(s_robot_screen);

            break;

        case BTN_DEFAULT:
            logo_screen();
            lv_scr_load(s_logo_screen);

            break;

        case BTN_BLUE_1:
            autonSelected = Auton::BLUE_1;

            testing_screen();
            lv_scr_load(s_testing_screen);

            break;

        case BTN_BLUE_2:
            autonSelected = Auton::BLUE_2;

            testing_screen();
            lv_scr_load(s_testing_screen);
            
            break;

        case BTN_RED_1:
            autonSelected = Auton::RED_1;

            testing_screen();
            lv_scr_load(s_testing_screen);
            
            break;

        case BTN_RED_2:
            autonSelected = Auton::RED_2;

            testing_screen();
            lv_scr_load(s_testing_screen);

            break;

        case BTN_CONFIRM:
            logo_screen();
            lv_scr_load(s_logo_screen);

            if (autonSelected = Auton::BLUE_1) //run auton

            break;

        default:
            break;
    }
}

/**
 * @brief Initialize
 * 
 */
void Nova::Brain::initialize(void) {
    lv_init();

    home_screen();

    lv_scr_load(s_home_screen);
}