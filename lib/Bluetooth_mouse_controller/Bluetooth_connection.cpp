#include "Bluetooth_connection.hpp"

Bluetooth_connection::Bluetooth_connection() : 
    is_connected{false}

{

}

void Bluetooth_connection::onConnect(BLEServer* pServer)
{
  is_connected = true;
  BLE2902* descriptor = (BLE2902*)this->mouse->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  descriptor->setNotifications(is_connected);
  pServer->startAdvertising();

}

void Bluetooth_connection::onDisconnect(BLEServer* pServer)
{
  is_connected = false;
  BLE2902* descriptor = (BLE2902*)this->mouse->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  descriptor->setNotifications(is_connected);
  pServer->startAdvertising();
}



