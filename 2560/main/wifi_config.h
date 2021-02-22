#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "esp_system.h"
#include <EEPROM.h>
#include "pinout.h"



char web_compleat[] = "<!DOCTYPE html>\
    <html <head>\
    <meta name=\"viewport \" content=\"width=device-width, initial-scale=1\">\
    <style>\
        html {\
            font-family: Helvetica;\
            display: inline-block;\
            margin: 0px auto;\
            background-color: #ffffec;\
            text-align: center;\
            color: #052f0e;\
        }\
        h4 {\
            color: #005cfa;\
        }\
            input {\
        padding: 12px 20px;\
        margin: 8px 0;\
        box-sizing: border-box;\
    } \
    input[type=text] {\
        border: 2px solid rgb(70, 9, 9);\
        border-radius: 4px;\
    }\
    input[type=button], input[type=submit], input[type=reset]{\
        background-color: #4CAF50;\
        border: none;\
        color: rgb(255, 255, 255);\
        padding: 16px 32px;\
        text-decoration: none;\
        margin: 4px 2px;\
        cursor: pointer;\
        border: 2px solid rgb(70, 9, 9);\
        border-radius: 8px;\
    }\
    </style>\
    </head>\
    <body>\
        <h1>6025 Controller</h1>\
        <img src=\"data:image/png;base64,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\">\
        <h3>___________________ </h3>\
        <span style=\"display:block; height: 40px; \"></span>\
            <h4> Insert your house Wifi Credentials </h4>\
        <form action=\"action_page.php\"> Wifi Name: <input type=\"text\" name=\"wifi_name\"><br>\
            Password: <input type=\"text\" name=\"wifi_pass\"><br>\
        <input type=\"submit\">\
        </form>\
            <h3>___________________ </h3>\
            <h3> Configuration web page</h3>\
            <h5> March - 2021</h5>\
    </body>\
    </html>";
WiFiServer server(80);
typedef struct
{
    char wifi_name[80];
    char wifi_pass[80];
} AP_data_user;

String header;
AP_data_user AP_data;
void get_url_info(char *data, uint16_t index);
bool get_credentials();
void auto_wifi_connect();

