#pragma once

#include <SIS.h>
#include "HTML_index.h"

int _rlyStatus;
void homePage(AsyncWebServerRequest *request);
void handleEspInfo(AsyncWebServerRequest *request);

class WebServer
{
private:

    void routes();
    void resetESP();
public:
    void init_WebServer(){
        routes();
        resetESP();
        server.begin();
    }
};
WebServer ws;

void WebServer::routes()
{
    server.on("/", homePage);
    
    
    server.on("/relay1", HTTP_GET, [](AsyncWebServerRequest *request){
        String state = request->arg("state");
        if (state == "1") {
            msr.RELAY_ON();
            _rlyStatus = 1;
        }
        else if (state == "0") {
            msr.RELAY_OFF();
            _rlyStatus = 0;
        }
        request->send(200, "text/plain", "OK");
    });

    server.on("/relay1_state", HTTP_GET, [](AsyncWebServerRequest *request){
        int state = _rlyStatus;
        request->send(200, "text/plain", String(state));
    });

    server.on("/espInfo", handleEspInfo);

    // server.on("/jsonInfo", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     String jsonInfoStr = jsonInfo();
    //     request->send_P(200, "text/json", jsonInfoStr.c_str());
    // });

}

// 🔹 Home Page Handler Function
void homePage(AsyncWebServerRequest *request)
{
    // Sensor Data (Dynamic Content in RAM)
    String message = "";
    message += "<div style='max-width:600px; margin:auto; background:white; padding:20px; border-radius:10px; box-shadow:0px 0px 10px rgba(0,0,0,0.1);'>";
    message += "<header class='header'><h1>IncepicX JM EduTech Services</h1><h2>IOT Wireless Dashboard</h2></header><h2 style='color:#2c3e50; border-bottom:2px solid #2c3e50; padding-bottom:5px; text-align:center;'>Monitoring System</h2>";

    message += "<p style='text-align:center; font-size:18px;'> <strong>Uptime:</strong> <span id='uptime'>" + sys.Uptime() + "</span></p>";
    message += "<p style='text-align:center; font-size:18px;'> <strong>Soil Moisture:</strong> <span id='moisture'>" + String(moisValue) + "</span> %</p>";
    message += "<p style='text-align:center; font-size:18px;'> <strong>Temperature:</strong> <span id='temperature'>" + String(temp) + "</span> °C</p>";
    message += "<p style='text-align:center; font-size:18px;'> <strong>Humidity:</strong> <span id='humidity'>" + String(hum) + "</span> %</p>";
    message += "<p style='text-align:center; font-size:18px;'> <strong>Day/Night:</strong> <span id='ldrValue'>" + String((ldrValue == 0) ? "Day" : "Night") + "</span></p>";

    // Send Response with Sensor Readings + Control System UI
    request->send(200, "text/html", message + String(htmlPage));
}



void handleEspInfo(AsyncWebServerRequest *request)
{
    String espInfo;
        espInfo += "\nFirmware Version      : " + String(FW_VERSION);
        espInfo += "\nStation ID            : " + sys.HostName();
        espInfo += "\nFree Heap             : " + (String) ESP.getFreeHeap();
        espInfo += "\nFree OTA Sketch Space : " + (String) ESP.getFreeSketchSpace();
        espInfo += "\nWiFi-AP SSID          : " + AP_SSID;
        espInfo += "\nWiFi-AP PASSWORD      : " + AP_PASS;
        espInfo += "\nWiFi-AP Mac Address   : " + WiFi.macAddress();
    request->send(200, "text/plain", espInfo);
}

void WebServer::resetESP(){
  server.on("/resetBoard", HTTP_GET, [](AsyncWebServerRequest *request){
    String espreset = "<html><body>";
    espreset += "<script>";
    espreset += "if (confirm('Click OK to RESET DEVICE.')) {";
    espreset += "   window.location.href = '/ESPrestart?nocache=" + String(millis()) + "';";
    espreset += "} else {";
    espreset += "   window.location.href = '/reset=esp?nocache=" + String(millis()) + "';";
    espreset += "}";
    espreset += "</script>";
    espreset += "</body></html>";
    request->send(200, "text/html", espreset);
  });
  server.on("/ESPrestart", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("ESP Device Resetting!...");
    request->redirect("/resetBoard");
    delay(5000);
    ESP.restart();
  });
}