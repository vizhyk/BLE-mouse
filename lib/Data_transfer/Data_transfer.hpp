#pragma once

#include "BluetoothSerial.h"
#include "Battery_checker.hpp"
#include <Bluetooth_mouse.hpp>
#include <BLE_logic.hpp>
#include <Preferences.h>
#include "json.hpp"
#include "Bluetooth_connection.hpp"
#include "Battery_checker.hpp"


class Data_transfer {
public:
Data_transfer();
bool send_receive_data(bool reset_values);
void setup_ble();
void send_receive_data_2();
};