#include "Battery_checker.hpp"

float average_output = 0;


Battery_checker::Battery_checker() :
    sum{0},
    ADC_data{0.0},
    output{0.0},
    battery_max{4.2},
    battery_min{2.8},
    R1{29600.0},
    R2{9940.0},
    used_pin{1},
    attached{false}
{

}

float Battery_checker::battery_check() {
   adc1_config_width(ADC_WIDTH_12Bit);
   adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_0db);

    attach(5);
    delay(1);

    for(int cycle = 0; cycle < 10; cycle++)
    {

        for (int i = 0; i < 10; i++) {
            sum += adc1_get_raw(ADC1_CHANNEL_0);
            delay(10);
            //Serial.println("\nSUM:"); Serial.print(sum);
        }

        ADC_data = sum / (float)10;
        sum = 0;
        //Serial.println("\nADC_DATA1:"); Serial.print(ADC_data);
        ADC_data = (ADC_data * 1.1) / 4095.0;
        //Serial.println("\nADC_DATA2:"); Serial.print(ADC_data);
        ADC_data = ADC_data / (R2/(R1+R2));
        //Serial.println("\nADC_DATA3:"); Serial.print(ADC_data);
        ADC_data = roundf(ADC_data * 100) / 100;
        //Serial.println("\nADC_DATA:"); Serial.print(ADC_data);
        output = ((ADC_data - battery_min) / (battery_max - battery_min)) * 100;
        //Serial.println("\noutput:"); Serial.print(output);
        average_output += output;
    }
    //int val = digitalRead(8);
    //delay(2000);
    //Serial.println("\nVAL:"); Serial.print(val);

    /*if(BL.getBatteryVolts() >= Usb_voltage){
        Serial.println("\nCharging:"); Serial.print(output);
    }*/
    average_output = average_output / 11;
    average_output = round(average_output);
    //Serial.println("\nAverage_output:"); Serial.printf(" round %f\n" ,average_output);

    sum = 0;
    if(average_output > 100)
    Serial.println("[INFO]: Battery overcharged ");
        return 100.0f;
    if (average_output < 100 && average_output > 0)
    Serial.println("[INFO]: Battery level is between 0 and 99");
        return average_output;
    if (average_output <= 0)
    {
        Serial.println("[ERROR]: Battery level is lower then 0!");
        return 0.0f;
    }
    /// sometimes happens
    else 
    Serial.println("[WARNING]: Something has happened. Wrong battery charge ");
        return average_output;    
}

float Battery_checker::charging_value() {
    int usb_voltage = 0;
    usb_voltage = analogRead(33);
    //Serial.println("usb_voltage");
    //Serial.println(usb_voltage); 
    /*adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_0db);
    attach(13);
    delay(1);
    float usb_voltage = adc1_get_raw(ADC1_CHANNEL_3);
    usb_voltage = (usb_voltage * 1.1) / 4095.0;*/
    //Serial.println("\nusb_voltage:"); Serial.print(usb_voltage);
    return usb_voltage;
}

bool Battery_checker::charging_status(float charge)
{
    
    if(charge >= 2000)
    return true;
    return false;
}

void Battery_checker::attach(int pin)
{
	used_pin = pin;
	channel = (adc_channel_t)digitalPinToAnalogChannel(used_pin);
	attached = true;
}
