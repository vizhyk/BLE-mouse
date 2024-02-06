#pragma once

#include <Bluetooth_mouse.hpp>
#include "Arduino.h"
#include "MPU6050_controller.hpp"
#include "Battery_checker.hpp"

class BLE_logic {

public:
void l_click_action();
void check_connection();
void ble_mouse_init(void);
bool mouse_action(int16_t aX, int16_t aY, int16_t aZ, int16_t GyX, int16_t GyY, int16_t GyZ);
bool mouse_up(int16_t aX, int16_t aZ, int sensibility, bool inverted, bool scrolling_enabled, int redefined_side);
bool mouse_down(int16_t aX, int16_t aZ, int sensibility, bool inverted, bool scrolling_enabled, int redefined_side);
bool mouse_left(int16_t aX, int16_t aZ, int sensibility, bool inverted, bool scrolling_enabled, int redefined_side);
bool mouse_right(int16_t aX, int16_t aZ, int sensibility, bool inverted, bool scrolling_enabled, int redefined_side);
void mouse_left_click(int16_t GyY,int16_t GyZ, Redefined_action value);
void sensetive_left_click_action(int16_t aZ, int16_t GyZ, Redefined_action value);
void sensetive_right_click_action(int16_t aZ, int16_t GyZ, Redefined_action value);
void mouse_right_click(int16_t GyY,int16_t GyZ,Redefined_action value);
bool alternative_move(int16_t GyX, int16_t GyZ, int16_t aZ, bool is_inverted);
void alternative_scrolling(int16_t GyX, int16_t GyZ);
void Notify();
void setCurrentvalues();
bool change_control_mode(int16_t GyZ);
bool enable_scrolling_mode(int16_t GyY, int16_t GyZ, bool alternative_mode, Redefined_action value);
bool sensetive_scrolling_mode(int16_t aZ, int16_t GyY, int16_t GyZ, bool alternative_mode, Redefined_action value);
bool disable_scrolling_mode( bool alternative_mode);
bool getStatus();
bool deviceConnected();
int  change_sensibility(int16_t GyY,int16_t GyZ, Redefined_action value);
int  alternative_mode_sensibility_converter(int alternative_sensibility);
};

