#include <SIS.h>

void setup() {
    Serial.begin(115200);

    sys.init_sensors();
    sys.init_actuators();
    
    delay(2000);
    sys.init_SoftAP();   //To Initialize WiFi Acces Point(AP)
    
    ws.init_WebServer();  //To Initialize Webserver
}

void loop() {
    delay(1000);
    msr.DHT_Loop(); 
    msr.LDR_Loop();
    msr.MOIS_Loop();
    msr.LED_control();

}