#include "components/brain.h"

/**
 * @brief Logo screen
 * 
 */
static void logo_screen(void) {
    s_logo_screen = lv_obj_create(NULL);

    image(s_logo_screen, &logo, LV_ALIGN_CENTER, {0, 0});

    back_btn(s_logo_screen, LV_ALIGN_TOP_LEFT, {0, 0}, lv_color_hex(0));
}