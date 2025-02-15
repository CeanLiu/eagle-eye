# ESP32-CAM Web-Based Surveillance System

## Overview
The **ESP32-CAM Web-Based Surveillance System** is an advanced, low-cost surveillance solution that integrates IoT technology with cloud storage and a web interface. This system is designed to provide real-time monitoring, motion detection, and automated video recording capabilities, leveraging the ESP32-CAM module and modern web technologies.

## Features
- **ESP32-CAM with FreeRTOS:** Efficiently manages tasks for real-time video processing and sensor input.
- **Motion Detection with PIR Sensors:** Triggers automatic video recording upon detecting movement.
- **Cloud Integration:** Securely uploads recorded footage to Google Drive via a Node.js/Express backend.
- **Live Streaming:** Provides real-time video feed accessible through a responsive React.js web interface.
- **Interactive Controls:** Users can access and manage recordings through an intuitive front-end.

## Technology Stack
- **Embedded System:** ESP32-CAM programmed using ESP-IDF, C/C++, and FreeRTOS.
- **Sensors:** Two PIR motion sensors for movement detection.
- **Backend:** Node.js with Express.js for handling video uploads and API communication.
- **Cloud Storage:** Google Drive integration for secure storage of recorded footage.
- **Frontend:** React.js for a dynamic and responsive user experience.

## System Architecture
![System Architecture Diagram](path/to/system_architecture_image.png)  
*Illustration of ESP32-CAM communication with sensors, backend, and cloud storage.*

## Installation & Setup
### Hardware Requirements
- ESP32-CAM Module
- 2x PIR Motion Sensors
- MicroSD Card (for local storage)
- Power Supply (5V)





