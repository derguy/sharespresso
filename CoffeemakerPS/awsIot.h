#ifndef AWSIOT_H_
#define AWSIOT_H_

#include <Arduino.h>
#include <Stream.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//AWS
#include "sha256.h"
#include "Utils.h"

//WEBSockets
#include <Hash.h>
#include <WebSocketsClient.h>

//MQTT PAHO
#include <SPI.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>

//AWS MQTT Websocket
#include "Client.h"
#include "AWSWebSocketClient.h"
#include "CircularByteBuffer.h"
#include <ArduinoJson.h>

#include "settings.h"

const int maxMQTTpackageSize = 512;
const int maxMQTTMessageHandlers = 2;

class AwsIotClient {
  private:
    AWSWebSocketClient awsWSclient;
    IPStack ipstack;
    MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers> *client = NULL;
    void publish_to_topic(const char* topic, const String& message);

    //# of connections
    long connection = 0;
    //count messages arrived
    int arrivedcount = 0;

  public:
    AwsIotClient();
    void initAwsClient();
    void loopAwsClient();
    char* generateClientID ();
    bool connect ();
    void subscribe ();
    void sendmessage(const String cardId, const String product, const int price); 
};
#endif