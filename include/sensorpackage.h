#ifndef SENSORPACKAGE_H
#define SENSORPACKAGE_H

#include "serialmanager.h"
#include "sensordata.h"
#include "sensorpackageutil.h"
#include "ProjectInfo.h"
#include <map>

class SensorPackage {
public:
    SensorPackage(const String& packageName, SerialManager& logger)
        : packageName(packageName), logger(logger) {
        systemStartTime = millis();
        // Add project information
        addMetadata("ProjectName", PROJECT_NAME);
        addMetadata("Author", AUTHOR);
        addMetadata("Version", VERSION);
        addMetadata("BuildNumber", BUILD_NUMBER);
        addMetadata("LastUpdate", LAST_UPDATE);
        addMetadata("Hostname", HOSTNAME);
    }

    void addSensor(Sensor* sensor) {
        sensorDataManager.addSensor(sensor);
    }

    void updateSensorData() {
        sensorDataManager.updateSensorData();
    }

    String getUptime() const {
        return String((millis() - systemStartTime) / 1000);
    }

    void addMetadata(const String& key, const String& value) {
        metadata[key] = value;
    }

    std::map<String, String> getMetadata() const {
        return metadata;
    }

    SensorDataManager& getSensorDataManager() {
        return sensorDataManager;
    }

    String getPackageName() const {
        return packageName;
    }

    void handleCommand(const String& command, Presenter& presenter) {
        if (command.equals("GET_DATA")) {
            sendData(presenter, false);
        } else if (command.equals("GET_DATA_JSON")) {
            sendData(presenter, true);
        } else if (command.equals("GET_EXHAUSTIVE_DATA")) {
            sendExhaustiveData(presenter);
        } else {
            logger.log("Unknown command received: " + command);
            Serial.println("ERROR: Unknown command");
        }
    }

private:
    void sendData(Presenter& presenter, bool asJson) {
        String dataString = presenter.prepareOutputData(asJson);
        Serial.println(dataString);
        logger.log("Sent data over USB: " + dataString);
    }

    void sendExhaustiveData(Presenter& presenter) {
        String json = "{";
        addJsonKeyValuePair(json, "packageName", packageName);
        addJsonKeyValuePair(json, "Uptime", getUptime());

        // Add metadata
        addMetadataToJson(json);

        // Add sensor data
        addSensorDataToJson(json);

        json.remove(json.length() - 1);  // Remove trailing comma
        json += "}";

        Serial.println(json);
        logger.log("Sent exhaustive data over USB: " + json);
    }

    void addMetadataToJson(String& json) {
        for (const auto& pair : metadata) {
            addJsonKeyValuePair(json, pair.first, pair.second);
        }
    }

    void addSensorDataToJson(String& json) {
        json += "\"Sensors\":{";
        for (const auto& sensor : sensorDataManager.getSensors()) {
            json += "\"" + jsonEscape(sensor->getSensorName()) + "\":{";
            addSensorDetailsToJson(json, sensor);
            json.remove(json.length() - 1);  // Remove trailing comma
            json += "},";
        }
        json.remove(json.length() - 1);  // Remove trailing comma
        json += "}";
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

    String packageName;
    SerialManager& logger;
    SensorDataManager sensorDataManager;
    std::map<String, String> metadata;
    unsigned long systemStartTime;
};

#endif
