#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "pinout.h"

#define FUKING_SLOW_TIME_PG 400
extern Entity sys;
extern uint8_t reset_unit[];

void pg_serial_date(int day, int month, int year);
void pg_listen();
void pg_time_check(int *hour, int *minute, int *weekday);

int calcrc(char ptr[], int length);
void pg_serial_action_valve(bool state, uint8_t valve, uint8_t time_hours, uint8_t time_minutes);
void action_prog_pg(uint8_t state, char program);
void change_time_pg(uint8_t week, uint8_t hours, uint8_t minutes, uint8_t seconds); //, uint8_t *day, uint8_t *hours, uint8_t *minutes)
void write_start_stop_pg(bool from, String time, uint8_t dir);
void write_percentage_pg(uint16_t position, uint16_t percentage);
uint8_t time_to_pg_format(uint8_t hours, uint8_t minutes);
void change_week_pg(char *date, uint8_t lenght, uint8_t program);
void pg_serial_fertirrigation(uint8_t valve_number, uint8_t wait_h, uint8_t wait_m, uint8_t water_h, uint8_t water_m);
void pg_serial_activate_fertirrigation(bool active);
void pg_serial_restart();
void web_to_pg_pump_associations(char pump_associations[]);
void shift_pumps(int valve_int, int pump);
void write_master_pump_association(char pump[], uint8_t len);
void pg_irrig_day(uint8_t *watering_days, uint8_t number_watering_days);

#define MAX_JSON_SIZE 512
bool send_stop_program;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

uint16_t pg_reag_to_web(uint16_t pg_time); //It return the time ok in minutes to the web
void json_program_starts(uint8_t program);

