# mqtt_esp8266_PIO

ESP8266 example, Arduino and PlatformIO

This repo uses the PlatformIO tool chain.

The project began with Arduino as the lowest friction option and [that project](https://github.com/HankB/mqtt_esp8266) was then imported using the PlatformIO Arduino import functionality. (QUICK ACCESS > PIO Home > Open and select "Import Arduino Project") The resulting project name was `211123-120815-nodemcuv2` which seemed a little awkward so the project has been renamed `mqtt_esp8266_PIO`. 

PlatformIO will import the project to a different location. It may not be possible to build the project using both tool chains from the same repo.

## Credits

Code is originally copied from Nick O'Leary's repository for the pubsubclient and can be seen at https://github.com/knolleary/pubsubclient/tree/master/examples/mqtt_esp8266

## Motivation

Build something that does a bit more than blink an LED and builds and works correctly using both Arduino and PlatformIO tool chains. (There was a problem with an earlier project that seems to be resolved by choosing the correct board definition.)

## Requirments

1. Create `secrets.h` and in it define the items described in `mqtt_esp8266.ino`. This file is listed in `.gitignore` and is probably something yuou do not want to commit/push.
1. Run an MQTT server for testing. This is trivially easy on Debian Linux and is run on the same host used for development. (If you are using Mosquitto 2.0 or later you may need to configure it to accept anonymous connections.)
1. Install Visual Studio Code and add the PlatformIO extension.
1. Import the existing Arduino project (This was my process, not needed if you clone this repo)
1. Select the correct board definition (`Espressif ESP8266 ESP-12E` for my board.)
1. Add the pubsubclient library produced by Nick O'Leary. <https://github.com/knolleary/pubsubclient> (QUICK ACCESS > PIO Home > Libraries and search "pubsubclient")

## Usage

Development has been performed on Debian Linux and using the `mosquitto` MQTT broker and client utilities.

### PlatformIO

1. Download and build the project using VS Code/PlatformIO. 
1. Use `minicom --device /dev/ttyUSB0` to view progress message. On my host the ESP8266 (NodeMCU) comes up as `/dev/ttyUSB0`. You will need to exit `minicom` in order to download from PlatformIO.
1. Interact with MQTT messages using `mosquitto_sub -v -t outTopic` to receive messages and `mosquitto_pub -t inTopic -m "hello back"` to publish. 
1. Monitor activity from the viewpoint of the MQTT broker using `sudo tail -f /var/log/mosquitto/mosquitto.log`.

## Status

Not fully functional.

* Attach to AP works (Using WPA2.)
* Connection to broker works.
* Publishing a message works.
* Subscribing to a topic does not work.
* Connection to broker drops with

```text
1638200439: Client ESP8266Client-c67c has exceeded timeout, disconnecting.
```

Same code works when built with Arduino platform.
