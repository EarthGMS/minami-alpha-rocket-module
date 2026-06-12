//THE MINAHEART MODULE PROGRAM

#include <Arduino.h>

//GPS MODULE
#include <TinyGPS++.h>
//#include <SoftwareSerial.h>

//ACCELEROMETER
#include <MPU6050.h>
#include <Wire.h>

//Altitude measure

//LoRa
#include <SPI.h>
#include <LoRa.h>

//Variables
#define ALTITUDE_PIN 10
#define NSS   PA0
#define RST   PB0
#define DIO0  PB1
float temperature, pressure, altitude;
bool parachuteActivate, fuel_igniter;

//TinyGPSPlus GPS_MODULE; //GPS MODULE VARIABLE
MPU6050 ACCELEROMETER; //ACCELEROMETER

//BMP280 - Altitude measure
//BMP280_DEV ALTITUDE_MEASURE(ALTITUDE_PIN);


//TO DO NEXT
void setup(){
    SerialUSB.begin(115200);
    Wire.begin();
    //GPS_MODULE_SERIAL.begin(115200);
    ACCELEROMETER.initialize();
    //ALTITUDE_MEASURE.begin();

    //LoRa

    Serial.begin(115200);

    LoRa.setPins(NSS, RST, DIO0);

    if (!LoRa.begin(433E6)) {  // match your module's frequency
        Serial.println("LoRa init failed!");
        while (true);
    }

    LoRa.setSpreadingFactor(9);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(7);
    LoRa.setTxPower(17);

    Serial.println("LoRa init OK");
}

void loop(){
    /*
    //Receive data from GPS tracker (Integrate later)
    while (GPS_MODULE_SERIAL.available() > 0) {
        char c = GPS_MODULE_SERIAL.read();
        GPS_MODULE.encode(c);
    }

    if (GPS_MODULE.location.isUpdated()) {
        Serial.print("Lat: "); Serial.println(GPS_MODULE.location.lat(), 6);
        Serial.print("Lng: "); Serial.println(GPS_MODULE.location.lng(), 6);
        Serial.print("Alt: "); Serial.println(GPS_MODULE.altitude.meters());
        Serial.print("Speed: "); Serial.println(GPS_MODULE.speed.kmph());
        Serial.print("Satellites: "); Serial.println(GPS_MODULE.satellites.value());
    }
        */

    //-----------------------------WEBSITE INPUT (TBD)------------------------------//

    //--------------------------------MPU6050---------------------------------//
    //Receive data from the accelerometer
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    ACCELEROMETER.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Accelerometer (raw → g): divide by 16384 (±2g default)
    SerialUSB.print("Accel X: "); SerialUSB.print(ax / 16384.0);
    SerialUSB.print(" Y: ");       SerialUSB.print(ay / 16384.0);
    SerialUSB.print(" Z: ");       SerialUSB.println(az / 16384.0);

    // Gyroscope (raw → °/s): divide by 131 (±250°/s default)
    SerialUSB.print("Gyro X: ");  SerialUSB.print(gx / 131.0);
    SerialUSB.print(" Y: ");       SerialUSB.print(gy / 131.0);
    SerialUSB.print(" Z: ");       SerialUSB.println(gz / 131.0);

    //--------------------------------ALTITUDE MEASREMENT---------------------------------//
    /*
    ALTITUDE_MEASURE.startForcedConversion();
    if (ALTITUDE_MEASURE.getMeasurements(temperature, pressure, altitude))
    {
        Serial.print(temperature);                 
        Serial.print(F("*C   "));
        Serial.print(pressure);    
        Serial.print(F("hPa   "));
        Serial.print(altitude);
        Serial.println(F("m"));  
    }
    */
    //-----------------------------LoRa communication------------------------------//
    LoRa.beginPacket();
    LoRa.print("ALT:1234,VEL:56.7");
    LoRa.endPacket();

    Serial.println("Sent packet");

    //Delay for 5 seconds

    SerialUSB.println("****************************");
    delay(1000);
}