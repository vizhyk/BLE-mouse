#pragma once

#include "Arduino.h"
#include "BLECharacteristic.h"
#include "BLE2902.h"
#include <BLEHIDDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "sdkconfig.h"

class Bluetooth_connection : public BLEServerCallbacks
{
public:
  Bluetooth_connection();
  BLECharacteristic* mouse;
  bool is_connected;
  void onConnect(BLEServer* pServer);
  void onDisconnect(BLEServer* pServer);
  bool getStatus();
};
