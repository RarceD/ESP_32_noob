#ifndef MQTT_INTERACTIONS
#define MQTT_INTERACTIONS

#include "secrets.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);
void reconnect();
void init_mqtt();
void callback(char *topic, byte *payload, unsigned int length);

void callback(char *topic, byte *payload, unsigned int length)
{
    //Create the json buffer:
    DynamicJsonBuffer jsonBuffer(8084);
    //Parse the huge topic
    JsonObject &parsed = jsonBuffer.parseObject(payload);
    LOGLN(esp_get_free_heap_size());
    LOGLN(esp_get_minimum_free_heap_size());
    int identifier = parsed["id"].as<int>(); // This is for the sendding function app
    // Obtein the topic
    String sTopic = String(topic);
}
void init_mqtt()
{
    client.setServer(mqtt_server, MQTT_PORT);
    client.setCallback(callback);
    reconnect();
}

void reconnect()
{
    int restart = 0;
    while (!client.connected())
    {
        LOG("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "Rarced-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD))
        {
            LOGLN("connected");
            String topic = String(sys.uuid_) + "/+/app";
            client.subscribe(topic.c_str());
            LOGLN(topic);
            digitalWrite(LED_WIFI, HIGH);
        }
        else
        {
            digitalWrite(LED_WIFI, LOW);
            LOG("failed, rc=");
            LOG(client.state());
            LOGLN(" try again in 5 seconds");
            if (restart > 10)
                esp_restart();
            else
                restart++;
            delay(3000);
        }
    }
}

#endif