void reconnect();
void send_web(char *topic, unsigned int length, int id);
void json_program_starts(uint8_t program);
void json_program_valves(uint8_t program);
void json_clear_starts(uint8_t program);
void json_query(const char id[], char status[]);
void json_program_action(bool open, char program);
void json_valve_action(bool open, uint8_t valve, uint8_t hours, uint8_t minutes);
void json_week_days(uint8_t program, uint8_t week_day);
uint16_t pg_reag_to_web(uint16_t pg_time);
void init_mqtt();
void callback(char *topic, byte *payload, unsigned int length);

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
void send_web(char *topic, unsigned int length, int id)
{
    String ack_topic = String(topic);
    String identifier = String(id);
    char json[40];
    DynamicJsonBuffer jsonBuffer(27);
    JsonObject &root = jsonBuffer.createObject();
    root.set("id", id);
    root.set("success", "true");
    root.printTo(json);
    client.publish((String(sys.uuid_) + ack_topic).c_str(), (const uint8_t *)json, strlen(json), false);
}
void json_program_starts(uint8_t program)
{
    char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    //Generate the structure of the program via json
    DynamicJsonBuffer jsonBuffer(128);
    JsonObject &root = jsonBuffer.createObject();
    uint8_t index_program = program; //I generate the json only for the program request
    root["prog"] = String(program_letters[index_program]);
    JsonArray &starts = root.createNestedArray("starts");
    //Generate all the starts
    for (uint8_t index_time = 0; index_time < 6; index_time++)
        if (prog[index_program].start[index_time][0] != 255)
        {
            String minutes, hours;
            if (prog[index_program].start[index_time][0] < 10)
                hours = '0' + String(prog[index_program].start[index_time][0]);
            else
                hours = String(prog[index_program].start[index_time][0]);
            if (prog[index_program].start[index_time][1] < 10)
                minutes = '0' + String(prog[index_program].start[index_time][1]);
            else
                minutes = String(prog[index_program].start[index_time][1]);
            starts.add(hours + ":" + minutes);
        }
    int water = (int)(prog[index_program].waterPercent);
    if (water < 0)
        water = 100;
    root["water"] = water;
    char json[150];
    root.printTo(json);
    client.publish((String(sys.uuid_) + "/program").c_str(), (const uint8_t *)json, strlen(json), false);
}
void json_program_valves(uint8_t program)
{
    DynamicJsonBuffer jsonBuffer(200);
    JsonObject &root = jsonBuffer.createObject();
    char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    //Generate the structure of the program via json
    root["prog"] = String(program_letters[program]);
    JsonArray &valves = root.createNestedArray("valves");
    for (uint8_t index_valves = 0; index_valves < 14; index_valves++)
    {
        LOGLN(prog[program].irrigTime[index_valves]);
        if (prog[program].irrigTime[index_valves] <= 200)
        {
            JsonObject &irrig = root.createNestedObject("");
            LOGLN(prog[program].irrigTime[index_valves]);
            irrig["v"] = index_valves + 1;
            int time_compleat = pg_reag_to_web((uint16_t)prog[program].irrigTime[index_valves]);
            uint16_t time_in_format_h;
            uint16_t time_in_format_m;
            if (time_compleat >= 60)
            {
                time_in_format_h = time_compleat / 60;
                time_in_format_m = time_compleat % 60;
                String h = String(time_in_format_h);
                String m = String(time_in_format_m);
                if (h.length() == 1)
                    h = '0' + h;
                if (m.length() == 1)
                    m = '0' + m;
                irrig["time"] = h + ":" + m;
            }
            else
            {
                String x = String(time_compleat);
                if (x.length() == 1)
                    x = '0' + x;
                irrig["time"] = "00:" + x;
            }
            valves.add(irrig);
        }
    }
    char json[300];
    root.printTo(json);
    client.publish((String(sys.uuid_) + "/program").c_str(), (const uint8_t *)json, strlen(json), false);
}
void json_clear_starts(uint8_t program)
{
    //I clear the starts info
    char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    DynamicJsonBuffer jsonBuffer(43);
    JsonObject &root = jsonBuffer.createObject();
    root["prog"] = String(program_letters[program]);
    JsonArray &starts = root.createNestedArray("starts");
    char json[43];
    root.printTo(json);
    client.publish((String(sys.uuid_) + "/program").c_str(), (const uint8_t *)json, strlen(json), false);
}
void json_query(const char id[], char status[])
{
    DynamicJsonBuffer jsonBuffer(344);
    JsonObject &root = jsonBuffer.createObject();
    root["id"] = String(id);
    root["status"] = String(status);
    root["connection"] = getStrength(5);
    int hour = 0;
    int weekday = 0;
    int minute = 0;
    pg_time_check(&hour, &minute, &weekday);
    String hour_query, min_query;
    if (hour < 10)
        hour_query = "0" + String(hour, DEC);
    else
        hour_query = String(hour, DEC);

    if (minute < 10)
        min_query = "0" + String(minute, DEC);
    else
        min_query = String(minute, DEC);
    root["date"] = "01/01/2021 " + hour_query + ":" + min_query;
    //I send the time to the web:
    //I check if there is any program active and I send to the web:
    JsonArray &active_json = root.createNestedArray("prog_active");
    char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    for (uint8_t prog = 0; prog < 6; prog++)
        if (active.programs[prog])
            active_json.add(String(program_letters[prog]));
    //I generate the main json frame
    char json[350];
    root.printTo(json);
    client.publish((String(sys.uuid_) + "/query").c_str(), (const uint8_t *)json, strlen(json), false);
    // root.prettyPrintTo(Serial);
}
void json_program_action(bool open, char program)
{
    //Publish in /manprog topic and send to the app whats happening
    DynamicJsonBuffer jsonBuffer(100);
    JsonObject &root = jsonBuffer.createObject();
    root["prog"] = String(program);
    if (open)
        root["action"] = 1;
    else
        root["action"] = 0;
    char json[200];
    root.printTo(json);
    // root.prettyPrintTo(Serial);
    client.publish((String(sys.uuid_) + "/manprog").c_str(), (const uint8_t *)json, strlen(json), false);
}
void json_valve_action(bool open, uint8_t valve, uint8_t hours, uint8_t minutes)
{
    DynamicJsonBuffer jsonBuffer(100);
    JsonObject &root = jsonBuffer.createObject();
    JsonObject &oasis = root.createNestedObject("valves");
    JsonObject &info = oasis.createNestedObject("");
    info["v"] = valve;
    if (open)
    {
        info["action"] = 1;
        String str_hours = String(hours);
        if (str_hours.length() == 1)
            str_hours = '0' + str_hours;
        String str_minutes = String(minutes);
        if (str_minutes.length() == 1)
            str_minutes = '0' + str_minutes;
        info["time"] = str_hours + ":" + str_minutes;
    }
    else
        info["action"] = 0;
    char json[200];
    root.printTo(json);
    // root.prettyPrintTo(Serial);
    client.publish((String(sys.uuid_) + "/manvalve").c_str(), (const uint8_t *)json, strlen(json), false);
}
void json_week_days(uint8_t program, uint8_t week_day)
{
    char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    String str_week_day;
    uint8_t compare_operation = 1;
    for (int i = 1; i <= 7; i++)
    {
        if (week_day & compare_operation)
        {
            str_week_day += String(i);
            str_week_day += ",";
        }
        compare_operation *= 2;
    }
    str_week_day.remove(str_week_day.length() - 1, 1);
    DynamicJsonBuffer jsonBuffer(200);
    JsonObject &root = jsonBuffer.createObject();
    root["prog"] = String(program_letters[program]);
    root["week_day"] = "[" + str_week_day + "]";
    char json[200];
    root.printTo(json);
    client.publish((String(sys.uuid_) + "/program").c_str(), (const uint8_t *)json, strlen(json), false);
    // root.prettyPrintTo(Serial);
}
uint16_t pg_reag_to_web(uint16_t pg_time) //It return the time ok in minutes to the web
{
    uint8_t combinations[12][2] = {{72, 1}, {84, 2}, {96, 3}, {108, 4}, {120, 5}, {132, 6}, {144, 7}, {156, 8}, {168, 9}, {180, 10}, {192, 11}, {204, 12}};
    if (pg_time < 60)
        return pg_time;
    //First obtein the hours
    uint8_t index = 0;
    while (index++ < 12)
        if (pg_time < combinations[index][0])
            break;
    //Obtein the hours and minutes and print them
    uint16_t hours = (uint16_t)combinations[index][1];
    uint16_t min = (pg_time - 60 - 12 * (hours - 1)) * 5;
    printf("La hora real es: %i:%i \n", hours, min);
    return (hours * 60 + min);
}
void json_send_programs(int i, int id)
{
    DynamicJsonBuffer jsonBuffer(6300);
    JsonObject &root = jsonBuffer.createObject();
    char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    if (id > 10)
    {
        root["id"] = id;
    }
    root["prog"] = String(program_letters[i]);
    root["water"] = prog[i].waterPercent;
    root["interval"] = 1;
    root["interval_init"] = 0;
    JsonArray &week_day = root.createNestedArray("week_day");
    String str_week_day;
    uint8_t compare_operation = 1;
    uint8_t week_day_number = prog[i].wateringDay;
    for (int j = 1; j <= 7; j++)
    {
        if (week_day_number & compare_operation)
            week_day.add(j);
        compare_operation *= 2;
    }
    JsonArray &starts = root.createNestedArray("starts");
    for (int j = 0; j < 6; j++)
    {
        String start_min, start_hours;
        if (prog[i].start[j][0] == 0 && prog[i].start[j][0] == 0)
            starts.add(String(""));
        // LOGLN("nop start day");
        else
        {
            if (prog[i].start[j][0] < 9)
                start_min = "0" + String(prog[i].start[j][0]);
            else
                start_min = String(prog[i].start[j][0]);
            if (prog[i].start[j][1] < 9)
                start_hours = "0" + String(prog[i].start[j][1]);
            else
                start_hours = String(prog[i].start[j][1]);
            starts.add(start_min + ":" + start_hours);
        }
    }
    root["from"] = String("01/01");
    root["to"] = String("31/12");
    JsonArray &valves = root.createNestedArray("valves");
    for (int j = 0; j < 128; j++)
    {
        JsonObject &irrig = root.createNestedObject("");
        irrig["v"] = j + 1;
        int hours = prog[i].irrigTime[j] / 60;
        int minutes = prog[i].irrigTime[j] - hours * 60;
        //TODO:
        // LOGLN(prog[i].irrigTime[j]);
        // LOGLN(hours);
        // LOGLN(minutes);
        String str_hours, str_minutes;
        if (hours > 9)
            str_hours = String(hours);
        else
            str_hours = "0" + String(hours);
        if (minutes > 9)
            str_minutes = String(minutes);
        else
            str_minutes = "0" + String(minutes);
        if (hours == 0 && minutes == 0)
            irrig["time"] = "";
        else
            irrig["time"] = str_hours + ":" + str_minutes;
        valves.add(irrig);
    }
    char json[3700];
    //   root.prettyPrintTo(Serial);
    //   char json[200];
    root.printTo(json);
    client.publish((String(sys.uuid_) + "/program").c_str(), (const uint8_t *)json, strlen(json), false);
    // delay(FUKING_SLOW_TIME_PG);
}
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
    // Then I identify the topic related with
    if (identifier >= 1)
    {
        LOG("Inside parser:");
        LOGLN(sTopic);
        if (sTopic.indexOf("manvalve") != -1) //done
        {
            // delay(1000);
            //I firts of all parse the message
            JsonArray &valves = parsed["valves"];
            //I obtein the values of the parser info:
            String valve_time;
            int valve_number[128], valve_action[128], valve_min[128], valve_hours[128];
            //Start the game:
            for (int index_oasis = 0; index_oasis < valves.size(); index_oasis++)
            {
                valve_number[index_oasis] = valves[index_oasis]["v"].as<int>();
                valve_action[index_oasis] = valves[index_oasis]["action"].as<int>();
                LOG("->");
                LOG(valve_number[index_oasis]);
                LOG(":");
                LOGLN(valve_action[index_oasis]);
                if (valve_action[index_oasis] == 1) // If I have to open then I have to obtein the time
                {
                    valve_time = valves[index_oasis]["time"].as<String>();
                    // I parse the valve time
                    valve_hours[index_oasis] = (valve_time.charAt(0) - '0') * 10 + (valve_time.charAt(1) - '0');
                    valve_min[index_oasis] = (valve_time.charAt(3) - '0') * 10 + (valve_time.charAt(4) - '0');
                    ///////////////////////////////////////////////////////////////////
                    LOG("El valor de válvula es la:");
                    LOG(valve_number[index_oasis]);
                    LOG("durante ");
                    LOG(valve_hours[index_oasis]);
                    LOG(":");
                    LOGLN(valve_min[index_oasis]);
                    active.valves[index_oasis] = true;
                    pg_serial_action_valve(valve_action[index_oasis], valve_number[index_oasis], valve_hours[index_oasis], valve_min[index_oasis]);
                }
                else if (valve_action[index_oasis] == 0)
                {
                    LOG("APAGAR LA: ");
                    LOGLN(valve_number[index_oasis]);
                    pg_serial_action_valve(valve_action[index_oasis], valve_number[index_oasis], valve_hours[index_oasis], valve_min[index_oasis]);
                    active.valves[index_oasis] = false;
                }
                delay(FUKING_SLOW_TIME_PG);
                pg_listen();
            }
            send_web("/manvalve", sizeof("/manvalve"), identifier);
            //I send via radio to the receiver
        }
        else if (sTopic.indexOf("manprog") != -1) //done
        {
            //I obtein the values of the parser info:
            uint8_t activate = parsed["action"];
            // LOGLN(activate);
            String manual_program;
            manual_program = parsed["prog"].as<String>();
            // I first send it to
            delay(500);
            action_prog_pg(activate, manual_program.charAt(0)); //I send the command tom PG
            char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
            for (uint8_t index_prog; index_prog < 6; index_prog++)
                if (program_letters[index_prog] == manual_program.charAt(0))
                    if (activate == 1)
                        active.programs[index_prog] = true;
                    else
                        active.programs[index_prog] = false;
            send_web("/manprog", sizeof("/manprog"), identifier); // I send ack to the app
        }
        else if (sTopic.indexOf("oasis") != -1) //done
        {
            LOGLN("Publish in /oasis/app");
            JsonArray &oasis = parsed["oasis"];
            LOGLN("The value of the assignations are:");
            uint8_t assigned_id[4];
            uint8_t ide[15];
            for (uint8_t oasis_num = 0; oasis_num < oasis.size(); oasis_num++)
            {
                ide[oasis_num] = oasis[oasis_num]["id"];
                LOG("El oasis ");
                LOGLN(ide[oasis_num]);
                LOG("Tiene Asignadas las siguientes salidas: ");
                for (uint8_t d = 0; d < sizeof(assigned_id); d++)
                {
                    assigned_id[d] = oasis[oasis_num]["assign"][d];
                    LOG(assigned_id[d]);
                    LOG(", ");
                }
                LOGLN("");
                // change_oasis_assigned(ide[oasis_num], assigned_id);
            }
            send_web("/oasis", sizeof("/oasis"), identifier);
        }
        else if (sTopic.indexOf("program") != -1) //done
        {
            //I parse the letter of the program
            String manual_program = parsed["prog"].as<String>();
            //I determin the positions of the PG in which I have to write
            uint16_t position_starts = 416;     // This is the position of the starts in PG EEPROM memmory
            uint16_t mem_pos = 1024;            // This is the position of the starts in PG EEPROM memmory
            uint16_t position_percentage = 144; // This is the position of the irrig % in PG EEPROM memmory
            uint8_t position_week = 0xB0;       //This is for the week day starts
            uint8_t position_from_to = 0xC0;    //For changing the starting and stop irrig day, not year
            bool return_pg_program = true;
            switch (manual_program.charAt(0))
            {
            case 'B':
                position_starts = 428;
                mem_pos = 1152;
                position_percentage = 146;
                position_week = 0xB1;
                position_from_to = 0xC4;
                break;
            case 'C':
                position_starts = 440;
                mem_pos = 1280;
                position_percentage = 148;
                position_week = 0xB2;
                position_from_to = 0xC8;
                break;
            case 'D':
                position_starts = 452;
                mem_pos = 1408;
                position_percentage = 150;
                position_week = 0xB3;
                position_from_to = 0xCC;
                break;
            case 'E':
                position_starts = 0x1D0;
                mem_pos = 1536;
                position_percentage = 152;
                position_week = 0xB4;
                position_from_to = 0xD0;
                break;
            case 'F':
                position_starts = 476;
                mem_pos = 1664;
                position_percentage = 154;
                position_week = 0xB5;
                position_from_to = 0xD4;
                break;
            default:
                break;
            }
            //I parse the array of starts and valves, if there's any
            JsonArray &starts = parsed["starts"]; //done
            if (starts.success())
            {
                return_pg_program = false;
                //It sometimes fail and disconnect to the broker, that why I call this

                //First parse all the existed starts:
                String str_time; //For writting in the memmory
                uint16_t time_prog[6][2];
                uint16_t start_time_hours = 0, start_time_min = 0;
                String mem_starts_h;
                for (uint8_t index_starts = 0; index_starts < starts.size(); index_starts++)
                {
                    str_time = starts[index_starts].as<String>();
                    LOGLN(str_time);
                    time_prog[index_starts][0] = (str_time.charAt(0) - '0') * 10 + (str_time.charAt(1) - '0'); //save hours
                    time_prog[index_starts][1] = (str_time.charAt(3) - '0') * 10 + (str_time.charAt(4) - '0'); //save minutes
                    LOG("El valor del arranque ");
                    LOG(index_starts);
                    LOG(" es de: ");
                    LOG(time_prog[index_starts][0]);
                    LOG(":");
                    LOGLN(time_prog[index_starts][1]);
                    delay(FUKING_SLOW_TIME_PG);
                    for (uint8_t times_2 = 0; times_2 < 2; times_2++)
                    {
                        //First format the info y PG language
                        start_time_hours = time_to_pg_format(0, time_prog[index_starts][times_2]);
                        String mem_time_start_hours = String(start_time_hours, HEX);
                        mem_time_start_hours.toUpperCase();
                        if (mem_time_start_hours.length() != 2)
                            mem_time_start_hours = '0' + mem_time_start_hours;
                        mem_starts_h = String(position_starts + times_2, HEX);
                        mem_starts_h.toUpperCase();
                        //Not that is compleatly in HEX I copy in the data buffer
                        ////cmd_write_data[13] = mem_starts_h.charAt(0);
                        ////cmd_write_data[14] = mem_starts_h.charAt(1);
                        ////cmd_write_data[15] = mem_starts_h.charAt(2);
                        ////cmd_write_data[17] = mem_time_start_hours.charAt(0);
                        ////cmd_write_data[18] = mem_time_start_hours.charAt(1);
                        //calcrc((char *)////cmd_write_data, sizeof(//cmd_write_data) - 2);
                        //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));
                        for (int i = 0; i < sizeof(//cmd_write_data); i++)
                            LOGW(//cmd_write_data[i]);
                        delay(FUKING_SLOW_TIME_PG);
                        pg_listen();
                        client.loop();
                    }
                    position_starts += 2;
                }
                //Clear all the starts that are not defined and could be saved in pg memmory:
                uint8_t start_to_clear = 6 - starts.size();
                uint16_t position_end = position_starts + 6; // try to write in 0x1AA and then in 0x1A8
                while (start_to_clear > 0)
                {
                    for (uint8_t times = 0; times <= 1; times++)
                    {
                        //First clear from the bottom to the top of the memmory:
                        delay(800);
                        mem_starts_h = String(position_end + times, HEX);
                        mem_starts_h.toUpperCase();
                        //cmd_write_data[13] = mem_starts_h.charAt(0);
                        //cmd_write_data[14] = mem_starts_h.charAt(1);
                        //cmd_write_data[15] = mem_starts_h.charAt(2);
                        //cmd_write_data[17] = 'F';
                        //cmd_write_data[18] = 'F';
                        //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                        //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));
                        for (int i = 0; i < sizeof(//cmd_write_data); i++)
                            LOGW(//cmd_write_data[i]);
                        LOGLN(" ");
                        delay(FUKING_SLOW_TIME_PG);
                        pg_listen();
                        client.loop();
                    }
                    start_to_clear--;
                    position_end -= 2;
                }
            }
            //WEEK STARTS:
            JsonArray &week_day = parsed["week_day"]; //done
            if (week_day.success())
            {
                return_pg_program = false;
                String day = "";
                for (uint8_t items = 0; items < week_day.size(); items++)
                    day += week_day[items].as<String>();
                char days[day.length() + 1];
                day.toCharArray(days, sizeof(days));
                change_week_pg(days, sizeof(days), position_week);
                delay(FUKING_SLOW_TIME_PG);
            }
            JsonArray &valves = parsed["valves"]; //almost done
            if (valves.success())
            {
                return_pg_program = false;
                if (valves.size() == 0)
                {
                    LOGLN("Clear all the valves");
                    for (uint8_t index_valves = 0; index_valves < 30; index_valves++)
                    {
                        String mem_starts = String(mem_pos, HEX);
                        mem_starts.toUpperCase();
                        //cmd_write_data[13] = mem_starts.charAt(0);
                        //cmd_write_data[14] = mem_starts.charAt(1);
                        //cmd_write_data[15] = mem_starts.charAt(2);
                        //cmd_write_data[17] = '0';
                        //cmd_write_data[18] = '0';
                        //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                        //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));
                        int i;
                        for (i = 0; i < sizeof(//cmd_write_data); i++)
                            LOGW(//cmd_write_data[i]);
                        mem_pos++;
                        delay(FUKING_SLOW_TIME_PG);
                        pg_listen();
                        client.loop();
                    }
                }
                else
                {
                    // LOG("Exists Valves");
                    String irrig_time; //The string for the 00:00 time format
                    uint16_t number_valves;
                    uint16_t val = 0;
                    uint16_t clear_num = 1;
                    // send_web("/program", sizeof("/program"), identifier);
                    for (uint16_t index_valves = 0; index_valves < 30; index_valves++)
                    {
                        uint16_t time_valves[2]; //This is a huge and ridiculous
                        irrig_time = valves[index_valves]["time"].as<String>();
                        LOG(number_valves + 1);

                        number_valves = valves[index_valves]["v"].as<uint16_t>() - 1;
                        time_valves[0] = (irrig_time.charAt(0) - '0') * 10 + (irrig_time.charAt(1) - '0'); //save hours
                        time_valves[1] = (irrig_time.charAt(3) - '0') * 10 + (irrig_time.charAt(4) - '0'); //save minutes
                        LOG("Los tiempos de la válvula ");
                        LOG(number_valves + 1);
                        LOG(" son: ");
                        LOG(time_valves[0]);
                        LOG(":");
                        LOGLN(time_valves[1]);
                        //Obtein the number of the valves and write the EEPROM memmory in correct positions
                        val = time_to_pg_format(time_valves[0], time_valves[1]);
                        String mem_time = String(val, HEX);
                        if (mem_time.length() == 1)
                            mem_time = '0' + mem_time;
                        mem_time.toUpperCase();
                        LOGLN(mem_time);
                        String mem_starts = String(mem_pos + number_valves, HEX);
                        mem_starts.toUpperCase();
                        //cmd_write_data[13] = mem_starts.charAt(0);
                        //cmd_write_data[14] = mem_starts.charAt(1);
                        //cmd_write_data[15] = mem_starts.charAt(2);
                        //cmd_write_data[17] = mem_time.charAt(0);
                        //cmd_write_data[18] = mem_time.charAt(1);
                        //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                        //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));
                        for (int i = 0; i < sizeof(//cmd_write_data); i++)
                            LOGW(//cmd_write_data[i]);
                        delay(FUKING_SLOW_TIME_PG);
                        LOGLN(" ");
                        clear_num++;
                        pg_listen();
                        client.loop();
                    }
                }
            }
            //Write in the PG memmory the irrig %
            uint16_t irrig_percent = parsed["water"].as<uint16_t>();
            if (parsed["water"].success())
            {
                return_pg_program = false;
                LOGLN("Water:");
                LOGLN(position_percentage);
                LOGLN(irrig_percent);
                write_percentage_pg(position_percentage, irrig_percent);
            }
            if (parsed["from"].success())
            {
                return_pg_program = false;
                String time_from = parsed["from"].as<String>();
                write_start_stop_pg(true, time_from, position_from_to);
                String time_to = parsed["to"].as<String>();
                write_start_stop_pg(false, time_to, position_from_to);
                // send_web("/program", sizeof("/program"), identifier);
            }
            if (return_pg_program)
            {
                if (manual_program.charAt(0) == 'A')
                    json_send_programs(0, identifier);
                else if (manual_program.charAt(0) == 'B')
                    json_send_programs(1, identifier);
                else if (manual_program.charAt(0) == 'C')
                    json_send_programs(2, identifier);
                else if (manual_program.charAt(0) == 'D')
                    json_send_programs(3, identifier);
                else if (manual_program.charAt(0) == 'E')
                    json_send_programs(4, identifier);
            }
            else
                send_web("/program", sizeof("/program"), identifier);
        }
        else if (sTopic.indexOf("query") != -1) //done
        {
            json_query(String(identifier).c_str(), "AUTO");
        }
        else if (sTopic.indexOf("general") != -1) //receive the delay between valves and mv and valve
        {
            if (parsed["pump_delay"].success() || parsed["valve_delay"].success())
            {
                int pump_delay = 0;
                int valve_delay = 0;
                pump_delay = parsed["pump_delay"].as<int>();
                valve_delay = parsed["valve_delay"].as<int>();
                if (pump_delay < 0)
                    pump_delay = 0xFF + pump_delay + 1;
                //cmd_write_data[13] = '0';
                //cmd_write_data[14] = '5';
                //cmd_write_data[15] = '1';
                String ret_valve = String(valve_delay, HEX);
                if (ret_valve.length() == 1)
                    ret_valve = '0' + ret_valve;
                ret_valve.toUpperCase();
                //cmd_write_data[17] = ret_valve.charAt(0);
                //cmd_write_data[18] = ret_valve.charAt(1);
                //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data)); //real send to PG
                int i;
                for (i = 0; i < sizeof(//cmd_write_data); i++)
                    LOGW(//cmd_write_data[i]);
                delay(800);
                //cmd_write_data[13] = '0';
                //cmd_write_data[14] = '5';
                //cmd_write_data[15] = '0';
                String ret_mv = String(pump_delay, HEX);
                if (ret_mv.length() == 1)
                    ret_mv = '0' + ret_mv;
                ret_mv.toUpperCase();
                //cmd_write_data[17] = ret_mv.charAt(0);
                //cmd_write_data[18] = ret_mv.charAt(1);
                //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data)); //real send to PG
                for (i = 0; i < sizeof(//cmd_write_data); i++)
                    LOGW(//cmd_write_data[i]);
            }
            if (parsed["date"].success())
            {
                String web_time = parsed["date"].as<String>();

                uint8_t time_hours = (web_time.charAt(11) - '0') * 10 + (web_time.charAt(12) - '0');
                uint8_t time_min = (web_time.charAt(14) - '0') * 10 + (web_time.charAt(15) - '0');
                int time_day = (web_time.charAt(0) - '0') * 10 + (web_time.charAt(1) - '0');
                int time_month = (web_time.charAt(3) - '0') * 10 + (web_time.charAt(4) - '0');
                int time_year = (web_time.charAt(8) - '0') * 10 + (web_time.charAt(9) - '0');

                uint16_t d = time_day;
                uint16_t m = time_month;
                uint16_t y = 2000 + time_year;
                uint16_t weekday = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
                //Set PG in time:
                if (weekday == 0)
                    weekday = 7;
                change_time_pg(weekday, time_hours, time_min, time_min); //year/month/week/day/hour/min
                delay(300);
                pg_serial_date(time_day, time_month, time_year);
            }
            if (parsed["fertirrigations"].success())
            {
                String fertirrigation = parsed["fertirrigations"].as<String>();
                LOGLN(fertirrigation);
                uint8_t time_fertirrigation_wait[4][2];
                uint8_t time_fertirrigation_irrigation[4][2];

                uint8_t index_valves = 3;
                uint8_t f = 0;
                while (f < fertirrigation.length() && index_valves >= 0)
                {
                    time_fertirrigation_irrigation[index_valves][0] = (fertirrigation.charAt(f++) - '0') * 10 + (fertirrigation.charAt(f++) - '0');
                    time_fertirrigation_irrigation[index_valves][1] = (fertirrigation.charAt(f++) - '0') * 10 + (fertirrigation.charAt(f++) - '0');
                    time_fertirrigation_wait[index_valves][0] = (fertirrigation.charAt(f++) - '0') * 10 + (fertirrigation.charAt(f++) - '0');
                    time_fertirrigation_wait[index_valves][1] = (fertirrigation.charAt(f++) - '0') * 10 + (fertirrigation.charAt(f++) - '0');
                    LOG("El fertirrigante ");
                    LOG(14 - index_valves);
                    LOG(" tiene el siguiente tiempo de espera: ");
                    LOG(time_fertirrigation_wait[index_valves][0]);
                    LOG(":");
                    LOG(time_fertirrigation_wait[index_valves][1]);
                    LOG(" y el tiempo de riego es: ");
                    LOG(time_fertirrigation_irrigation[index_valves][0]);
                    LOG(":");
                    LOGLN(time_fertirrigation_irrigation[index_valves][1]);
                    pg_serial_fertirrigation(index_valves, time_fertirrigation_wait[index_valves][0], time_fertirrigation_wait[index_valves][1],
                                             time_fertirrigation_irrigation[index_valves][0], time_fertirrigation_irrigation[index_valves][1]);
                    index_valves--;
                    pg_listen();
                    client.loop();
                }
            }
            if (parsed["config"].success())
            {
                String activate_fertirrigation = parsed["config"].as<String>();

                LOGLN(activate_fertirrigation);
                bool active = false;
                for (int i = 0; i < activate_fertirrigation.length(); i++)
                {
                    if (activate_fertirrigation.charAt(i) == '1')
                    {
                        active = true;
                        break;
                    }
                    LOGW(activate_fertirrigation.charAt(i));
                }
                active ? pg_serial_activate_fertirrigation(true) : pg_serial_activate_fertirrigation(false);
            }
            if (parsed["pump_associations"].success())
            {

                //This should be on the parser.success...
                LOGLN("pump_associations");
                const char *pump_associations = parsed["pump_associations"];
                for (int i = 0; i < 10; i++)
                {
                    LOGW(pump_associations[i]);
                }
                char data_asso[] = "0000000000000000000000000000000007000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
                for (int i = 0; i < sizeof(data_asso); i++)
                    data_asso[i] = pump_associations[i];
                //I obtein the values and write on memmory:
                // web_to_pg_pump_associations(data_pump);
                int pump_mem = 0x100;
                int index_ = 0;
                while (index_ < sizeof(data_asso) - 2)
                {
                    char valve_number[] = "00";
                    valve_number[0] = data_asso[index_++];
                    valve_number[1] = data_asso[index_++];
                    String str_pos = String(pump_mem++, HEX);
                    str_pos.toUpperCase();
                    //cmd_write_data[13] = str_pos.charAt(0);
                    //cmd_write_data[14] = str_pos.charAt(1);
                    //cmd_write_data[15] = str_pos.charAt(2);
                    //I add the numbers:
                    //cmd_write_data[17] = valve_number[0];
                    //cmd_write_data[18] = valve_number[1];
                    //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                    //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));

                    LOGLN(" ");
                    delay(FUKING_SLOW_TIME_PG);
                    client.loop();
                }
                pg_serial_restart();
                delay(500);
            }
            if (parsed["master_pump_associations"].success())
            {
                // //Parse the master pump association:
                LOGLN("master_pump_associations");
                String master_pump = parsed["master_pump_associations"].as<String>();

                char data_pump[] = "C0F8FF02000002002000000008008080";
                for (int i = 0; i < 33; i++)
                    data_pump[i] = master_pump[i];
                //I obtein the values and write on memmory:
                uint8_t pump_mem_position = 0x80;
                uint8_t index = 0;
                while (index < sizeof(data_pump) - 2)
                {
                    char valve_number[] = "00";
                    valve_number[0] = data_pump[index++];
                    valve_number[1] = data_pump[index++];
                    String str_pos = String(pump_mem_position++, HEX);
                    str_pos.toUpperCase();
                    //cmd_write_data[13] = '0';
                    //cmd_write_data[14] = str_pos.charAt(0);
                    //cmd_write_data[15] = str_pos.charAt(1);
                    //cmd_write_data[17] = valve_number[0];
                    //cmd_write_data[18] = valve_number[1];
                    //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                    //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));
                    for (int i = 0; i < sizeof(//cmd_write_data); i++)
                        LOGW(//cmd_write_data[i]);
                    LOGLN(" ");
                    pg_listen();
                    delay(FUKING_SLOW_TIME_PG);
                    client.loop();
                }
                delay(FUKING_SLOW_TIME_PG);
            }
            if (parsed["pump_ids"].success())
            {
                String pump_ids = parsed["pump_ids"].as<String>();
                LOGLN(pump_ids);
                int pos = 0;
                for (int i = 0; i < pump_ids.length(); i++)
                {
                    String pump_position = String(0x180 + pos, HEX);
                    if (pump_position.length() == 1)
                        pump_position = '0' + pump_position;
                    //cmd_write_data[13] = pump_position.charAt(0);
                    //cmd_write_data[14] = pump_position.charAt(1);
                    //cmd_write_data[15] = pump_position.charAt(2);
                    String write_pg_pumps = String(pump_ids.charAt(i++)) + String(pump_ids.charAt(i));
                    if (write_pg_pumps.length() == 1)
                        write_pg_pumps = '0' + write_pg_pumps;
                    write_pg_pumps.toUpperCase();
                    //cmd_write_data[17] = write_pg_pumps.charAt(0);
                    //cmd_write_data[18] = write_pg_pumps.charAt(1);
                    //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
                    //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data)); //real send to PG
                    for (int j = 0; j < sizeof(//cmd_write_data); j++)
                        LOGW(//cmd_write_data[j]);
                    delay(FUKING_SLOW_TIME_PG);
                    pos++;
                }
            }
            if (parsed["pause"].success())
            {
                int pause = parsed["pause"].as<int>();
                LOG("I pause the programmer for: ");
                LOGLN(pause);
                String mem_pause = String(pause, HEX);
                mem_pause.toUpperCase();
                if (mem_pause.length() != 2)
                    mem_pause = '0' + mem_pause;
                //Not that is compleatly in HEX I copy in the data buffer
                //cmd_write_data[13] = '0';
                //cmd_write_data[14] = '4';
                //cmd_write_data[15] = 'E';
                //cmd_write_data[17] = mem_pause.charAt(0);
                //cmd_write_data[18] = mem_pause.charAt(1);
                //calcrc((char *)//cmd_write_data, sizeof(//cmd_write_data) - 2);
               // //Serial2.write(//cmd_write_data, sizeof(//cmd_write_data));
                for (int i = 0; i < sizeof(//cmd_write_data); i++)
                    LOGW(//cmd_write_data[i]);
                delay(600);
            }
            send_web("/general", sizeof("/general"), identifier);
        }
        else if (sTopic.indexOf("stop") != -1) //I stop all the stuff open
        {
            uint8_t index_close = 0;
            for (; index_close < 14; index_close++)
                if (active.valves[index_close])
                {
                    pg_serial_action_valve(false, index_close + 1, 0, 0);
                    delay(1000);
                }
            char program_letters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
            for (index_close = 0; index_close < 6; index_close++)
                if (active.programs[index_close])
                {
                    action_prog_pg(0, program_letters[index_close]); //I send the command tom PG
                    active.programs[index_close] = false;
                    send_stop_program = true;
                    delay(800);
                }
            stop_man_web.manual_web = false;
            stop_man_web.number_timers = 0;
            for (uint8_t c = 0; c < 10; c++)
            {
                stop_man_web.active[c] = false;
                stop_man_web.valve_number[c] = 0;
                stop_man_web.millix[c] = 0;
                stop_man_web.times[c] = 0;
            }
            send_web("/stop", sizeof("/stop"), identifier);
        }
        else if (sTopic.indexOf("command") != -1) //I stop all the stuff open
        {
            send_web("/command", sizeof("/command"), identifier);
            delay(FUKING_SLOW_TIME_PG);
            pg_serial_restart();
            delay(FUKING_SLOW_TIME_PG);
        }
    }
}
void web_to_pg_pump_associations(char pump_associations[])
{
    int real_pump = 8;
    //  8  7  6  5  4  3  2  1 asignation
    // 16 15 14 13 12 11 10  9

    char valve_number[] = "00";
    uint8_t index = 0;
    int times = 0;
    while (times < 16)
    {
        valve_number[0] = pump_associations[index++];
        valve_number[1] = pump_associations[index++];
        // printf("Char: 0x%c%c \n", valve_number[0], valve_number[1]);
        int valve_int = (int)strtol(valve_number, NULL, 16);
        LOGLN(valve_int);
        shift_pumps(valve_int, real_pump);
        real_pump += 8;
        times++;
    }
}
void shift_pumps(int valve_int, int pump)
{
    // printf("The number is: %d\n", valve_int);
    int compare = 0b10000000;
    for (int i = 0; i < 8; i++)
    {
        if (valve_int & compare)
        {
            LOG("The number is: ");
            LOGLN(pump);
        }
        compare = compare >> 0x01;
        pump--;
    }
}
void init_mqtt()
{
    client.setServer(mqtt_server, MQTT_PORT);
    client.setCallback(callback);
    reconnect();
}
