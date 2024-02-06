#pragma once

#include "Arduino.h"
#include "BLECharacteristic.h"
#include "BLE2902.h"
#include <BLEHIDDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Preferences.h>
#include "json.hpp"
#include "sdkconfig.h"

class Bluetooth_iclickWrite :  public BLECharacteristicCallbacks
{
public:
  Bluetooth_iclickWrite();
  void onWrite(BLECharacteristic *pCharacteristic);
  void set_iclick_settings();
};