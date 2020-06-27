#include <WiFi.h>

const char *ssid = "Hotel_Config_Lamp";
const char *password = "hotel2020";

WiFiServer server(80); // Set web server port number to 80
String header;         // Variable to store the HTTP request

uint8_t wifi_name[30], wifi_pass[30];

char web_compleat[] = "<!DOCTYPE html>\
<html <head>\
<meta name=\"viewport \" content=\"width=device-width, initial-scale=1\">\
<style>\
    html {\
        font-family: Helvetica;\
        display: inline-block;\
        margin: 0px auto;\
        background-color: #131e48;\
        text-align: center;\
        color: #7dbedc;\
    }\
    h4 {\
        color: #d0ca17;\
    }\
</style>\
</head>\
<body>\
    <h1>Hotel Credentials</h1>\
    <h3>___________________ </h3>\
    <span style=\"display:block; height: 40px; \"></span>\
    <form action=\"action_page.php\"> Wifi Name: <input type=\"text \" name=\"wifi_name\"><br>\
        Password: <input type=\"text\" name=\"wifi_pass\"><br>\
        <h3>___________________ </h3>\
        <h4>Select week day: </h4>\
        Week (LMXJVSD): <input type=\"text\" name=\"week\">\
        <h4>Select start time: </h4>\
        Hours: <input type=\"text\" name=\"hours\">\
        <h3>  </h3>\
        <input type=\"Submit\">\
        <h3>___________________ </h3>\
    </form>\
        <span style=\"display:block; height: 100px; \"></span>\
        <h3> Hotel setup web page</h3>\
        <h5> July - 2020</h5>\
</body>\
</html>";
void setup()
{
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Access point in: ");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println(IP);
  server.begin();

  while (!obtein_credentials())
    ;
}

void loop()
{
  Serial.println("I have pass so i can connected to wifi :)");
  delay(5000);
}

bool obtein_credentials()
{
  WiFiClient client = server.available(); // Listen for incoming clients
  if (client)
  {                               // If a new client connects,
    Serial.println("New Client"); // print a message out in the serial port
    String currentLine = "";      // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        //Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            if (header.indexOf("GET /action_page.php?wifi_name=") >= 0)
            {
              //GET /action_page.php?wifi_name=asd&wifi_pass=Fgh HTTP/1.1
              uint8_t index_wifi_name = header.indexOf("wifi_name=") + 10;
              uint8_t index_wifi_pass = header.indexOf("&wifi_pass=") + 11;

              Serial.println(" ");

              for (uint8_t i = 0; i < (header.indexOf("&wifi_pass=") - index_wifi_name); i++)
              {
                wifi_name[i] = header.charAt(index_wifi_name + i);
                if (wifi_name[i] == '+')
                  wifi_name[i] = ' ';
                Serial.write(wifi_name[i]);
              }
              Serial.println(" ");

              for (uint8_t i = 0; i < (header.indexOf(" HTTP/1.1") - index_wifi_pass); i++)
              {
                wifi_pass[i] = header.charAt(index_wifi_pass + i);
                if (wifi_pass[i] == '+')
                  wifi_pass[i] = ' ';
                Serial.write(wifi_pass[i]);
              }
              Serial.println(" ");
              return true;
            }
            // Display the HTML web page
            client.println(web_compleat);
            /*
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; background-color: #1c2e75; text-align: center;color: #CACAC8; }");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("body{ background-color: black;  color: white;}");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            client.println("<body><h1>Hotel Credentials</h1>");
            client.println("<h4>___________________ </h4>");
            client.println("<span style=\"display:block; height: 40px;\"></span>");
            client.println("<form action=\"/action_page.php\"> Wifi Name: <input type=\"text\" name=\"wifi_name\"><br>");
            client.println("Password: <input type=\"text\" name=\"wifi_pass\"><br> <input type=\"Submit\"></form>");
            client.println("<h4>___________________ </h4>");
            client.println("<span style=\"display:block; height: 100px;\"></span>");
            client.println("<h4> Hotel setup web page</h4>");
            client.println("<h5> July - 2020</h5>");
            client.println("</body></html>");
            client.println();
            */
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");
  }
  return false;
}
