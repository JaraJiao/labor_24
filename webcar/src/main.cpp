#include <Arduino.h>
#include <WiFi.h>
#include <iostream>
#include <sstream>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

#define RIGHT_MOTOR 0
#define LEFT_MOTOR 1

#define FORWARD 1
#define BACKWARD -1

const int PWMFreq = 1000; //1KHz
const int PWMResolution = 8;
const int PWMSpeedChannel = 4;

const char* ssid = "A08-Car"
const char* password = "12345678"

AsyncWebServer servwe(80);
AsyncWebServer wsCarInput("/CarInput");

struct MOTOR_PINS
{
  int pinEN;
  int pinIN1;
  int pinIN2;
};

std::vector<MOTOR_PINS> motorPins =
{
  {22,16,17},  // Right motor (EnA, IN1, IN2)
  {23,18,19}. // Left moto    (EnB, IN3, IN4)
};


void setUpPinModes()
{
  ledcSetup(PWMSpeedChannel,PWMFreq,PWMResolution);

  for (int i=0; i< motorPins.size(); i++)
  {
    pinMode(motorPin[i].pinEN, OUTPUT);
    pinMode(motorPin[i].pinIN1, OUTPUT);
    pinMode(motorPin[i].pinIN2, OUTPUT);

    ledcAttachPin(motorPins[i].pinEn, PWMSpeedChannel);
  }
  

}

void setup() {
// put your setup code here, to run once:
setUpPinModes();
Serial.begin(115200);

WiFi.softAP(ssid, password);
IPAddress IP = WiFi.softAPIP();
Serial.print("AP IP address:");
Serial.println(IP);

Server.ON("/", HTTP_GET, handleRoot);
Server.onNotFound(handleNotFound);

wsCarInput.onEvent(onCarInputWebSocketEvent);
server.addHandler(&wsCarInput);
server.begin();
Serial.println("HTTP Server started");
 
}

void loop() {

}