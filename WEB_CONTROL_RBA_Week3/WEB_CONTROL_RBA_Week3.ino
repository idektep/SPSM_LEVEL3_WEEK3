#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver idektep = Adafruit_PWMServoDriver(0x40);
#define SERVOMIN 100
#define SERVOMAX 600

//-----------------------------------------------Set your device name and password.--------------------------------------//
const char *ssid = "RobotArm";
const char *password = "12345678";
//-----------------------------------------------------------------------------------------------------------------------//

//------------------------------Define address PCA Drive robot arm-----------------------------------//

#define servo1 0





//---------------------------------------------------------------------------//
int countFlag = 0;
const char *hold_flag = "99";

int delay_value = 10;
int Home = 0;  //Home
int poscountmax = 180;

//---------------------------------------------------------------------------//

int pos1 = 0;






//---------------------------------------------------------------------------//
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


void setup() {
  Serial.begin(115200);
  idektep.begin();
  idektep.setPWMFreq(60);
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  server.begin();
  Serial.println("HTTP server started");
  //-------------------------------------//
  
//------------------------HomePosition Robot Arm-----------------------------//
  pos1 = 90;





  idektep.setPWM(servo1, 0, angleToPulse(pos1));





//---------------------------------------------------------------------------//
}

void loop() {
  ws.cleanupClients();
  processRobotArmMovement();
}
