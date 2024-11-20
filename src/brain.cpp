/**
 * \file brain.cpp
 *
 * Updated - 11/19/2024
 * Last Successful Test - 11/19/2024
 */

#include "main.h"

static void btn_event_handler(lv_event_t * e);

static void home_screen(void);
static void match_screen(void);
static void logo_screen(void);

lv_obj_t * s_logo_screen;
lv_obj_t * s_home_screen;
lv_obj_t * s_match_screen;

typedef struct
{
    int x;
    int y;
} Coordinates;

typedef enum
{
    BTN_MATCH,
    BTN_BACK,
    BTN_TESTING,
    BTN_DEFAULT,
    BTN_BLUE_1,
    BTN_BLUE_2,
    BTN_RED_1,
    BTN_RED_2,
    BTN_UNKNOWN
} ButtonType;

static void back_btn(
    lv_obj_t * screen,
    lv_align_t align,
    Coordinates offset,
    lv_color_t
    label_color
)
{
    lv_obj_t * back_btn = lv_btn_create(screen);
    lv_obj_t * back_text = lv_label_create(back_btn);

    lv_obj_add_event_cb(back_btn, btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0), LV_PART_MAIN);
    lv_obj_align(back_btn, align, offset.x, offset.y);
    lv_obj_set_user_data(back_btn, (lv_obj_user_data_t)(intptr_t)BTN_BACK);

    lv_label_set_text(back_text, "Back");
    lv_obj_set_style_text_color(back_text, label_color, LV_PART_MAIN);
}

static void version(lv_obj_t * screen)
{
    lv_obj_t * text = lv_label_create(screen);
    lv_label_set_text(text, Nova::VERSION);
    lv_obj_align(text, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
}

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
)
{
    lv_obj_t * btn = lv_btn_create(screen);

    lv_obj_set_width(btn, width);
    lv_obj_set_height(btn, height);

    lv_obj_set_style_border_width(btn, border_width, LV_PART_MAIN);
    lv_obj_set_style_border_color(btn, border_color, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, bg_color, LV_PART_MAIN);
    lv_obj_align(btn, align, offset.x, offset.y);
    lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_user_data(btn, (lv_obj_user_data_t)(intptr_t)btn_id);

    if (label)
    {
        lv_obj_t * label_match = lv_label_create(btn);
        lv_label_set_text(label_match, label);
        lv_obj_align(label_match, LV_ALIGN_CENTER, 0, 0);
    }
}

static void image(
    lv_obj_t * screen,
    const lv_img_dsc_t * ptr_img,
    lv_align_t align,
    Coordinates offset
)
{
    lv_obj_t * img = lv_img_create(screen);

    lv_img_set_src(img, ptr_img);

    lv_obj_align(img, align, offset.x, offset.y);
}


static void btn_event_handler(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);

    ButtonType btn_type = (ButtonType)(intptr_t)lv_obj_get_user_data(btn); 

    switch (btn_type)
    {
    case BTN_MATCH:
        match_screen();
        lv_scr_load(s_match_screen);

        break;

    case BTN_BACK:
        home_screen();
        lv_scr_load(s_home_screen);

        break;

    case BTN_TESTING:
        printf("Testing button pressed\n");

        break;

    case BTN_DEFAULT:
        logo_screen();
        lv_scr_load(s_logo_screen);

        break;

    case BTN_BLUE_1:
        printf("Blue far side button pressed\n");

        break;

    case BTN_BLUE_2:
        printf("Blue close side button pressed\n");

        break;

    case BTN_RED_1:
        printf("Red far side button pressed\n");

        break;

    case BTN_RED_2:
        printf("Red close side button pressed\n");

        break;

    default:
        printf("Unknown button pressed\n");

        break;
    }
}

static void home_screen(void)
{
    s_home_screen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(s_home_screen, lv_color_hex(0), LV_PART_MAIN);

    image(s_home_screen, &logo_2, LV_ALIGN_LEFT_MID, {25, 0});

    button(s_home_screen, 170, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-25, -60}, "Match", lv_color_hex(0xFFFFFFF), BTN_MATCH);
    button(s_home_screen, 170, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-25, 0}, "Testing", lv_color_hex(0xFFFFFFF), BTN_TESTING);
    button(s_home_screen, 170, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-25, 60}, "Default", lv_color_hex(0xFFFFFFF), BTN_DEFAULT);

    version(s_home_screen);
}

static void logo_screen(void)
{
    s_logo_screen = lv_obj_create(NULL);

    image(s_logo_screen, &logo, LV_ALIGN_CENTER, {0, 0});

    back_btn(s_logo_screen, LV_ALIGN_TOP_LEFT, {0, 0}, lv_color_hex(0));
}

static void match_screen(void)
{
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

void Nova::Brain::initialize(void)
{
    lv_init();

    home_screen();

    lv_scr_load(s_home_screen);
}