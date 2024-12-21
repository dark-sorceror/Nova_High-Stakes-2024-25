#include "components/brain.h"

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