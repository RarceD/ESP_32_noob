
#!/usr/bin/python
import paho.mqtt.client as mqtt
# get the credentials of the devises
from not_show import intro_json, UPDATE_TOPICS, MQTT_CREDENTIALS
import sys
import os
import json
import zlib
import hashlib
import multiprocessing
import time
import base64
import ssl
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
    business = str(sys.argv[1]).lower()
    devise = str(sys.argv[2]).lower()
    update_file_name = str(sys.argv[3])
    # print(update_file_name)
    # Check if it makes sense the words introduce:
    if (business == 'infrico' or business == 'solidy'):
            if (devise == 'esp32' or devise == 'atmega'):
                print("Comienza el proceso de update...")
            else:           
                print("Invalid parameters!!")
    else:
        print("Invalid parameters!!")
        sys.exit()

# First I open the file:
file = open(update_file_name, "rb")
update_bin = file.read()
# Obtein the md5 checksum:
md5_value = hashlib.md5(update_bin).hexdigest()
# I create the string file and compress to zlib:
update_zlib = zlib.compress(update_bin, level=9)
update_zlib_encoded = base64.b64encode(update_zlib)
# and close the file
file.close()


# and close the file

def received_message(mqttc, obj, msg):
    # I get the version of the firmware in order to increase when I finish the update
    intro_info = str(msg.payload)
    offset = intro_info.find('firmware') + len('firmware": "')
    version = ''
    for i in range(0, 8):
        version += intro_info[offset + i]
    version = int(version[5:])
    # Copy the current version and increase 1 time
    intro_json['firmware'] =intro_json['firmware'][:5] + str(version + 1)
    # Fill the json correctly:
    intro_json['md5'] = md5_value
    intro_json['model'] = devise
    topic_to_update = UPDATE_TOPICS['esp32_intro'].replace('x', business)
    json_msg = json.dumps(intro_json)
    mqttc.unsubscribe(topic_to_update, 0)
    # I publish the new version json and then the version 
    print('Increase the version')
    mqttc.publish(UPDATE_TOPICS['esp32_bin'].replace('x', business), update_zlib_encoded, 0, True)
    print('Publish the firmware in /bin ')
    mqttc.publish(topic_to_update, json_msg, 0, True)

# Configure the mqtt client:
mqttc = mqtt.Client()
mqttc.on_message = received_message
# I connect to broker and set all the permisions:
mqttc.tls_set('C:/Users/Asus/Desktop/ESP_32_noob/MQTT_auto_replay/ca.crt', tls_version=ssl.PROTOCOL_TLSv1_2)
mqttc.tls_insecure_set(True)
mqttc.username_pw_set(MQTT_CREDENTIALS['USER'],MQTT_CREDENTIALS['PASS'])
mqttc.connect(MQTT_CREDENTIALS['HOST'], 8883, 60)
mqttc.publish('Start', '{"Start_ALL":1}', 0, False)

# I generate the first update json:
mqttc.subscribe(UPDATE_TOPICS['esp32_intro'].replace('x', business), 0)
mqttc.loop_forever()
