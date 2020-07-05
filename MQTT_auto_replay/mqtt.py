
import paho.mqtt.client as mqtt
from not_show import *


def on_connect(mqttc, obj, flags, rc):
    pass
    # print("rc: " + str(rc))


def on_message(mqttc, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    if (msg.topic == "canbricks/infrico/alive"):
        print("CONSEGUIDOOOO")
        # mqttc.publish(msg.topic, "hola", 0, False)
        # msg.topic = "random"


def on_publish(mqttc, obj, mid):
    print("mid: " + str(mid))


def on_subscribe(mqttc, obj, mid, granted_qos):
    pass
    # print("Subscribed: " + str(mid) + " " + str(granted_qos))



# If you want to use a specific client id, use
# mqttc = mqtt.Client("client-id")
# but note that the client id must be unique on the broker. Leaving the client
# id parameter empty will generate a random id for you.
mqttc = mqtt.Client()
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_publish = on_publish
mqttc.on_subscribe = on_subscribe
# Uncomment to enable debug messages
# mqttc.on_log = on_log
mqttc.connect(HOST_MQTT, 1883, 60)
mqttc.subscribe("#", 0)

mqttc.loop_forever()
