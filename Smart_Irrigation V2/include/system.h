#pragma once

#include <SIS.h>

class System
{
private:
    String sample;
public:
    String HostName();
    String Uptime();
    void init_SoftAP();
    // void onOTAStart();
    // void onOTAProgress(size_t current, size_t final);
    // void onOTAEnd(bool success);
    // void init_OTA();
    void init_sensors();
    void setMotorState(bool state);
    void init_actuators();
};
System sys;


String System::Uptime()
{
    uptime::calculateUptime();
    int _day = uptime::getDays();
    int _hour = uptime::getHours();
    int _min = uptime::getMinutes();
    int _sec = uptime::getSeconds();
    String dayStr = (_day < 10) ? ("0" + String(_day)) : String(_day);
    String hourStr = (_hour < 10) ? ("0" + String(_hour)) : String(_hour);
    String minStr = (_min < 10) ? ("0" + String(_min)) : String(_min);
    String secStr = (_sec < 10) ? ("0" + String(_sec)) : String(_sec);

    return dayStr + ":" + hourStr + ":" + minStr + ":" + secStr;
}

String System::HostName()
{
    String Hostname;
    Hostname = WiFi.macAddress(); // getting MAC address from esp and setting only last 6 char as hostname
    Hostname.replace(":", "");
    Hostname = "SIS_" + Hostname.substring(6);

    return Hostname;
}

void System::init_SoftAP()
{
    AP_SSID =  "AP_"+ HostName();
    WiFi.mode(WIFI_STA);
    WiFi.softAP(AP_SSID, AP_PASS);
    WiFi.softAPConfig(local_IP, gateway, subnet);
}

// void System::onOTAStart() {
//     // Log when OTA has started
//     Serial.println("OTA update started!");
//     // <Add your own code here>
// }

// void System::onOTAProgress(size_t current, size_t final) {
//     // Log every 1 second
//     if (millis() - ota_progress_millis > 1000) {
//       ota_progress_millis = millis();
//       Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
//     }
// }

// void System::onOTAEnd(bool success) {
//     // Log when OTA has finished
//     if (success) {
//       Serial.println("OTA update finished successfully!");
//     } else {
//       Serial.println("There was an error during OTA update!");
//     }
//     // <Add your own code here>
// }

// void System::init_OTA()
// {
//     ElegantOTA.begin(server);    // Start ElegantOTA
//     // ElegantOTA callbacks
//     ElegantOTA.onStart(onOTAStart);
//     ElegantOTA.onProgress(onOTAProgress);
//     ElegantOTA.onEnd(onOTAEnd);                 // Start OTA Update
// }

void System::init_sensors() {
    dht.begin();    //dht sensor

    pinMode(DHTPIN, INPUT);
    pinMode(LDR_PIN, INPUT);
    pinMode(MOIS_PIN, INPUT);
}

// Function to update motor state
void System::setMotorState(bool state) {
    digitalWrite(RELAY_PIN, state ? HIGH : LOW);
    motorState = state;
    Serial.print("Motor State: ");
    Serial.println(state ? "ON" : "OFF");
}

void System::init_actuators() {
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    setMotorState(false); // Initially turn off the motor
}


/*======================= General Functions: ==========================*/


// String jsonInfo()
// {
//     StaticJsonDocument<300> jsonDoc;  // Create a JSON document using DynamicJsonDocument

//     jsonDoc["Version"] = FW_VERSION;  // Populate the JSON document with data
//     jsonDoc["HostName"] = sys.HostName();
//     jsonDoc["Local_IP"] = WiFi.softAPIP();
//     jsonDoc["Uptime"] = sys.Uptime();
//     jsonDoc["FreeHeap"] = String(ESP.getFreeHeap());

//     jsonDoc["Motor Status"] = rly_status;
//     jsonDoc["Soil Moisture"] = moisValue;
//     jsonDoc["Temperature"] = temp;
//     jsonDoc["Humidity"] = hum;
//     jsonDoc["LDR"] = ldrValue;

//     String jsonInfoString;  // Serialize the JSON document to a string
//     serializeJsonPretty(jsonDoc, jsonInfoString);

//     return jsonInfoString;
// }