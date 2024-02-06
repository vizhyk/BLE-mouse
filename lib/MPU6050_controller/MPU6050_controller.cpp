#include "MPU6050_controller.hpp"


MPU6050::MPU6050() :
    MPU_addr{0x68}, 
    minVal{265}, 
    maxVal{402}
{

}

void MPU6050::init_mpu6050(void)
{
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true); 
  Serial.println("[INFO]: MPU6050 initialized");
}

std::vector<int16_t> MPU6050::gyroscope_data()
{
  std::vector<int16_t> Axis;
  Wire.beginTransmission(MPU_addr);    
  Wire.write(0x3B);                
  Wire.endTransmission(false);     
  Wire.requestFrom(MPU_addr,(uint8_t) 14,true);

  axis_X=Wire.read()<<8|Wire.read();                
  axis_Y=Wire.read()<<8|Wire.read();
  axis_Z=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read(); 
  
  Axis.insert(Axis.end(), {axis_X, axis_Y, axis_Z, GyX, GyY, GyZ});
  /*Serial.print("\nGyX: "); Serial.print(GyX); 
  Serial.print("\nGyY: "); Serial.print(GyY); 
  Serial.print("\nGyZ: "); Serial.print(GyZ);  
  Serial.print("\naxis_X: "); Serial.print(axis_X);
  Serial.print("\naxis_Y: "); Serial.print(axis_Y);  
  Serial.print("\naxis_Z: "); Serial.print(axis_Z);*/
  return Axis;
}

