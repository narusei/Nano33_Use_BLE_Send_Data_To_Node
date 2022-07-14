/*
  Acceleration　Data Logger using BLE.
  Please write this sketch to nano33BLE.
  Then, Starting Blegger.
  Blegger : https://github.com/narusei/blegger
*/

#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

#define LSM9DS1_SERVICE_UUID   "92c25488-dcbc-11ec-9d64-0242ac120002"

#define LSM9DS1_Acceleration_Characteristic_UUID    "97e480da-dcbc-11ec-9d64-0242ac120002"
#define LSM9DS1_Gyroscope_Characteristic_UUID       "dc5d8910-dcca-11ec-9d64-0242ac120002"

#define localNAME "IMUMonitor"
#define DeviceNAME "nano33BLE"

// Bluetooth® Low Energy Battery Service
BLEService Sensor_LSM9DS1_Service(LSM9DS1_SERVICE_UUID);

// Bluetooth® Low Energy Battery Level Characteristic
BLEStringCharacteristic LSM9DS1_Acceleration(LSM9DS1_Acceleration_Characteristic_UUID, BLERead | BLENotify, 24);
BLEStringCharacteristic LSM9DS1_Gyroscope(LSM9DS1_Gyroscope_Characteristic_UUID, BLERead | BLENotify, 24);

float AccelerationX = 0, AccelerationY = 0, AccelerationZ = 0;
float GyroscopeX = 0, GyroscopeY = 0, GyroscopeZ = 0;

float oldValue = 0;  // last value 
long previousMillis = 0;  // last time value was checked, in ms

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // initialize the built-in LED pin to indicate when a central is connected

  // begin ble initialization
  if (!BLE.begin()) {
    while (1);
  }
  
  // begin imu initialization
  if (!IMU.begin()) {
    while (1);
  }

  BLE.setLocalName(localNAME);
  BLE.setDeviceName(DeviceNAME);

  // Add the service UUID
  BLE.setAdvertisedService(Sensor_LSM9DS1_Service);

  // Add characteristic
  Sensor_LSM9DS1_Service.addCharacteristic(LSM9DS1_Acceleration);
  Sensor_LSM9DS1_Service.addCharacteristic(LSM9DS1_Gyroscope);

  // Add the service
  BLE.addService(Sensor_LSM9DS1_Service);
  
  // Set initial value for this characteristic
  LSM9DS1_Acceleration.writeValue(String(oldValue));
  LSM9DS1_Gyroscope.writeValue(String(oldValue));

  // Start advertising
  BLE.advertise();
}

void loop() {
  // wait for a Bluetooth® Low Energy central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral:
  if (central) {
    delay(100);
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()) {
      long currentMillis = millis();
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
        updateValue();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void updateValue() {
  readLSM9DS1();
  String valueof_LSM9DS1_Acceleration = String(AccelerationX) + "," +  String(AccelerationY) + "," + String(AccelerationZ);
  String valueof_LSM9DS1_Gyroscope = String(GyroscopeX) + "," +  String(GyroscopeY) + "," + String(GyroscopeZ);
  float aSum = fabs(AccelerationX) + fabs(AccelerationY) + fabs(AccelerationZ);
  if (aSum != oldValue) {
    LSM9DS1_Acceleration.writeValue(valueof_LSM9DS1_Acceleration);
    LSM9DS1_Gyroscope.writeValue(valueof_LSM9DS1_Gyroscope);
    oldValue = aSum;
  }
}

void readLSM9DS1() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(AccelerationX, AccelerationY, AccelerationZ);
  }
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(GyroscopeX, GyroscopeY, GyroscopeZ);
  } 
}
