#pragma once

#include "MPU6050_controller.hpp"

class Sleep_mode {
public:
Sleep_mode();
bool action_checker(int16_t axis_X, int16_t temporary_axis_X, int16_t axis_Y, int16_t temporary_axis_Y);
void sleep_mode_start();
void wake_up_device();
};

