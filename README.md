# ROLEX Robot

An autonomous multi-sensor robot designed for environmental monitoring, hazard detection, and blueprint-style map generation using Arduino and Raspberry Pi.

---

## Overview

ROLEX is a differential-drive robot that integrates multiple sensors to perceive its surroundings, detect hazards, and navigate autonomously. The system logs real-time sensor data and reconstructs a visual map of the explored environment.

---

## Features

- Multi-sensor integration:
  - Temperature (LM35)
  - Gas (MQ2)
  - Ultrasonic distance sensor
  - PIR motion sensors
  - IR cliff detection
  - Color-based entry detection

- Autonomous behavior:
  - Obstacle avoidance
  - Hazard detection (gas and temperature)
  - Return-to-entry mechanism

- Data acquisition:
  - Real-time sensor data transmission via serial communication
  - Structured logging into CSV format

- Visualization:
  - Blueprint-style path reconstruction
  - Event marking (hazards, motion, cliff detection)

---

## System Architecture

Arduino handles sensor interfacing and control logic. Data is transmitted via serial communication to a Raspberry Pi, which logs the data and generates a map.
