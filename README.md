# SmartHelmetForMineWorkers

This project aims to create a smart helmet for coal mine workers to monitor environmental conditions (temperature and humidity) and the wearer's heart rate. It includes an alert system that triggers when certain conditions are met, such as high temperature or humidity, or a low heart rate.

# Components Used
1. DHT22 sensor for temperature and humidity
2. Pulse sensor for heart rate monitoring
3. ESP8266 for WiFi connectivity
4. ThingSpeak for data logging
5. Buzzers for alerts
# Installation and Setup
1. Connect the DHT22 sensor to the DHTPIN (pin 4) and define DHTTYPE as DHT22 in the code.
2. Connect the pulse sensor to the A0 pin.
3. Set up a WiFi network (replace ssid and password with your network credentials).
4. Set up a ThingSpeak account and obtain your Channel Number and Write API Key.
5. Upload the code to your ESP8266 board.
# Usage
1. The helmet will continuously monitor temperature, humidity, and heart rate.
2. If the temperature exceeds 50°C, humidity exceeds 100%, or the heart rate drops below 40 bpm, the buzzer will alert the wearer.
3. Data is sent to ThingSpeak for logging and monitoring.
