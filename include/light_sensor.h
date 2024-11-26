#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "sensor.h"

class LightSensor : public Sensor {
public:
    LightSensor() : Sensor("Light Sensor") {}

protected:
    bool read_sensor_data() override {
        float light = random(0, 1000);  // Simulate light intensity (0 to 1000 lux)
        setData("Light", String(light));
        return true;
    }
};

#endif
