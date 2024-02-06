#pragma once

#include <BLEDevice.h>
#include "Bluetooth_connection.hpp"
#include "Bluetooth_onWrite.hpp"
#include "Bluetooth_iclickWrite.hpp"
#include "Battery_checker.hpp"
#include "BLEHIDDevice.h"
#include <BLEUtils.h>
#include <BLEServer.h>
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"
#include <driver/adc.h>
#include "esp32-hal-log.h"
#include "esp_log.h"
#include "Set_values.hpp"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_BACK 8
#define MOUSE_FORWARD 16
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)



class Bluetooth_mouse  {
private:
  uint8_t mouse_buttons;
  uint8_t battery_level;
  std::string device_name;
  Bluetooth_connection* connection_status;
  Bluetooth_onWrite* onWrite;
  Bluetooth_iclickWrite* iclickWrite;
  BLEHIDDevice* hid;
  BLECharacteristic* mouse;
  void buttons(uint8_t button);
  void rawAction(uint8_t message[], char message_size);
  static void taskServer(void* pvParameter);

public:
  Bluetooth_mouse(std::string deviceName = "mouse ble", std::string deviceManufacturer  = "me", uint8_t batteryLevel = 100);
  void begin();
  void click(uint8_t button = MOUSE_LEFT);
  void move(signed char coordinate_X, signed char coordinate_Y, signed char mouse_wheel = 0, signed char hWheel = 0);
  void press(uint8_t button = MOUSE_LEFT);   
  void release(uint8_t button = MOUSE_LEFT); 
  bool isPressed(uint8_t button = MOUSE_LEFT); 
  bool isConnected();
  void setBatteryLevel(uint8_t level);
  void setNotifications();
  void setCurrentvalues();
  BLECharacteristic* pChar;
  int8_t batteryLevel;
  std::string deviceManufacturer;
  std::string deviceName;
  
protected:
  virtual void onStarted(BLEServer *pServer) { };
};

extern Bluetooth_mouse bluetooth_mouse;