void get_url_info(char *data, uint16_t index)
{
    for (uint8_t i = 0; i < 30; i++)
    {
        //I save the info in the struct
        if (header.charAt(index + i) == '&' || header.charAt(index + i) == ' ')
            break;
        else
            data[i] = header.charAt(index + i);
        if (data[i] == '+')
            data[i] = ' ';
        LOGW(data[i]);
    }
}
bool get_credentials()
{
    WiFiClient client = server.available(); // listen for incoming clients

    if (client)
    {                                  // if you get a client,
        LOGLN("New Client."); // print a message out the serial port
        String currentLine = "";       // make a String to hold incoming data from the client
        while (client.connected())
        { // loop while the client's connected
            if (client.available())
            {                           // if there's bytes to read from the client,
                char c = client.read(); // read a byte, then
                header += c;
                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        LOGLN("________________________________");
                        LOGLN(header);
                        //GET /action_page.php?wifi_name=JoseLuis&wifi_pass=Todo+bien HTTP/1.1

                        if (header.indexOf("/action_page.php?wifi_name=") >= 0)
                        {
                            //GET /action_page.php?wifi_name=asd&wifi_pass=Fgh HTTP/1.1
                            LOGLN("__________START");
                            LOGLN(" ");
                            LOG("USER: ");
                            uint16_t index = header.indexOf("&wifi_name=") + 32;
                            get_url_info(AP_data.wifi_name, index);
                            LOGLN(" ");
                            LOG("PASS:");
                            index = header.indexOf("&wifi_pass=") + 11;
                            get_url_info(AP_data.wifi_pass, index);
                            LOGLN(" ");
                            LOGLN("__________END");
                            return true;
                        }
                        // the content of the HTTP response follows the header:
                        client.println(web_compleat);

                        // The HTTP response ends with another blank line:
                        client.println();
                        // break out of the while loop:
                        break;
                    }
                    else // if you got a newline, then clear currentLine:
                        currentLine = "";
                }
                else if (c != '\r') // if you got anything else but a carriage return character,
                    currentLine += c;
            }
        }
        header = "";
        // close the connection:
        client.stop();
        // LOGLN("Client Disconnected.");
    }
    return false;
}
void auto_wifi_connect()
{
    const char *ssid = "WIFI-6025";
    const char *password = "pass123";
    int attemps = 0;
    LOGLN("Configuring access point");

    //I alocate the eeprom memmory:
    EEPROMClass eeprom;
    eeprom.begin(100);

    if (digitalRead(BUTTON_RESET) == LOW)
    {
        LOGLN("MANUAL RESET");
        eeprom.writeString(0, "nop");
        eeprom.writeString(80, "nop");
        eeprom.commit();
        digitalWrite(LED, HIGH);
        delay(2000);
        digitalWrite(LED, LOW);
    }
    LOGLN("----Alocated on EEPROM:");
    String wifi_flash_memmory_user = eeprom.readString(0);
    String wifi_flash_memmory_pass = eeprom.readString(80);
    delay(100);
    LOGLN(wifi_flash_memmory_user);
    LOGLN(wifi_flash_memmory_pass);

    //I try to connect to wifi if not:
    bool valid_credentials = true;
    // WiFi.begin(a, b);
    WiFi.begin(wifi_flash_memmory_user.c_str(), wifi_flash_memmory_pass.c_str());
    delay(50);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        LOG(".");
        if (attemps++ > 30)
        {
            LOGLN("not valid credentials");
            valid_credentials = false;
            break;
        }
    }
    if (valid_credentials)
    {
        randomSeed(micros());
        LOGLN("");
        LOGLN("WiFi connected");
        LOGLN("IP address: ");
        LOGLN(WiFi.localIP());
    }
    else
    {
        LOGLN("Fail on connected with store flash data, genetate access point");
        WiFi.softAP(ssid, password);
        IPAddress myIP = WiFi.softAPIP();
        LOG("AP IP address: ");
        LOGLN(myIP);
        server.begin();
        uint32_t blink_interval = millis();
        bool blink_status = true;
        //todo: blink to better knowlwedge of waitting introduuice
        while (!get_credentials())
            if (millis() - blink_interval >= 500)
            {
                digitalWrite(LED_WIFI, blink_status);
                blink_status = !blink_status;
                blink_interval = millis();
            }
        LOGLN("i get the user:");
        for (int i = 0; i < sizeof(AP_data.wifi_name); i++)
            LOGW(AP_data.wifi_name[i]);
        LOGLN("");
        LOGLN("i get the pass:");
        for (int i = 0; i < sizeof(AP_data.wifi_pass); i++)
            LOGW(AP_data.wifi_pass[i]);
        LOGLN("");
        WiFi.softAPdisconnect(true);
        // We start by connecting to a WiFi network
        LOGLN();
        LOG("Connecting to ");
        LOGLN(AP_data.wifi_name);
        WiFi.begin(AP_data.wifi_name, AP_data.wifi_pass);
        attemps = 0;
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            LOG(".");
            if (attemps++ > 25)
                esp_restart();
        }
        //I save on the flash of the device:
        eeprom.writeString(0, AP_data.wifi_name);
        eeprom.writeString(80, AP_data.wifi_pass);
        eeprom.commit();

        LOGLN("");
        LOGLN("WiFi connected");
        LOGLN("IP address: ");
        LOGLN(WiFi.localIP());
        digitalWrite(LED_WIFI, HIGH);
    }
}
int getStrength(int points)
{
    long rssi = 0;
    long quality = 0;
    long averageRSSI = 0;

    for (int i = 0; i < points; i++)
    {
        rssi += WiFi.RSSI();
        delay(20);
    }

    averageRSSI = rssi / points;

    if (averageRSSI <= -100)
        quality = 0;
    else if (averageRSSI >= -50)
        quality = 100;
    else
        quality = 2 * (averageRSSI + 100);

    return quality;
}
