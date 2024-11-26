#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "serialmanager.h"
#include "sensor.h"
#include <vector>

class SensorDataManager {
public:
    SensorDataManager() : logger(nullptr), systemStartTime(0) {}

    void initialize(SerialManager& logManager) {
        logger = &logManager;
        systemStartTime = millis();
    }

    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
        sensor->initialize(*logger);
    }

    void updateSensorData() {
        for (auto& sensor : sensors) {
            sensor->collectData();
        }
    }

    unsigned long getUptime() const {
        return (millis() - systemStartTime) / 1000;  // Return uptime in seconds
    }

    std::vector<Sensor*> getSensors() const {
        return sensors;
    }

private:
    SerialManager* logger;
    std::vector<Sensor*> sensors;
    unsigned long systemStartTime;
};

#endif
