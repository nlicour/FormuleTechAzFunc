#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const int ledRedPin = D4;
const int ledGreenPin = D2;
const int ledBluePin = D1;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int beforeOffRedValue = 0;
int beforeOffGreenValue = 0;
int beforeOffBlueValue = 0;

const char *SSID = "RAJA_WIFI_I";
const char *password = "EA588b9NsyNiBDPs6hPxiaxAkeRnY5J3";

AsyncWebServer server(80);

void dimToValue(int ledPin, int oldValue = 0, int newValue = 0)
{
  if (oldValue < newValue)
  {
    for (int i = oldValue; i < 1023 && i <= newValue; i++)
    {
      // changing the LED brightness with PWM
      analogWrite(ledPin, i);
      delay(20);
    }
  }
  else if (newValue < oldValue)
  {
    for (int i = oldValue; i > 0 && i > newValue; i--)
    {
      // changing the LED brightness with PWM
      analogWrite(ledPin, i);
      delay(20);
    }
  }
}

// in 8 bit format (value max is 255)
void setRGB(int r = 0, int g = 0, int b = 0)
{
  dimToValue(ledRedPin, redValue, r);
  dimToValue(ledGreenPin, greenValue, g);
  dimToValue(ledBluePin, blueValue, b);
  redValue = r;
  greenValue = g;
  blueValue = b;
}

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

void notFound(AsyncWebServerRequest *request)
{
  if (request->method() == HTTP_OPTIONS)
  {
    request->send(200);
  }
  else
  {
    request->send(404, "text/plain", "Not found");
  }
}

void setRgbWebFunction(AsyncWebServerRequest *request)
{
  int red = redValue;
  int green = greenValue;
  int blue = blueValue;

  String message;
  if (request->hasParam("red"))
  {
    message = request->getParam("red")->value();
    red = message.toInt();
  }
  if (request->hasParam("green"))
  {
    message = request->getParam("green")->value();
    green = message.toInt();
  }

  if (request->hasParam("blue"))
  {
    message = request->getParam("blue")->value();
    blue = message.toInt();
  }
  setRGB(red, green, blue);

  beforeOffRedValue = redValue;
  beforeOffGreenValue = greenValue;
  beforeOffBlueValue = blueValue;

  request->send(200, "text/plain", "Ok, rgb value set to: r:" + String(red) + " g:" + String(green) + " b:" + String(blue));
}

void setLedState(AsyncWebServerRequest *request)
{
  String message;
  if (request->hasParam("state"))
  {
    message = request->getParam("state")->value();
    if (message.toInt() == 0)
    {

      setRGB(0, 0, 0);
    }
    else
    {
      setRGB(beforeOffRedValue, beforeOffGreenValue, beforeOffBlueValue);
    }
  }

  request->send(200, "text/plain", "Ok, led state value set to: " + message);
}

void startWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "endpoints ->\n -- setRgb (params -> red(int), green(int), blue(int))\nexemple -> http://192.168.1.176/setRgb?red=0&green=255&blue=0\n-- setLedState (params -> state(int - 0 ou 1))\nexemple -> http://192.168.1.176/setLedState?state=0"); });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/setRgb", HTTP_GET, [](AsyncWebServerRequest *request)
            { setRgbWebFunction(request); });

  server.on("/setLedState", HTTP_GET, [](AsyncWebServerRequest *request)
            { setLedState(request); });

  server.onNotFound(notFound);

  //DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  server.begin();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9200);
  delay(10);
  startWifiConnection();
  startWebServer();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
