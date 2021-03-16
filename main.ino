#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager


#define TRIGGER_PIN 0

#define led 16  //D1

      #include <Espalexa.h>
      void Test(uint8_t brightness);
      String Device_1_Name = "Test";
      Espalexa espalexa;
     
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\n Starting");

  pinMode(TRIGGER_PIN, INPUT);
  
        espalexa.addDevice(Device_1_Name, test); 
        espalexa.begin();
}

   
void loop() {
              pinMode(led, OUTPUT);
  // is configuration portal requested?
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
    WiFiManager wifiManager;


    //wifiManager.resetSettings();
    
    if (!wifiManager.startConfigPortal("TestWifi")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  espalexa.loop();
  // put your main code here, to run repeatedly:

}


//our callback functions
void test(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(led, HIGH);
      Serial.println("Device1 ON");
    }
  else
  {
    digitalWrite(led, LOW);
    Serial.println("Device1 OFF");
  }
}
