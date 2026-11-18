# Wi-Fi-Talking-Robot
# Wi-Fi Talking Robot

## Project Overview
A Wi-Fi-controlled robotic vehicle developed using NodeMCU ESP8266. The robot receives movement commands through a mobile or web interface and uses a Bluetooth audio module to play sound through a speaker.

## Hardware Components
- NodeMCU ESP8266
- L298N Motor Driver Module
- Dual-Shaft BO Motors
- TG113 Bluetooth Amplifier Board
- Lithium-Ion Battery
- Speaker
- Robot Chassis and Connecting Wires

## Technologies Used
- Embedded C/C++
- Arduino IDE
- ESP8266 Wi-Fi
- HTTP Communication
- Bluetooth Audio

## Key Features
- Wireless robot control through Wi-Fi.
- Forward and backward movement.
- Left and right navigation.
- Diagonal movement.
- Adjustable motor speed.
- Bluetooth audio playback through speaker.

## Working Principle
1. NodeMCU creates a Wi-Fi access point.
2. A mobile control interface sends movement commands.
3. The ESP8266 web server receives and processes commands.
4. The L298N motor driver controls the DC motors.
5. The TG113 Bluetooth amplifier receives audio from a paired device and plays it through the speaker.

## Pin Connections

| L298N | NodeMCU |
|---|---|
| ENA | D5 (GPIO14) |
| ENB | D6 (GPIO12) |
| IN1 | D8 (GPIO15) |
| IN2 | D7 (GPIO13) |
| IN3 | D4 (GPIO2) |
| IN4 | D3 (GPIO0) |

## Source Code
See `code/wifi_talking_robot.ino`.

## Project Status
Source code uploaded. Hardware testing and calibration required.
