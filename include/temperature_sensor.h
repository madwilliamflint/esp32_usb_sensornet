#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "sensor.h"

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor() : Sensor("Temperature Sensor") {}

protected:
    bool read_sensor_data() override {
        float temperature = random(200, 350) / 10.0;  // Simulate temperature (20.0 to 35.0 C)
        setData("Temperature", String(temperature));
        return true;
    }
};

#endif
