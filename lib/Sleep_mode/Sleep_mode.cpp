#include "Sleep_mode.hpp"

MPU6050 mpu_data;
Sleep_mode::Sleep_mode() 
{

}

bool Sleep_mode::action_checker(int16_t axis_X, int16_t temporary_axis_X, int16_t axis_Y, int16_t temporary_axis_Y) {
 int16_t avarage_X = abs(temporary_axis_X) - abs(axis_X);
 int16_t avarage_Y = abs(temporary_axis_Y) - abs(axis_Y);
  if((avarage_X <= 500 && avarage_X >= -500) && (avarage_Y <= 500 && avarage_Y >= -500))
  {
    return false;
  }
  //Serial.print("Action deteced");
  return true;
}

void Sleep_mode::sleep_mode_start() {
    btStop();
    setCpuFrequencyMhz(160);
}

void Sleep_mode::wake_up_device() {
  Serial.print("\nWake up function started");
  ESP.restart();
}
