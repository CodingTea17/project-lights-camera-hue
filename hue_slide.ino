#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* SSID = "YOURWIFINAME";
const char* PASSWORD = "YOURWIFIPASSWORD";
const char* NETWORK_ADDRESS = "http://YOURHUEHUBIP";
int slideSwitch = 13;
bool slideState = false;
String lightState = "false";

void setup() {
  // Turn on serial connection @ baud = 115200
  Serial.begin(9600);
  Serial.println("");
  // Connect to the WiFi using the constants SSID and PASSWORD
  WiFi.begin(SSID, PASSWORD);
  slideState = digitalRead(slideSwitch);
  // Show 'Connecting..' until the status becomes "connected"
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  // Once the status becomes "connected" print "Connected"
  Serial.println("Connected");
}

void loop() {
  bool changed = didSlideChangeState();
  switch (changed) {
  case true:
    lightState = getLightState();
    Serial.println(lightState);
    Serial.println(slideState);
    if(lightState == "false" && slideState == 1) {
      setLight("true");
    } else if(lightState == "true" && slideState == 0) {
      setLight("false");
    }
    break;
  default:
    // Nada
    break; 
  }
  delay(1000);
}

bool didSlideChangeState() {
  bool currentSlideState = digitalRead(slideSwitch);
  if(slideState != currentSlideState) {
    slideState = currentSlideState;
    return true;
  }
  return false;
}

void setLight(String newLightState) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://YOURHUEHUBIP/api/YOURDEVICEUSERNAME/lights/2/state");
    String stateChange = String("{\"on\":") + newLightState + String("}");
    Serial.println(stateChange);
    http.PUT(stateChange);
    http.end();
  }
}

String getLightState() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.println("ping");
    http.begin("http://YOURHUEHUBIP/api/YOURDEVICEUSERNAME/lights/2");
    int httpCode = http.GET();
    if (httpCode > 0) {      
      String httpResponse = http.getString();
      const size_t capacity =  JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(11);
      DynamicJsonBuffer jsonBuffer(capacity);
      JsonObject& response = jsonBuffer.parseObject(httpResponse);
      if(response.success()) {
        return response["state"]["on"];
      }
    }
    http.end();
  }
  return "false";
}

