# Build Reports

Track memory usage as libraries and code are added.

## Code Usage

As reported by Platform IO.

|Stage|RAM|%|Flash|%|notes|
|---|---|---|---|---|---|
|MQTT|28620|34.9|279961|26.8||
|Publish BME280|29620|36.2|295265|28.3||
|No Serial|28988|35.4|284565|27.2|doesn't work|

## MQTT

Code/libraries to publish simple MQTT message.

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

## Publish BME280

Add code to read BME280 and publish results to MQTT

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

## No Serial

Make serial output conditional (and turn it off)

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
Linking .pio/build/nodemcuv2/firmware.elf
Retrieving maximum program size .pio/build/nodemcuv2/firmware.elf
Checking size .pio/build/nodemcuv2/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [====      ]  35.4% (used 28988 bytes from 81920 bytes)
Flash: [===       ]  27.2% (used 284565 bytes from 1044464 bytes)
```