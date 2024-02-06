#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <vector>


class MPU6050 {
private:
    const uint16_t MPU_addr;
    int16_t axis_X;
    int16_t axis_Y;
    int16_t axis_Z;
    int16_t Tmp;
    int16_t GyX;
    int16_t GyY;
    int16_t GyZ;
    int minVal;
    int maxVal;

public:
    MPU6050();
    void init_mpu6050(void);
    std::vector<int16_t> gyroscope_data();
};


