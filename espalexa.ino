#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


#define led 16  //D1
// prototypes
boolean connectWifi();

//callback functions
void Device(uint8_t brightness);

// WiFi Credentials
const char* ssid = "ADD SSID";
const char* password = "ADD PASSWORD";

// device names
String Device_1_Name = "Test Device Name";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(led, OUTPUT);
   digitalWrite(led, HIGH);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, Device); 

  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
    digitalWrite(led, HIGH);
      Serial.println("Device1 ON");
       delay(2500);
          digitalWrite(led, LOW);
             Serial.println("Device1 off");
}

void loop()
{
  espalexa.loop();
  delay(1);


  

}

//our callback functions
void Device(uint8_t brightness)
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





// connect to wifi  returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
