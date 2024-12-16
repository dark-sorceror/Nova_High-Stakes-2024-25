/**
 * \file brain.cpp
 *
 * \brief Contains lvgl implementation for auton planner logic on brain
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include "lvgl.h"

#include "globals.h"

#include "components/brain.h"

#include "../renders/logo.c"
#include "../renders/logo_2.c"
#include "../renders/field.c"

LV_IMG_DECLARE(logo);
LV_IMG_DECLARE(logo_2);
LV_IMG_DECLARE(field);

static void btn_event_handler(lv_event_t * e);

static void home_screen(void);
static void match_screen(void);
static void logo_screen(void);
static void testing_screen(void);
static void robot_screen(void);

lv_obj_t * s_logo_screen;
lv_obj_t * s_home_screen;
lv_obj_t * s_match_screen;
lv_obj_t * s_testing_screen;
lv_obj_t * s_robot_screen;

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

int autonSelected;

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

/**
 * @brief Logo screen
 * 
 */
static void logo_screen(void) {
    s_logo_screen = lv_obj_create(NULL);

    image(s_logo_screen, &logo, LV_ALIGN_CENTER, {0, 0});

    back_btn(s_logo_screen, LV_ALIGN_TOP_LEFT, {0, 0}, lv_color_hex(0));
}

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

/**
 * @brief Robot screen
 * 
 */
static void robot_screen(void) {
    s_robot_screen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(s_robot_screen, lv_color_hex(0), LV_PART_MAIN);

    static lv_point_t line_points_1[] = {
        {187, 60},
        {287, 60},
        {287, 200}
    };

    static lv_point_t line_points_2[] = {
        {287, 200},
        {187, 200},
        {187, 60}
    };

    lv_obj_t * line = lv_line_create(s_robot_screen);

    lv_line_set_points(line, line_points_1, 3);
    lv_obj_set_style_line_width(line, 2, LV_PART_MAIN);

    lv_obj_t * line2 = lv_line_create(s_robot_screen);

    lv_line_set_points(line2, line_points_2, 3);
    lv_obj_set_style_line_width(line2, 2, LV_PART_MAIN);

    back_btn_2(s_robot_screen, LV_ALIGN_TOP_MID, {0, 20}, lv_color_hex(0xFFFFFF));

    const std::vector<double> driveMotorEfficiencies = Nova::drive.get_efficiency_all();
    const std::vector<double> driveMotorTemperatures = Nova::drive.get_temperature_all();
    const std::vector<std::int8_t> driveMotorPorts = Nova::drive.get_port_all();
    
    /*
    const std::vector<double> driveMotorEfficiencies = Nova::drive.get_efficiency_all();
    const std::vector<double> driveMotorTemperatures = Nova::drive.get_temperature_all();
    const std::vector<std::int8_t> driveMotorPorts = Nova::drive.get_port_all();

    const bool isIntakeMotorInstalled = Nova::intake.is_installed();
    const double intakeMotorEfficiency = Nova::intake.get_efficiency();
    const double intakeMotorTemperature = Nova::intake.get_temperature();
    const int8_t intakeMotorPort = Nova::intake.get_port();

    const double conveyorMotorEfficiency = Nova::conveyor.get_efficiency();
    const double conveyorMotorTemperature = Nova::conveyor.get_temperature();
    const int8_t conveyorMotorPort = Nova::conveyor.get_port();

    */

    for (std::size_t i = 0; i < driveMotorEfficiencies.size(); ++i) {
        std::int8_t port = driveMotorPorts[i];
        //pros::Device device(port, pros::DeviceType(2));
        bool isInstalled = true;
        double efficiency = driveMotorEfficiencies[i];
        double temperature = driveMotorTemperatures[i];

        text(
            s_robot_screen, 
            ("(" + std::to_string(port) + "): ").c_str(), 
            determine_text_color(isInstalled ? port : -1, 0, 0, 0), 
            i < 3 ? LV_ALIGN_TOP_LEFT : LV_ALIGN_TOP_RIGHT, 
            {
                i < 3 ? 0 : -20, 
                80 * int(i % 3)
            }
        );
        text(
            s_robot_screen, 
            ("Eff: " + std::string(isInstalled ? std::to_string(efficiency) : "")).c_str(), 
            determine_text_color(isInstalled ? efficiency : -1, 1, 70, 50), 
            i < 3 ? LV_ALIGN_TOP_LEFT : LV_ALIGN_TOP_RIGHT, 
            {
                i < 3 ? 0 : -20, 
                80 * int(i % 3) + 15
            }
        );
        text(
            s_robot_screen, 
            ("Temp: " + std::string(isInstalled ? std::to_string(temperature) : "")).c_str(), 
            determine_text_color(isInstalled ? temperature : -1, -1, 30, 35), 
            i < 3 ? LV_ALIGN_TOP_LEFT : LV_ALIGN_TOP_RIGHT, 
            {
                i < 3 ? 0 : -20, 
                80 * int(i % 3) + 30
            }
        );

    }
}

