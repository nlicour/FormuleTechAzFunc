#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *SSID = "RAJA_WIFI_I";
const char *password = "EA588b9NsyNiBDPs6hPxiaxAkeRnY5J3";

unsigned long dt, timer = 0;

int ledState = 0;

bool state;

String serverName = "http://192.168.1.189/";
HTTPClient http;
WiFiClient client;

void startWifiConnection()
{
  // Connect to WiFi network
  Serial.println();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.print(WiFi.localIP());
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(D7, INPUT_PULLUP);

  startWifiConnection();
  state = false;
}

void loop()
{
  // put your main code here, to run repeatedly:
  dt = millis() - timer;
  state = digitalRead(D7) == LOW;
  if (dt >= 70) // True for every 500 ms.
  {
    timer = millis();
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      if (state)
      {
        //Serial.println("1\n");
        Serial.println("state =:" + String(ledState) + "\n");

        ledState = ledState == 0 ? 1 : 0;
        String serverPath = serverName + "setLedState?state="+ ledState;

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
        {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        }
        else
        {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
        delay(300);
      }
      // else
      // {
      //   Serial.println("0\n");
      // }
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
  }
}