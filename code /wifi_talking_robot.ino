/*
  Project: Wi-Fi Talking Robot
  Controller: NodeMCU ESP8266
  Motor Driver: L298N
  Audio Module: TG113 Bluetooth Amplifier

  Wi-Fi Network: WIFI CAR
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// L298N motor driver connections
#define ENA   14   // D5 - Left motor speed
#define ENB   12   // D6 - Right motor speed
#define IN_1  15   // D8
#define IN_2  13   // D7
#define IN_3  2    // D4
#define IN_4  0    // D3

const char* ssid = "WIFI CAR";

// Web server on port 80
ESP8266WebServer server(80);

String command = "";
int speedCar = 800;
const int speed_Coeff = 3;

// Set motor speed
void setMotorSpeed() {
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

// Move forward
void goAhead() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  setMotorSpeed();
}

// Move backward
void goBack() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  setMotorSpeed();
}

// Turn right
void goRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  setMotorSpeed();
}

// Turn left
void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  setMotorSpeed();
}

// Move forward-right
void goAheadRight() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENB, speedCar);
}

// Move forward-left
void goAheadLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar / speed_Coeff);
}

// Move backward-right
void goBackRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENB, speedCar);
}

// Move backward-left
void goBackLeft() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar / speed_Coeff);
}

// Stop robot
void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Handle commands received over Wi-Fi
void handleCommand() {
  if (server.hasArg("State")) {
    command = server.arg("State");
    Serial.println(command);

    if (command == "F") goAhead();
    else if (command == "B") goBack();
    else if (command == "L") goLeft();
    else if (command == "R") goRight();
    else if (command == "I") goAheadRight();
    else if (command == "G") goAheadLeft();
    else if (command == "J") goBackRight();
    else if (command == "H") goBackLeft();
    else if (command == "S") stopRobot();

    // Speed control
    else if (command == "0") speedCar = 400;
    else if (command == "1") speedCar = 470;
    else if (command == "2") speedCar = 540;
    else if (command == "3") speedCar = 610;
    else if (command == "4") speedCar = 680;
    else if (command == "5") speedCar = 750;
    else if (command == "6") speedCar = 820;
    else if (command == "7") speedCar = 890;
    else if (command == "8") speedCar = 960;
    else if (command == "9") speedCar = 1023;
    else stopRobot();
  }

  server.send(200, "text/plain", "Command received");
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  analogWriteRange(1023);
  stopRobot();

  // Create Wi-Fi access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  Serial.println("Wi-Fi Robot Started");
  Serial.print("Wi-Fi Name: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start web server
  server.on("/", handleCommand);
  server.onNotFound(handleCommand);
  server.begin();

  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
