# ESP_32_noob
ESP_32_noob learning, I have a esp32 wroom 32 and I'm using esp idf api for programming the chip.

## 1.1. Bluethoot tecnology

First of all I want to learn everything related with bluethoot tecnology and ESP32 diferent modes.

### 1.1.1. BLE vs Bluetooth 3.0

Bluethoot: 

* Short Range
* Low power 
* Low data rate

| Clasic Bluetooth       |BLE                    |
|  :---:                 | :---:                 |
|High datarate           |Low datarate           |
|Long range              |Small range            |
|High power consumption  |Low power consumption  |
|Audio Steamming         | -                     |
|Class 4 - 0.5mW         | 10 mW max             |
|Class 1 - 100mW         |  -                    |

f = ISM 2.400GHz and 79 channels                                  |

### 1.1.2. Topology:

Master/Slave - up to 7 slaves in a "piconet"

             - "parkel" slaves -> They are sleep but in the net

* FHSS: Frecuency Hoppping Spread Spectum, it hops in frecuencies in order to not interfeer with other devise near it.
* TDM: Time domain multiplexing, the master devise set time periods of 625uS to let the others on the network to comunicate with them. Every time happends the fecuency change. The connection between elements can be SCO (Synchronous Connection Oriented) or ACL (Asynchronous Connection-Less).

### 1.1.3. Data format:

| Access Code |Header |Payload|
|  :---: | :---: |:---: |
| 72 bits |54 bits |0-2745 bits|
This always happend in 625uS 

* Access code: 

| Preamble |Synchronization |Trailer|
|  :---: | :---: |:---: |
| 4 bits |64 bits |4 bits|
Synchronization is from the master's ID

* Header:

| AM_ADDR |Type |Flow     |ARQN   |SEQN  |HEC|
|  :---: | :---: |  :---: | :---: |:---: |:---: |
| 3 bits |4 bits |1 bits|1 bits|1 bits|8 bits|
AM_ADDR: Active member address, one master 7 slaves
Type: 12 packets for SCO and ACL
HEC: Header Error Check like CRC

* Payload (Data):

| DATA |
|  :---: |  

### 1.1.4. Profiles:

* They define the attributes, services or formats -> How to talk to the devise.
* There are dozen of profiles.
* SPP (Serial Port Protocol): Es one of the profiles more used.
* They are in the application layer and the fix the bottom protocols.

#### Host Stack:

It mostly happens on top of them.
| -      |-      |APPLICATION|    -  |     -|
|  :---: | :---: |  :---:    | :---: |:---: |
| TCS    |OBEX   |-          |WAP    |   SDP|
| -      |-      |RF COMM    |      -|-     |
| Lotgic Link Control + Adaption Protocol|

#### Controller Stack:

Chil level, it happends on hardware.
| HCI (Host control Interface) AT commands |
|  :---: |
| Link Manager Protocol |
|  BasebandX/Link Controller |
| Radio |
