/**
 * \file brain.h
 *
 * \brief Contains brain definitions for brain.cpp
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#ifndef _BRAIN_H_
#define _BRAIN_H_

#include "liblvgl/lvgl.h"

#include "../renders/logo.c"
#include "../renders/logo_2.c"
#include "../renders/field.c"

#include "globals.h"

typedef struct {
    int x;
    int y;
} Coordinates;

typedef enum {
    BLUE_1,
    BLUE_2,
    RED_1,
    RED_2
} Auton;

typedef enum {
    BTN_MATCH,
    BTN_BACK,
    BTN_BACK_2,
    BTN_TESTING,
    BTN_ROBOT,
    BTN_DEFAULT,
    BTN_BLUE_1,
    BTN_BLUE_2,
    BTN_RED_1,
    BTN_RED_2,
    BTN_CONFIRM,
    BTN_UNKNOWN
} ButtonType;

LV_IMG_DECLARE(logo);
LV_IMG_DECLARE(logo_2);
LV_IMG_DECLARE(field);

extern lv_obj_t * s_logo_screen;
extern lv_obj_t * s_home_screen;
extern lv_obj_t * s_match_screen;
extern lv_obj_t * s_testing_screen;
extern lv_obj_t * s_robot_screen;

extern int autonSelected;

void home_screen(void);
void match_screen(void);
void logo_screen(void);
void testing_screen(void);
void robot_screen(void);

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
);

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
);

/**
 * @brief Display version
 * 
 * @param screen 
 */
static void version(lv_obj_t * screen);

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
);

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
);

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
);

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
);

namespace Nova {
    class Brain {
        public:
            /**
             * @brief Initialize Brain
             * 
             */
            void initialize(void);
    };

}; // namespace Nova

#endif // _BRAIN_H_