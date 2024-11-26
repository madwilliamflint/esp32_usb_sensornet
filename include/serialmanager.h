#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <Arduino.h>

class SerialManager {
public:
    void initialize(long baudRate) {
        Serial.begin(baudRate);
        while (!Serial) {
            // Wait for Serial connection
        }
        Serial.println("Serial connection initialized.");
    }

    void log(const String& message) {
        Serial.println(message);
    }

    void log(const char* message) {
        Serial.println(message);
    }

    void log(float value) {
        Serial.println(value);
    }

    void log(int value) {
        Serial.println(value);
    }
};

#endif
