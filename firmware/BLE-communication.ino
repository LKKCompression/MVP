#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

void setup() {
    Serial.begin(115200);
    BLEDevice::init("LKK Compression Sock");
    pServer = BLEDevice::createServer();
    pCharacteristic = pServer->createCharacteristic(
                        BLEUUID((uint16_t)0x2A37),
                        BLECharacteristic::PROPERTY_READ | 
                        BLECharacteristic::PROPERTY_NOTIFY
                    );
    pServer->getAdvertising()->start();
}

void loop() {
    float pressure = bmp.readPressure();
    char buffer[10];
    dtostrf(pressure, 6, 2, buffer);
    pCharacteristic->setValue(buffer);
    pCharacteristic->notify();
    delay(1000);
}
