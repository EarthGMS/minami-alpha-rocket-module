//THE MINAHEART MODULE PROGRAM

#include <Arduino.h>

//GPS MODULE
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//ACCELEROMETER
#include <MPU6050.h>
#include <Wire.h>

//Altitude measure
#include <BMP280_DEV.h>

//Variables
#define ALTITUDE_PIN 10
float temperature, pressure, altitude;
bool parachuteActivate, fuel_igniter;

//TinyGPSPlus GPS_MODULE; //GPS MODULE VARIABLE
MPU6050 ACCELEROMETER; //ACCELEROMETER

SoftwareSerial GPS_MODULE_SERIAL(4,3);

//BMP280 - Altitude measure
BMP280_DEV ALTITUDE_MEASURE(ALTITUDE_PIN);


//TO DO NEXT
void setup(){
    Serial.begin(115200);
    Wire.begin();
    //GPS_MODULE_SERIAL.begin(115200);
    ACCELEROMETER.initialize();
    ALTITUDE_MEASURE.begin();
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
    Serial.print("Accel X: "); Serial.print(ax / 16384.0);
    Serial.print(" Y: ");       Serial.print(ay / 16384.0);
    Serial.print(" Z: ");       Serial.println(az / 16384.0);

    // Gyroscope (raw → °/s): divide by 131 (±250°/s default)
    Serial.print("Gyro X: ");  Serial.print(gx / 131.0);
    Serial.print(" Y: ");       Serial.print(gy / 131.0);
    Serial.print(" Z: ");       Serial.println(gz / 131.0);

    //--------------------------------ALTITUDE MEASREMENT---------------------------------//
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

    //-----------------------------WEBSITE OUTPUT (TBD)------------------------------//


    //Delay for 5 seconds
    delay(5000);
}