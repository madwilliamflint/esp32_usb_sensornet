#ifndef PRESENTER_H
#define PRESENTER_H

#include "sensordata.h"
#include "serialmanager.h"
#include "sensorpackageutil.h"

class Presenter {
public:
    Presenter(SensorDataManager& sensorManager, SerialManager& logger, const String& packageName)
        : sensorManager(sensorManager), logger(logger), packageName(packageName) {}

    String prepareOutputData(bool asJson = true) {
        if (asJson) {
            return prepareJsonData();
        } else {
            return prepareStringData();
        }
    }

private:
    String prepareJsonData() {
        String json = "{";
        addJsonKeyValuePair(json, "packageName", packageName);
        addJsonKeyValuePair(json, "Uptime", sensorManager.getUptime());

        json += "\"Sensors\":{";
        for (const auto& sensor : sensorManager.getSensors()) {
            json += "\"" + jsonEscape(sensor->getSensorName()) + "\":{";
            addSensorDetailsToJson(json, sensor);
            json.remove(json.length() - 1);  // Remove trailing comma
            json += "},";
        }
        json.remove(json.length() - 1);  // Remove trailing comma
        json += "}";

        json += "}";
        logger.log("Prepared JSON data for USB: " + json);
        return json;
    }

    void addSensorDetailsToJson(String& json, Sensor* sensor) {
        String dataString = sensor->getData();
        char dataStr[dataString.length() + 1];
        strcpy(dataStr, dataString.c_str());
        char* token = strtok(dataStr, ",");
        while (token != nullptr) {
            String keyValue(token);
            int delimiterPos = keyValue.indexOf(':');
            if (delimiterPos > 0) {
                String key = keyValue.substring(0, delimiterPos);
                String value = keyValue.substring(delimiterPos + 1);
                addJsonKeyValuePair(json, key, value);
            }
            token = strtok(nullptr, ",");
        }
        addJsonKeyValuePair(json, "LastSuccessAge", sensor->getLastSuccessAge());
        addJsonKeyValuePair(json, "SuccessRate", sensor->getSuccessRate());
    }

    String prepareStringData() {
        String dataString = "DATA:Uptime:" + String(sensorManager.getUptime()) + "s,";
        for (const auto& sensor : sensorManager.getSensors()) {
            dataString += sensor->getData() + ",";
            dataString += "LastSuccessAge:" + String(sensor->getLastSuccessAge()) + "s,";
            dataString += "SuccessRate:" + String(sensor->getSuccessRate()) + "%,";
        }
        dataString.remove(dataString.length() - 1);  // Remove trailing comma
        logger.log("Prepared data for USB: " + dataString);
        return dataString;
    }

    SensorDataManager& sensorManager;
    SerialManager& logger;
    String packageName;
};

#endif
