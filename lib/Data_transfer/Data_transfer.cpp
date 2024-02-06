#include "Data_transfer.hpp"

BluetoothSerial SerialBT;
Battery_checker battery;
BLE_logic ble;

using json = nlohmann::json;
Data_transfer::Data_transfer(){}


void Data_transfer::send_receive_data_2() {
     bool status;
     status = ble.getStatus();
     //float bat = battery.battery_check();
     //float charg = battery.charging_value();
     //bool charging_status = battery.charging_status(charg);
     //Serial.println("Voltage on 13th pin:");
     //Serial.println(charging_status);

     /*if(bat == 0.0)
     {
       Serial.print("LOW ENERGY, deep sleep started");
       esp_deep_sleep_start();
     }*/
     
     if(status) {

      ble.Notify();
      delay(5000);
     }
}