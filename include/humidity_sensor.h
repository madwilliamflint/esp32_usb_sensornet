#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "sensor.h"

class HumiditySensor : public Sensor {
public:
    HumiditySensor() : Sensor("Humidity Sensor") {}

protected:
    bool read_sensor_data() override {
        float humidity = random(300, 700) / 10.0;  // Simulate humidity (30.0 to 70.0 %)
        setData("Humidity", String(humidity));
        return true;
    }
};

#endif
