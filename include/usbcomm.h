#ifndef USBCOMM_H
#define USBCOMM_H

#include "presenter.h"
#include "sensorpackage.h"

void handleUSBCommunication(Presenter& presenter, SerialManager& logger, SensorPackage& sensorPackage) {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        logger.log("Received command: " + command);
        sensorPackage.handleCommand(command, presenter);
    }
}

#endif
