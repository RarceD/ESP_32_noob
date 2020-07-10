
#!/usr/bin/python
import paho.mqtt.client as mqtt
# get the credentials of the devises
from not_show import intro_json, UPDATE_TOPICS, TOPICS_TO_SUBSCRIBE, HOST_MQTT, GET_INFO_DEVISES, TOPICS_TO_PUBLISH
import sys
import os
import json
import zlib
import hashlib

"""
For converting to windows:
    pip install pyinstaller
Go to your program’s directory and run:
    pyinstaller yourprogram.py
"""

# The parameters introduce by the user:
business = ""  # The name of the enterprise to make the update
devise = ""  # The model, or ESP32 or ATMEGA
update_file_name = ""  # The file direction of the update

# Check if the update is possible:
if (len(sys.argv) != 4):
    print("Invalid number of parameters !!")
    sys.exit()
else:
    business = str(sys.argv[1]).upper()
    devise = str(sys.argv[2]).upper()
    update_file_name = str(sys.argv[3])
    # print(update_file_name)
    # Check if it makes sense the words introduce:
    if (business == 'INFRIKO' and (devise == 'ESP32' or devise == 'ATMEGA')):
        print("Comienza el proceso de update...")
    else:
        print("Invalid parameters!!")
        sys.exit()

# First I open the file:
file = open(update_file_name, "rb")
update_bin = file.read()
# I create the string file and compress to zlib:
update_zlib = zlib.compress(update_bin, level=-1)
#Obtein the md5 checksum:
md5_value = hashlib.md5(update_bin).hexdigest()
# and close the file
file.close()


# Configure the mqtt client:
mqttc = mqtt.Client()
# I connect to broker:
mqttc.connect(HOST_MQTT, 1883, 60)
# I generate the first update json:

intro_json['md5'] = md5_value
intro_json['model'] = devise
json_msg = json.dumps(intro_json)
print(json_msg)
mqttc.publish(UPDATE_TOPICS['esp32_intro'], json_msg, 0, True)
"""
# I publish the update:


# Suscribe to all the devises topics:
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['STATUS'], 0)
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['DATAS'], 0)
mqttc.subscribe(TOPICS_TO_SUBSCRIBE['HELLO'], 0)
mqttc.subscribe('topic', 0)
# mqttc.publish(TOPICS_TO_PUBLISH['SETUP'],
#               GET_INFO_DEVISES['all_params'], 0, False)
mqttc.loop_forever()
"""
