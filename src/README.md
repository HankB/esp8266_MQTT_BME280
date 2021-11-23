# mqtt_esp8266

ESP8266 example, Arduino and PlatformIO

## Credits

Code is originally copied from Nick O'Leary's repository for the pubsubclient and can be seen at https://github.com/knolleary/pubsubclient/tree/master/examples/mqtt_esp8266

## Motivation

Build something that does a bit more than blink an LED and builds and works correctly using both Arduino and PlatformIO tool chains.

## Requirments

1. Create `secrets.h` and in it define the items described in `mqtt_esp8266.ino`. This file is listed in `.gitignore` and is probably something yuou do not want to commit/push.
1. Run an MQTT server for testing. This is trivially easy on Debian Linux and is run on the same host used for development. (If you are using Mosquitto 2.0 or later you may need to configure it to accept anonymous connections.)
1. Install the Arduino toolchain and add the pubsubclient as instructed in `mqtt_esp8266.ino`.
1. Install Visual Studio Code and add the PlatformIO extension. Details to follow.

## Usage

Development has been performed on Debian Linux and using the `mosquitto` MQTT broker and client utilities.

### Arduino

1. Build and download the sketch using Arduino. Use the serial monitor for progress messages. On my host the ESP8266 (NodeMCU) comes up as `/dev/ttyUSB0`.
1. Interact with MQTT messages using `mosquitto_sub -v  -t outTopic` to receive messages and `mosquitto_pub -t inTopic -m "hello back"` to publish.
