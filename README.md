# Arduino IDE Firmware for Yosef's Thesis

This repository contains the firmware for the Arduino IDE that is used in Yosef's Thesis. The firmware is written in C++ and is used to control the hardware of the system. The firmware consists of two main parts: firmware for ESP32 and firmware for Arduino Mega. The ESP32 is used to convert data from MS5611 and DHT22 to Modbus TCP Protocol and the Arduino Mega is used to control the L298N H-Bridge Motor Driver using Modbus TCP Protocol.

## Hardware Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP32 Board](https://www.espressif.com/en/products/socs/esp32)
- [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3)
- MS5611 Temperature and Pressure (Barometer) Sensor
- DHT22 Temperature and Humidity Sensor
- L298N H-Bridge Motor Driver

## Software Dependencies

- [ESP8266 Modbus Library](https://github.com/emelianov/modbus-esp8266)
- [Arduino Modbus Library](https://github.com/arduino-libraries/ArduinoModbus)
- [Arduino Ethernet Library](https://www.arduino.cc/en/Reference/Ethernet)
- [MS5611 Library](https://github.com/abishur/ms5x)
- [Wire Library](https://www.arduino.cc/en/Reference/Wire)
- [DHT Library](https://www.arduino.cc/reference/en/libraries/dht-sensor-library/)
