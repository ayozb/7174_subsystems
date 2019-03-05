#include <Wire.h>

#define I2C_SLAVE_ADDR1 0x03

typedef struct {
  uint8_t distanceLow;
  uint8_t distanceHigh;
  int distance;
  uint8_t strengthLow;
  uint8_t strengthHigh;
  int strength;
}Lidar;

Lidar lidarOne = {0, 0, 0, 0, 0, 0};

void readData(Lidar* lidar);

void setup() {
  Wire.begin();   // join i2c bus (address optional for master)
  Serial.begin(9600);
}

void loop() {

  if(Wire.requestFrom(I2C_SLAVE_ADDR1, 1)){// request 1 byte from slave device 
    readData(&lidarOne);  

    Serial.print("distance: ");
    Serial.println(lidarOne.distance);
    delay(20);
  }
}

void readData(Lidar* lidar){
  while(Wire.available()) {
    lidar->distance = Wire.read();
  }
}
