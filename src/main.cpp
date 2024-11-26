#include <Arduino.h>

#include "ProjectInfo.h"
#include "masthead.h"

#include "serialmanager.h"
#include "sensordata.h"
#include "usbcomm.h"
#include "presenter.h"
#include "sensorpackage.h"

#include "temperature_sensor.h"
#include "humidity_sensor.h"
#include "pressure_sensor.h"
#include "light_sensor.h"

SerialManager serialManager;
SensorPackage sensorPackage("esp32-usbclient", serialManager);
Presenter presenter(sensorPackage.getSensorDataManager(), serialManager, "SensorPackage");

void setup() {
    serialManager.initialize(115200);
    serialManager.log("ESP32 USB Device Ready");
    Serial.setDebugOutput(true);  // Enable debug output

    // Add sensors
    sensorPackage.addSensor(new TemperatureSensor());
    sensorPackage.addSensor(new HumiditySensor());
    sensorPackage.addSensor(new PressureSensor());
    sensorPackage.addSensor(new LightSensor());

    // Print project information
    serialManager.log(masthead());
}

void loop() {
    sensorPackage.updateSensorData();
    handleUSBCommunication(presenter, serialManager, sensorPackage);
    delay(1000);  // Delay for stability
}
