
import paho.mqtt.client as mqtt
from not_show import * ##get the credentials of the devises


def on_connect(mqttc, obj, flags, rc):
    pass
    # print("rc: " + str(rc))


def on_message(mqttc, obj, msg):
    # print(msg.topic)
    print(msg.topic + msg + ":" + str(msg.payload))
    # mqttc.publish(TOPICS_TO_PUBLISH["SETUP"], GET_INFO_DEVISES['all_params'], 0, False)


def on_publish(mqttc, obj, mid):
    print("mid: " + str(mid))


def on_subscribe(mqttc, obj, mid, granted_qos):
    pass
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

mqttc = mqtt.Client()
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_publish = on_publish
mqttc.on_subscribe = on_subscribe
# I connect to broker:
mqttc.connect(HOST_MQTT, 1883, 60)
#Suscribe to all the devises topics:
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['STATUS'], 0)
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['DATAS'], 0)
mqttc.subscribe('a', 0)
mqttc.publish(TOPICS_TO_PUBLISH["SETUP"], GET_INFO_DEVISES['all_params'], 0, False)

mqttc.loop_forever()
