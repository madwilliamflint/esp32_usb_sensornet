#ifndef SENSOR_H
#define SENSOR_H

#include "serialmanager.h"
#include <map>

class Sensor {
public:
    Sensor(const String& name) : name(name), lastSuccessTime(0), successCount(0), totalAttempts(0) {}

    virtual void initialize(SerialManager& logger) {
        this->logger = &logger;
        logger.log(name + " initialized");
    }

    virtual bool collectData() {
        recordAttempt();
        bool success = read_sensor_data();
        if (success) {
            recordSuccess();
        }
        return success;
    }

    virtual String getData() const {
        String data;
        for (const auto& pair : dataMap) {
            data += pair.first + ":" + pair.second + ",";
        }
        data.remove(data.length() - 1);  // Remove trailing comma
        return data;
    }

    unsigned long getLastSuccessAge() const {
        return (millis() - lastSuccessTime) / 1000;
    }

    float getSuccessRate() const {
        return totalAttempts > 0 ? (successCount * 100.0 / totalAttempts) : 0.0;
    }

    String getSensorName() const {
        return name;
    }

protected:
    virtual bool read_sensor_data() = 0;

    void setData(const String& key, const String& value) {
        dataMap[key] = value;
        logger->log(name + " data collected: " + key + " = " + value);
    }

private:
    void recordSuccess() {
        lastSuccessTime = millis();
        successCount++;
    }

    void recordAttempt() {
        totalAttempts++;
    }

    String name;
    SerialManager* logger;
    std::map<String, String> dataMap;
    unsigned long lastSuccessTime;
    unsigned long successCount;
    unsigned long totalAttempts;
};

#endif
