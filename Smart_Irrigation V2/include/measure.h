#pragma once

#include "SIS.h"

class Measure
{
private:
    float _temp;
    uint8_t _hum;
    uint8_t _mois;
    float _ldr;
    float _relay;
public:
    void DHT_Loop();
    void LDR_Loop();
    void MOIS_Loop();
    void RELAY_ON();
    void RELAY_OFF();
    void GLED_ON();
    void GLED_OFF();
    void RLED_ON();
    void RLED_OFF();
    void LED_control();
    
};
Measure msr;

void Measure::DHT_Loop()
{
    // Read temperature as Celsius (the default)
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(hum) || isnan(temp)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
}

void Measure::LDR_Loop()
{
    ldrValue = digitalRead(LDR_PIN);
    Serial.println(ldrValue);
}

void Measure::MOIS_Loop()
{
    int sensorValue = analogRead(MOIS_PIN);  // Read the analog value from sensor
    moisValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
}

void Measure::RELAY_ON() {
    digitalWrite(RELAY_PIN, HIGH);
}

void Measure::RELAY_OFF() {
    digitalWrite(RELAY_PIN, LOW);
}

void Measure::GLED_ON() {
    digitalWrite(LED_GREEN, HIGH);
}

void Measure::GLED_OFF() {
    digitalWrite(LED_GREEN, LOW);
}

void Measure::RLED_ON() {
    digitalWrite(LED_RED, HIGH);
}

void Measure::RLED_OFF() {
    digitalWrite(LED_RED, LOW);
}

void Measure::LED_control() {
    if (digitalRead(RELAY_PIN) == 1) {
        GLED_ON();
        RLED_OFF();
    } else if (digitalRead(RELAY_PIN) == 0) {
        GLED_OFF();
        RLED_ON();
    }

}