#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "sensor.h"

class PressureSensor : public Sensor {
public:
    PressureSensor() : Sensor("Pressure Sensor") {}

protected:
    bool read_sensor_data() override {
        float pressure = random(950, 1050);  // Simulate pressure (950 to 1050 hPa)
        setData("Pressure", String(pressure));
        return true;
    }
};

#endif
