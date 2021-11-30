# esp8266_MQTT_BME280

Use <https://github.com/HankB/mqtt_esp8266_PIO> as a starting point for a project to use the BME280 to report temperature and other conditions.

This repo uses the PlatformIO tool chain.

Hardware is `NodeMCU 1.0 (ESP-12E Module)`.

## Credits

Code to support MQTT is originally copied from Nick O'Leary's repository for the pubsubclient and can be seen at https://github.com/knolleary/pubsubclient/tree/master/examples/mqtt_esp8266. Code to read the BME280 os copied from an example at <https://platformio.org/lib/show/166/Adafruit%20BME280%20Library> and some settings from <https://github.com/optio50/ESP8266-NodeMCU-12E-with-BME280> (see <https://github.com/HankB/Arduino_BME280_NodeMCU_ESP-12E>.)

## Motivation

Need to monitor temperature and have BME280 sensors to do so. Trying as an alternate to the HTU21D now in use on other projects.

## Requirements

1. Create `secrets.h` and in it define the items described in `src/main.cpp`. This file is listed in `.gitignore` and is probably something you do not want to commit/push.
1. Run an MQTT server for testing. This is trivially easy on Debian Linux and is run on the same host used for development. (If you are using Mosquitto 2.0 or later you may need to configure it to accept anonymous connections.)
1. Select the correct board definition (`NodeMCU 1.0 (ESP-12E Module)` for my board.) May try an ESP-01 at some point. (That can support I2C on the two GPIO pins.)
1. Add the pubsubclient library produced by Nick O'Leary. <https://github.com/knolleary/pubsubclient> (QUICK ACCESS > PIO Home > Libraries and search "pubsubclient")

## Usage

Development has been performed on Debian Linux and using the `mosquitto` MQTT broker and client utilities. Development begins using the NodeMCU ESP-E12.

### PlatformIO

1. Download and build the project using VS Code/PlatformIO. 
1. Use `minicom --device /dev/ttyUSB0` to view progress message. On my host the ESP8266 (NodeMCU) comes up as `/dev/ttyUSB0`. You will need to exit `minicom` in order to download from PlatformIO.
1. Interact with MQTT messages using `mosquitto_sub -v -t outTopic` to receive messages and `mosquitto_pub -t inTopic -m "hello back"` to publish. 
1. Monitor activity from the viewpoint of the MQTT broker using `sudo tail -f /var/log/mosquitto/mosquitto.log`.

## Status

* Test imported (unchanged) project - works

## Build reports

### Code Usage

As reported by Platform IO.

|Stage|RAM|%|Flash|%|notes|
|---|---|---|---|---|---|
|MQTT|28620|34.9|279961|26.8||
|publish BME280|29620|36.2|295265|28.3||

### MQTT

```text
CONFIGURATION: https://docs.platformio.org/page/boards/espressif8266/nodemcuv2.html
PLATFORM: Espressif 8266 (3.2.0) > NodeMCU 1.0 (ESP-12E Module)
HARDWARE: ESP8266 80MHz, 80KB RAM, 4MB Flash
PACKAGES: 
 - framework-arduinoespressif8266 3.30002.0 (3.0.2) 
 - tool-esptool 1.413.0 (4.13) 
 - tool-esptoolpy 1.30000.201119 (3.0.0) 
 - toolchain-xtensa 2.100300.210717 (10.3.0)
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 36 compatible libraries
Scanning dependencies...
Dependency Graph
|-- <PubSubClient> 2.8.0
|-- <ESP8266WiFi> 1.0
Building in release mode
Retrieving maximum program size .pio/build/nodemcuv2/firmware.elf
Checking size .pio/build/nodemcuv2/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [===       ]  34.9% (used 28620 bytes from 81920 bytes)
Flash: [===       ]  26.8% (used 279961 bytes from 1044464 bytes)
```

### publish BME280

```text
CONFIGURATION: https://docs.platformio.org/page/boards/espressif8266/nodemcuv2.html
PLATFORM: Espressif 8266 (3.2.0) > NodeMCU 1.0 (ESP-12E Module)
HARDWARE: ESP8266 80MHz, 80KB RAM, 4MB Flash
PACKAGES: 
 - framework-arduinoespressif8266 3.30002.0 (3.0.2) 
 - tool-esptool 1.413.0 (4.13) 
 - tool-esptoolpy 1.30000.201119 (3.0.0) 
 - tool-mklittlefs 1.203.210628 (2.3) 
 - tool-mkspiffs 1.200.0 (2.0) 
 - toolchain-xtensa 2.100300.210717 (10.3.0)
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 39 compatible libraries
Scanning dependencies...
Dependency Graph
|-- <PubSubClient> 2.8.0
|-- <Adafruit Unified Sensor> 1.1.4
|-- <Adafruit BME280 Library> 2.2.1
|   |-- <Adafruit BusIO> 1.9.8
|   |   |-- <Wire> 1.0
|   |   |-- <SPI> 1.0
|   |-- <Wire> 1.0
|   |-- <SPI> 1.0
|   |-- <Adafruit Unified Sensor> 1.1.4
|-- <ESP8266WiFi> 1.0
|-- <Wire> 1.0
Building in release mode
Compiling .pio/build/nodemcuv2/src/main.cpp.o
... eliding compiler warnings
Linking .pio/build/nodemcuv2/firmware.elf
Retrieving maximum program size .pio/build/nodemcuv2/firmware.elf
Checking size .pio/build/nodemcuv2/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [====      ]  36.2% (used 29620 bytes from 81920 bytes)
Flash: [===       ]  28.3% (used 295265 bytes from 1044464 bytes)
```