/**
 * @brief Testing screen
 * 
 */
static void testing_screen(void) {
    s_testing_screen = lv_obj_create(NULL);

    lv_obj_set_style_bg_color(s_testing_screen, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t * data = lv_obj_create(s_testing_screen);
    
    lv_obj_set_size(data, 240, 150);

    lv_obj_align(data, LV_ALIGN_LEFT_MID, 20, -30);

    lv_obj_set_style_bg_color(data, lv_color_hex(0), LV_PART_MAIN);

    static pros::Link link(1, "3388N_Nova", pros::E_LINK_TX);

    const int batteryPercent = pros::battery::get_capacity();
    const int batteryTemperature = pros::battery::get_temperature();

    const bool isBrainConnected = pros::competition::is_connected();

    const std::int32_t isControllerConnected = Nova::ctr.is_connected();
    const std::int32_t getControllerBatteryLevel = Nova::ctr.get_battery_level();
    const std::int32_t getControllerBatteryCapacity = Nova::ctr.get_battery_capacity();

    const bool isRadioConnected = link.connected();

    std::vector<std::string> autons = {"BLUE 1", "BLUE 2", "RED 1", "RED 2"};

    text(
        s_testing_screen, 
        ("Auton Running: " + autons[autonSelected]).c_str(), 
        lv_color_hex(0xFFFFFF), 
        LV_ALIGN_BOTTOM_RIGHT, 
        {-10, -10}
    );

    text(
        data, 
        ("Battery Percent: " + std::to_string(batteryPercent) + "%").c_str(), 
        determine_text_color(batteryPercent, 1, 70, 50), 
        LV_ALIGN_TOP_MID, 
        {0, 0}
    );
    text(
        data, 
        ("Battery Temperature: " + std::to_string(batteryTemperature) + "oC").c_str(), 
        determine_text_color(batteryTemperature, -1, 30, 35), 
        LV_ALIGN_TOP_MID, 
        {0, 15}
    );
    text(
        data, 
        ("Brain Connected: " + std::string(isBrainConnected == 0 ? "NO" : "YES")).c_str(), 
        determine_text_color(isBrainConnected, 0, 0, 0), 
        LV_ALIGN_TOP_MID, 
        {0, 30}
    );
    text(
        data, 
        ("Controller Connected: " + std::string(isControllerConnected == 0 ? "NO" : "YES")).c_str(), 
        determine_text_color(isControllerConnected, 0, 0, 0), 
        LV_ALIGN_TOP_MID, 
        {0, 45}
    );
    text(
        data, 
        ("Controller Battery Level: " + std::string(isControllerConnected ? std::to_string(getControllerBatteryLevel) : "")).c_str(), 
        determine_text_color(isControllerConnected ? getControllerBatteryLevel : -1, 1, 70, 50), 
        LV_ALIGN_TOP_MID, 
        {0, 60}
    );
    text(
        data, 
        ("Controller Battery Capacity: " + std::string(isControllerConnected ? std::to_string(getControllerBatteryCapacity) : "")).c_str(), 
        determine_text_color(isControllerConnected ? getControllerBatteryCapacity : -1, 1, 30, 35), 
        LV_ALIGN_TOP_MID, 
        {0, 75}
    );
    text(
        data, 
        ("Radio Connected: " + std::string(isRadioConnected == 0 ? "NO" : "YES")).c_str(), 
        determine_text_color(isRadioConnected, 0, 0, 0), 
        LV_ALIGN_TOP_MID, 
        {0, 90}
    );

    back_btn(s_testing_screen, LV_ALIGN_RIGHT_MID, {-77, 20}, lv_color_hex(0xFFFFFF));
    button(s_testing_screen, 170, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_BOTTOM_LEFT, {55, -20}, "Robot", lv_color_hex(0xFFFFFFF), BTN_ROBOT);
    button(s_testing_screen, 170, 40, 2, lv_color_hex(0xFFFFFF), lv_color_hex(0), LV_ALIGN_RIGHT_MID, {-27, -20}, "Confirm", lv_color_hex(0xFFFFFFF), BTN_CONFIRM);
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