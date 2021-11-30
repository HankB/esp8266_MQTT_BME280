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
* Publish BME280 readings
* Conditional serial I/O (working only with serial enabled)

## Errata

Removing all serial output causes the app to misbehave. I've spent over an hour trying to sort that and am setting it aside for the moment.
 
## Build reports

Build reports now in a [separate page](Build_Reports.md)
