#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial Serial1(2, 3); //define software serial port name as 
                               //Serial1 and define pin2 as RX and pin3 as TX

//pin D2 = rx
//pin D3 = tx
//pin A4 = SDA
//pin A5 = SCL
#define I2C_SLAVE_ADDR 0x03

typedef struct { //structure to hold incoming data
  uint8_t distanceLow;
  uint8_t distanceHigh;
  int distance;
  uint8_t strengthLow;
  uint8_t strengthHigh;
  int strength;
}Lidar;

Lidar lidarOne = {0, 0, 0, 0, 0, 0};
boolean printing = false;

boolean getLidarData(Lidar* lidar);

void setup() {
  Serial.begin(9600); //PC baudrate
  Serial1.begin(115200);  //LiDar baudrate
  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onRequest(requestEvent);  
}

void loop() {  
  if(getLidarData(&lidarOne)){  
    if(printing){
      Serial.print(lidarOne.distance);
      Serial.print("cm\t");
      Serial.print("strength: ");
      Serial.println(lidarOne.strength);
      }    
  }
}
boolean getLidarData(Lidar* lidar) {
  static char i = 0;
  char j = 0;
  int checksum = 0; 
  static int rx[9];
  if(Serial1.available()) {  
    rx[i] = Serial1.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        lidar->distanceLow = rx[2];
        lidar->distanceHigh = rx[3];
        lidar->strengthLow = rx[4];
        lidar->strengthHigh = rx[5];
        lidar->distance = rx[2] + rx[3] * 256;
        lidar->strength = rx[4] + rx[5] * 256;
        return true;
      }
      i = 0;
    } else {
      i++;
    } 
  }
  return false; 
}

void requestEvent() {
  Wire.write((uint8_t)lidarOne.distance); //wraps to 0 if greater than 255cm
}
