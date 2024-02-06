#include "MPU6050_controller.hpp"
#include "BLE_logic.hpp"
#include "Data_transfer.hpp"
#include "Sleep_mode.hpp"
#include "Button.hpp"
#include "driver/rtc_io.h"
#include <Preferences.h>
#include "Bluetooth_onWrite.hpp"
#include "Bluetooth_iclickWrite.hpp"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define WATCHDOG_TIMEOUT_S 300
#define WATCHDOG_DEEP_SLEEP 600
volatile bool is_sleep = false;
volatile bool deep_sleep = false;
volatile bool l_click = false;

bool deviceConnected = false;

bool reset_values = false;

bool enable_click = true;

int left_click_counter = 0;

std::vector<int16_t> gyroscope_data;
int16_t axis_X, axis_Y;
int16_t temporary_axis_X, temporary_axis_Y;

Preferences pref;
MPU6050 mpu;
BLE_logic ble_logic;
Data_transfer data_transfer;
Sleep_mode sleep_mode;
Button button;
Bluetooth_onWrite onWrite;
Bluetooth_iclickWrite iclick;

TaskHandle_t Task1;
TaskHandle_t Task2;

hw_timer_t *watchDogTimer = NULL;
hw_timer_t *watchDogTimerDeepSleep = NULL;
hw_timer_t *watchDogTimerClick = NULL;


void IRAM_ATTR watchDogInterrupt()
{
  is_sleep = true;
}

void IRAM_ATTR watchDogDeepSleepInterrupt()
{
  deep_sleep = true;
}

void IRAM_ATTR watchDogClickInterrupt()
{
  l_click = true;
}

void watchDogRefresh()
{
  timerWrite(watchDogTimer, 0);
  timerWrite(watchDogTimerDeepSleep, 0);
}

void watchDogClickRefresh()
{
  timerWrite(watchDogTimerClick, 0);
}

void mouse_controller(void *pvParameters)
{
  for (;;)
  { 
      bool status;
      bool click_status;
      button.press_button();
      onWrite.set_settings();
      //iclick.set_iclick_settings();
      ble_logic.setCurrentvalues();
      gyroscope_data = mpu.gyroscope_data();
      temporary_axis_X = gyroscope_data[0];
      temporary_axis_Y = gyroscope_data[1];
      click_status = ble_logic.mouse_action(gyroscope_data[0], gyroscope_data[1], gyroscope_data[2], gyroscope_data[3], gyroscope_data[4], gyroscope_data[5]);

      if(left_click_counter == 1)
      {
        l_click = false;
      }

      if (click_status && enable_click)
      {
        watchDogClickRefresh();
        left_click_counter = 0;
        // Serial.print("time refreshed");
      }

      if (l_click && enable_click && left_click_counter == 0 )
      {
        ble_logic.l_click_action();
        l_click = false;
        left_click_counter++;
      }

      gyroscope_data.clear();
      gyroscope_data = mpu.gyroscope_data();
      axis_X = gyroscope_data[0];
      axis_Y = gyroscope_data[1];
      gyroscope_data.clear();
      status = sleep_mode.action_checker(axis_X, temporary_axis_X, axis_Y, temporary_axis_Y);
      if (status)
      {
        watchDogRefresh();
      }
      if (is_sleep)
      {
        Serial.print("Sleep mode started");
        sleep_mode.sleep_mode_start();
        for (;;)
        {
          gyroscope_data = mpu.gyroscope_data();
          temporary_axis_X = gyroscope_data[0];
          temporary_axis_Y = gyroscope_data[1];
          gyroscope_data.clear();
          gyroscope_data = mpu.gyroscope_data();
          axis_X = gyroscope_data[0];
          axis_Y = gyroscope_data[1];
          status = sleep_mode.action_checker(axis_X, temporary_axis_X, axis_Y, temporary_axis_Y);
          if (status)
          {
            Serial.print("wake_up_device");
            sleep_mode.wake_up_device();
          }
          if (deep_sleep)
          {
            Serial.print("deep sleep started");
            esp_deep_sleep_start();
          }
        }
      }
  }
}

void Data_send_receive(void *pvParameters)
{ 
  for (;;)
  {
    auto connected = ble_logic.deviceConnected();
    if(connected == true) 
    {
      Serial.print("Data transfer allowed");
      data_transfer.send_receive_data_2();
    }
  }
}

void setup()
{
    watchDogTimer = timerBegin(0, 80, true);
    timerAttachInterrupt(watchDogTimer, &watchDogInterrupt, true);
    timerAlarmWrite(watchDogTimer, WATCHDOG_TIMEOUT_S * 1000000, false);
    timerAlarmEnable(watchDogTimer);

    watchDogTimerDeepSleep = timerBegin(1, 80, true);
    timerAttachInterrupt(watchDogTimerDeepSleep, &watchDogDeepSleepInterrupt, true);
    timerAlarmWrite(watchDogTimerDeepSleep, WATCHDOG_DEEP_SLEEP * 1000000, false);
    timerAlarmEnable(watchDogTimerDeepSleep);

    watchDogTimerClick = timerBegin(2, 80, true);
    timerAttachInterrupt(watchDogTimerClick, &watchDogClickInterrupt, true);
    timerAlarmWrite(watchDogTimerClick, left_click_time * 1000000, true);
    timerAlarmEnable(watchDogTimerClick);

    mpu.init_mpu6050();
    ble_logic.ble_mouse_init();
    button.init_button();
    onWrite.set_auto_click_timer();

    rtc_gpio_pullup_en(GPIO_NUM_33);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0);
  
  
  xTaskCreatePinnedToCore(
      mouse_controller,
      "mouse_controller",
      4096,
      NULL,
      1,
      &Task1,
      0);

  xTaskCreatePinnedToCore(
      Data_send_receive,
      "Data_send_receive",
      4096,
      NULL,
      1,
      &Task2,
      1);
}

void loop()
{
  //Serial.println("Perform some job");
  //delay(2000);
}
