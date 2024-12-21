#include "components/brain.h"

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