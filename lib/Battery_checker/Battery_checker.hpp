#pragma once

#include "Arduino.h"
#include "esp_adc_cal.h"

class Battery_checker {
private:
adc_channel_t channel ;
int used_pin;
long sum;
float ADC_data;
float output;
const float battery_max;
const float battery_min;
const float R1;
const float R2;
bool attached;

public:
Battery_checker();
float battery_check();
float charging_value();
bool charging_status(float charge);
void attach(int pin);
void attach_to_pin(void);
};


