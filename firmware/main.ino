#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h> // Pressure sensor
#include <Adafruit_MAX30102.h> // PPG sensor for blood flow

Adafruit_BMP280 bmp;
Adafruit_MAX30102 max30102;

void setup() {
    Serial.begin(115200);
    if (!bmp.begin()) {
        Serial.println("Could not find BMP280 sensor!");
        while (1);
    }
    if (!max30102.begin()) {
        Serial.println("Could not find MAX30102 sensor!");
        while (1);
    }
}
void loop() {
    float pressure = bmp.readPressure(); // Pressure in Pascals
    int heartRate = max30102.getHeartRate(); // Get HR from PPG

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" Pa, Heart Rate: ");
    Serial.println(heartRate);

    delay(1000);
}