#include "Bluetooth_iclickWrite.hpp"

Bluetooth_iclickWrite::Bluetooth_iclickWrite() {};

using json = nlohmann::json;

Preferences prefer;

int function_iclick_call_counter = 0;

void Bluetooth_iclickWrite::onWrite(BLECharacteristic *pCharacteristic)
{

    std::string payload = pCharacteristic->getValue();
      std::string str_for_dump;

      if (payload.length() > 0) {
        Serial.println(payload.c_str());

        json example = json::parse(payload);
        str_for_dump =  example.dump(1);
        Serial.println(str_for_dump.c_str());

        auto iclick_l_eye = example["left_button"].get<bool>();
        auto iclick_r_eye = example["right_button"].get<bool>();
        Serial.println("[INFO]: left click value: ");
        Serial.println(iclick_l_eye);
        Serial.println("[INFO]: right click value: ");
        Serial.println(iclick_r_eye);
      }
    
}

void Bluetooth_iclickWrite::set_iclick_settings()
{
  prefer.begin("iclick_sett", false); 

  auto iclick_settings = prefer.getBool("iclick_config", 0);
  if(function_iclick_call_counter < 1)
  {
    if(iclick_settings)
    { 

     i_click_mode = prefer.getBool("iclick_mode",0);
     Serial.println("i_click_mode");
     Serial.println(i_click_mode);
     i_click_left = prefer.getInt("iclick_l_eye", 0);
     Serial.println("iclick_l_eye");
     Serial.println(i_click_left);
     i_click_right = prefer.getInt("iclick_r_eye", 0);
     Serial.println("iclick_r_eye");
     Serial.println(i_click_right);

     function_iclick_call_counter++;
    }
    Serial.print("[INFO]: set_iclick_settings started ");
  }
  prefer.end();
}