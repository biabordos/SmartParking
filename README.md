## 🚀 Live simulation of Smart Parking Management System
An automated parking solution based on the Arduino Uno platform, designed to manage vehicle access and real-time occupancy monitoring.

Project can be visualized and tested in browser here:
[Link Smart Parking](https://www.tinkercad.com/things/74DYC3nty3U-smartparking/editel?returnTo=%2Fthings%2F74DYC3nty3U-smartparking)

## 1. Overview
The system provides an automated gate control mechanism using ultrasonic distance sensing. It is capable of tracking vehicle entry and exit, maintaining an internal counter of available spaces, and generating secure access credentials for users.

## 2. Hardware Architecture
The system integrates several hardware components to achieve full automation:

* **Microcontroller:** Arduino Uno R3.
* **Sensing Unit:** 2x HC-SR04 Ultrasonic Sensors (positioned at entry and exit points).
* **Actuator:** SG90 Servo Motor (controlling the physical barrier).
* **User Interface:** 16x2 Character LCD (parallel interface).
* **Calibration:** 10k Potentiometer for LCD contrast adjustment.

## 3. Operational Logic
The system follows a continuous monitoring loop to process distance data from the sensors:

1.  **Distance Calculation:** The sensors utilize ultrasonic pulses to measure the distance of approaching objects. A vehicle is recognized when a distance of less than 20 cm is detected.
2.  **Entrance Protocol:** If a vehicle is detected and the occupancy counter is greater than zero, the system:
    * Decrements the available space counter.
    * Generates a random 4-digit security PIN.
    * Initiates a 90-degree servo rotation to open the barrier.
    * Maintains the open state for 3 seconds before closing.
3.  **Exit Protocol:** When the exit sensor detects a vehicle:
    * Increments the available space counter (up to the maximum capacity of 5).
    * Activates the servo motor for vehicle egress.
4.  **Display Logic:** The LCD provides real-time updates on the current status, including available spots and user instructions.
