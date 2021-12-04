/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "secrets.h"
/* secrets.h should define the following as appropriate for your network.
const char* ssid = "...";
const char* password = "...";
const char* mqtt_server = "host.domain"; // "<host>.localddomain" works for me.
*/

#define serial_IO 1     // control compilation of serial I/O
// NOTE: currently turning off Serial I/O rsults in an app that does not work.

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
Adafruit_BME280 bme; // I2C
time_t      world_time;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
#if serial_IO
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
#if serial_IO
    delay(500);
    Serial.print(".");
#else
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on 
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED off 
    delay(400);
#endif
  }

  randomSeed(micros());

#if serial_IO
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}

void setup_BME280(void) {
  // configure BME280/I2C
  Wire.begin(D3, D4); // Make sure you have D3 & D4 hooked up to the BME280
  Wire.setClock(100000);
  unsigned status = bme.begin(0x76);
  if (!status) {
#if serial_IO
      Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
      Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
      while (1) delay(10);
#else
      while(1) {
        digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on 
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED off 
        delay(90);
      }
#endif
  }
}

// Parse timestamp from inbound message
void callback(char* topic, byte* payload, unsigned int length) {
#if serial_IO
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif

  char buff[100];
  length = (length>99)?99:length;
  for (unsigned int i = 0; i < length; i++)
    buff[i] = (char)payload[i];
  buff[length] = '\0';

  world_time = atol(buff);
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on
  else
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
#if serial_IO
    Serial.print("Attempting MQTT connection...");
#endif
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
#if serial_IO
      Serial.println("connected");
#endif
      // Once connected, publish an announcement...
      client.publish("outTopic", "PIO says hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
#if serial_IO
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
#endif
      // Wait 5 seconds before retrying
      digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on 
      delay(20);
      digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED off 
      delay(4980);
    }
  }
}

#if serial_IO
void printValues(void) {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}
#endif

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
#if serial_IO
  Serial.begin(115200);
  while(!Serial);    // time to get serial running
#endif
  setup_wifi();
  setup_BME280();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    snprintf (msg, MSG_BUFFER_SIZE, "t:%lld, temp:%.2f, press:%.0f, humid:%.1f", 
      world_time, bme.readTemperature()/5*9+32.0,
      bme.readPressure()/100, bme.readHumidity());
    client.publish("outTopic", msg);
#if serial_IO
    Serial.print("Publish message: ");
    Serial.println(msg);
    printValues();
#endif
  }
}
