# IoT-Based Industrial Safety System

## Overview
This project is an **IoT-based Industrial Safety System** that monitors various environmental parameters such as temperature, pH, conductivity, and turbidity. The system uses an **ESP8266 WiFi module** to send real-time data to an online server for remote monitoring and control.

## Features
- **Real-time sensor monitoring** (Temperature, pH, Conductivity, Turbidity)
- **LCD Display** for local visualization of sensor readings
- **Wireless Data Upload** to an online server (`projectsfactoryserver.in`)
- **Remote Server Communication** to receive and process commands
- **Periodic Data Upload** after every 30 cycles

## Hardware Requirements
- **Arduino Uno / Mega**
- **ESP8266 WiFi Module**
- **DS18B20 Temperature Sensor**
- **pH Sensor**
- **Conductivity Sensor**
- **Turbidity Sensor**
- **16x2 LCD with I2C module**
- **Power Supply (5V, 3.3V)**
- **Jumper Wires and Breadboard**

## Software Requirements
- **Arduino IDE**
- **ESP8266 Library**
- **OneWire Library (for DS18B20)**
- **LiquidCrystal_I2C Library (for LCD)**

## Installation & Setup
1. Clone this repository:
   ```bash
   git clone https://github.com/kaustubh812/Industrial-Safety-System.git
   ```
2. Open the Arduino IDE and install the required libraries.
3. Connect the hardware components as per the circuit diagram.
4. Upload the `main.ino` file to the Arduino board.
5. Configure WiFi credentials in the code:
   ```cpp
   #define ssid "iotserver"
   #define pass "iotserver123"
   ```
6. Open the Serial Monitor to debug and check data transmission.

## Circuit Diagram
*(Add a schematic or Fritzing diagram here)*

## Working Principle
1. The system reads sensor values periodically.
2. The values are displayed on a **16x2 LCD**.
3. After **30 cycles**, data is sent to the **server** via ESP8266.
4. The system checks for commands from the **server** and executes them accordingly.

## Server Communication
- **Upload Data:** Sensor readings are uploaded to `projectsfactoryserver.in`.
- **Read Commands:** The system checks for commands from the server and executes the required actions.
- **Clear Server Data:** If needed, the system clears the server buffer.

## Future Improvements
- Add **MQTT support** for better cloud integration.
- Implement **data logging** for historical analysis.
- Introduce **mobile app support** for real-time monitoring.

## Contributing
Contributions are welcome! Feel free to fork the repo and submit a pull request.

## License
This project is licensed under the **MIT License**.

---
**Made with ❤️ for Industrial Safety Applications**

