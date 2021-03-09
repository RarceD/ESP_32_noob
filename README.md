## 1.1. Bluethoot tecnology
Learn everything related with bluethoot tecnology and ESP32 diferent modes.


### 1.1.1. BLE vs Bluetooth 3.0 basics

Bluethoot: 

* Short Range
* Low power (meh, I have tested and 120mA...)
* Low data rate
* f = ISM 2.400GHz and 79 channels                                  

| Clasic Bluetooth       |BLE                    |
|  :---:                 | :---:                 |
|High datarate           |Low datarate           |
|Long range              |Small range            |
|High power consumption  |Low power consumption  |
|Audio Steamming         | -                     |
|Class 4 - 0.5mW         | 10 mW max             |
|Class 1 - 100mW         |  -                    |

### 1.1.2. Topology:

Master/Slave:

* up to 7 slaves in a "piconet"
* "parkel" slaves -> They are sleep but in the net
* FHSS: Frecuency Hoppping Spread Spectum, it hops in frecuencies in order to not interfeer with other devise near it.
* TDM: Time domain multiplexing, the master devise set time periods of 625uS to let the others on the network to comunicate with them. Every time happends the fecuency change. The connection between elements can be SCO (Synchronous Connection Oriented) or ACL (Asynchronous Connection-Less).

### 1.1.3. Data format:

This always happend in 625uS 
Synchronization is from the master's ID

| Access Code |Header |Payload|
|  :---: | :---: |:---: |
| 72 bits |54 bits |0-2745 bits|

* Access code: 

| Preamble |Synchronization |Trailer|
|  :---: | :---: |:---: |
| 4 bits |64 bits |4 bits|

* Header:

| AM_ADDR |Type |Flow     |ARQN   |SEQN  |HEC|
|  :---: | :---: |  :---: | :---: |:---: |:---: |
| 3 bits |4 bits |1 bits|1 bits|1 bits|8 bits|

 - AM_ADDR: Active member address, one master 7 slaves
 - Type: 12 packets for SCO and ACL
 - HEC: Header Error Check like CRC

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
| Lotgic | Link |Control |Adaption |Protocol|

#### Controller Stack:

Chil level, it happends on hardware.
| HCI (Host control Interface) AT commands |
|  :---: |
| Link Manager Protocol |
|  BasebandX/Link Controller |
| Radio |

### 1.2. GAP

generic access profile 
Makes your device visible to the outside world, is the protocol for get connected with others blue.


### 1.3. GATT
GATT is an acronym for the Generic Attribute Profile , and it defines the way that two Bluetooth Low Energy devices transfer data back and forth using concepts called Services and Characteristics. It makes use of a generic data protocol called the Attribute Protocol (ATT), which is used to store Services, Characteristics and related data in a simple lookup table using 16-bit IDs for each entry in the table.

* connections are exclusive
* BLE peripheral can only be connected to one central device at a time

#### 1.3.1 Profiles
Are a pre-defined collection of Services
#### 1.3.2 Services
A service can have one or more characteristics, and each service distinguishes itself from other servicesby means of a unique numeric ID called a UUID, which can be either 16-bit (for officially adopted BLEServices) 
#### 1.3.3 Characteristics
The lowest level concept in GATT transactions is the Characteristic, which encapsulates a single data point (though it may contain an array of related data. They are also used to send data back to the BLE peripheral, since you are also able to write to characteristic. 

