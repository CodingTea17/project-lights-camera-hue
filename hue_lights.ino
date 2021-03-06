#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
// A file I declared my passwords and other sensitive info in
// Delete it if you don't have one
#include "env.h"

const char* SSID = YOURWIFINAME;
const char* PASSWORD = YOURWIFIPASSWORD;
String NETWORK_ADDRESS = String("http://") + YOURHUEHUBIP;

void setup() {
  // Turn on serial connection @ baud = 115200
  Serial.begin(9600);

  // Connect to the WiFi using the constants SSID and PASSWORD
  WiFi.begin(SSID, PASSWORD);

  // Show 'Connecting..' until the status becomes "connected"
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  // Once the status becomes "connected" print "Connected"
  Serial.println("Connected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(String("http://") + YOURHUEHUBIP + String("/api/") + YOURDEVICEUSERNAME + String("/lights/2"));

    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode > 0) {
      const size_t capacity =  JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(11);
      DynamicJsonBuffer jsonBuffer(capacity);
      String httpResponse = http.getString();
      http.end();
      JsonObject& response = jsonBuffer.parseObject(httpResponse);
      if(response.success()) {
        http.begin(String("http://") + YOURHUEHUBIP + String("/api/") + YOURDEVICEUSERNAME + String("/lights/2/state"));
        String onState = response["state"]["on"];
        if(onState == "true") {
          http.PUT("{\"on\":false}");
        }
        http.end();
      }
    }
  }
  delay(30000);
}
