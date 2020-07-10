
#!/usr/bin/python
import paho.mqtt.client as mqtt
# get the credentials of the devises
from not_show import TOPICS_TO_SUBSCRIBE, HOST_MQTT, GET_INFO_DEVISES, TOPICS_TO_PUBLISH
import sys
import os

# I get the parameters:
print('Number of arguments:', len(sys.argv), 'arguments.')
print('Argument List:', str(sys.argv))

business = ""  # The name of the enterprise to make the update
devise = ""  # The model, or ESP32 or ATMEGA
update_file_name = "" #The file direction of the update

def on_message(mqttc, obj, msg):
    pass
    # This is call when I receive a msg on a suscribe topic
    """
    print('Topic: ' + msg.topic)
    print('')
    print('Payload: ' + str(msg.payload))
    print('')
    print('')
    """
    # print(msg.topic + msg + ":" + str(msg.payload))
    # mqttc.publish(TOPICS_TO_PUBLISH["SETUP"], GET_INFO_DEVISES['all_params'], 0, False)


# Check if the update is possible:
if (len(sys.argv) != 4):
    print("Invalid number of parameters !!")
    sys.exit()
else:
    business = str(sys.argv[1]).upper()
    devise = str(sys.argv[2]).upper()
    update_file_name = str(sys.argv[3])
    print(update_file_name)
    #Check if it makes sense the words introduce:
    if (business == 'INFRIKO' and (devise == 'ESP32' or devise == 'ATMEGA')):
            print("Comienza el proceso de update...")
    else:
        print("Invalid parameters!!")
        sys.exit()
        
# First I open the file:
file = open(update_file_name, "r")
# I create the json
json_update = file.read()
# I close the file
file.close()
# Configure the mqtt client:
mqttc = mqtt.Client()
mqttc.on_message = on_message
# I connect to broker:
mqttc.connect(HOST_MQTT, 1883, 60)
# I publish the update:
mqttc.publish('test',json_update, 0, False)

"""
# Suscribe to all the devises topics:
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['STATUS'], 0)
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['DATAS'], 0)
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['HELLO'], 0)
mqttc.subscribe('topic', 0)
# mqttc.publish(TOPICS_TO_PUBLISH['SETUP'],
#               GET_INFO_DEVISES['all_params'], 0, False)
mqttc.loop_forever()
"""