#ifndef SENSORPACKAGEUTIL_H
#define SENSORPACKAGEUTIL_H

#include <Arduino.h>

// Function to escape JSON strings
String jsonEscape(const String& str) {
    String escaped = str;
    escaped.replace("\"", "\\\"");
    escaped.replace("\\", "\\\\");
    escaped.replace("/", "\\/");
    escaped.replace("\b", "\\b");
    escaped.replace("\f", "\\f");
    escaped.replace("\n", "\\n");
    escaped.replace("\r", "\\r");
    escaped.replace("\t", "\\t");
    return escaped;
}

// Function to add key-value pairs to a JSON string
void addJsonKeyValuePair(String& json, const String& key, const String& value) {
    json += "\"" + jsonEscape(key) + "\":\"" + jsonEscape(value) + "\",";
}

// Function to add key-value pairs to a JSON string with numeric values
template<typename T>
void addJsonKeyValuePair(String& json, const String& key, T value) {
    json += "\"" + jsonEscape(key) + "\":" + String(value) + ",";
}

#endif
