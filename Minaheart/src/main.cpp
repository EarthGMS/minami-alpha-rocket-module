//THE MINAHEART MODULE PROGRAM

#include <Arduino.h>

//GPS MODULE
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//ACCELEROMETER
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

TinyGPSPlus GPS_MODULE; //GPS MODULE VARIABLE
Adafruit_MPU6050 ACCELEROMETER; //ACCELEROMETER

//TO DO NEXT
void setup(){
    Serial.begin(115200);
    Wire.begin();
}

void loop(){
    //Receive data from GPS tracker

    //Receive data from the accelerometer

    //Send data to the website

    //Delay for 5 seconds
}