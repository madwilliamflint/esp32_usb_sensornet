#ifndef MASTHEAD_H
#define MASTHEAD_H

#include "ProjectInfo.h"
#include <Arduino.h>

String masthead() {
  String projectInfo = "";
  projectInfo += "Project Name: " + String(PROJECT_NAME) + "\n";
  projectInfo += "Author: " + String(AUTHOR) + "\n";
  projectInfo += "Version: " + String(VERSION) + "\n";
  projectInfo += "Build Number: " + String(BUILD_NUMBER) + "\n";
  projectInfo += "Last Update: " + String(LAST_UPDATE) + "\n";
  projectInfo += "Hostname: " + String(HOSTNAME) + "\n";
  return projectInfo;
}

#endif
