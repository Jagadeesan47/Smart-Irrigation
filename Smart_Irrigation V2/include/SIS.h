#pragma once

#define FW_VERSION "1.5.3"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <uptime.h>
#include <ArduinoJson.h>
// #include "update.h"
#include "DHT.h"


/* Defining Macros
================*/

#define DHTPIN 4  // DHT-11 Sensor Pin
#define DHTTYPE DHT11   // DHT 11
#define MOIS_PIN A0 // Soil Moisture Sensor Pin
#define LDR_PIN 2  // Light Sensor Pin

#define RELAY_PIN 5  // Relay for Motor Control
#define LED_RED 12    // Red LED (Indicates Problem)
#define LED_GREEN 13  // Green LED (Indicates Normal)


/*Variable Declarations
=====================*/
String AP_SSID = "HostName + ~AP";
String AP_PASS = "1234567890";


float temp, hum;
int moisValue, ldrValue;
bool rly_status;
bool motorState = false;  // Variable to store motor state// HTML Page (Ensure this is included)
extern const char htmlPage[] PROGMEM;

/*Declaring Instances
===================*/
IPAddress local_IP(192, 168, 1, 2);  // Config Static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

DHT dht(DHTPIN, DHTTYPE);

AsyncWebServer server(80);                          //For Webserver


/*General Functions
====================*/


/*Created Header Files
====================*/
#include "measure.h"
#include "system.h"
#include "webserver.h"
