#pragma once

#include "Arduino.h"
#include "BLECharacteristic.h"
#include "BLE2902.h"
#include <BLEHIDDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "json.hpp"
#include "sdkconfig.h"
#include <Preferences.h>

class Bluetooth_onWrite :  public BLECharacteristicCallbacks
{
public:
  Bluetooth_onWrite();
  void onWrite(BLECharacteristic *pCharacteristic);
  void set_settings();
  void set_auto_click_timer();
};