#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
// MESSAGE STRINGS
const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String SETUP_SERVER_START = "SETUP: HTTP server started --> IP addr: ";
const String SETUP_SERVER_PORT = " on port: ";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// and a content-type so the client knows what's coming, then a blank line:
const String HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";
const String HTML_WELCOME = "<h1>Welcome to your ESP32 Web Server!</h1>";
// BASIC WIFI CONFIGURATION CONSTANTS
// The SSID (Service Set IDentifier), in other words, the network's name
const char *SSID = "ArpaNet";
// Password for the network
// By default the ESP32 uses WPA / WPA2-Personal security, therefore the
// the password MUST be between 8 and 63 ASCII characters
const char *PASS = "123parola";
// The default port (both TCP & UDP) of a WWW HTTP server number according to
// RFC1340 is 80
const int HTTP_PORT_NO = 80;
// ADDITIONAL GLOBALS
// Initialize the HTTP server on the ESP32 board
WiFiServer HttpServer(HTTP_PORT_NO);
void setup() {
Serial.begin(9600);
if (!WiFi.softAP(SSID, PASS)) {
// replace with if (!WiFi.softAP(SSID, PASS)) to use the password
Serial.println(SETUP_ERROR);
// Lock system in infinite loop in order to prevent further execution
while (1)
;
}
// Get AP's IP address for info message
const IPAddress accessPointIP = WiFi.softAPIP();
const String webServerInfoMessage = SETUP_SERVER_START + accessPointIP.toString()
+ SETUP_SERVER_PORT + HTTP_PORT_NO;
// Start the HTTP server
HttpServer.begin();
Serial.println(webServerInfoMessage);
}
void loop() {
WiFiClient client = HttpServer.available(); // listen for incoming clients
if (client) { // if you get a client,
Serial.println(INFO_NEW_CLIENT); // print a message out the serial port
String currentLine = ""; // make a String to hold incoming data from the client
while (client.connected()) { // loop while the client's connected
if (client.available()) { // if there's bytes to read from the client,
const char c = client.read(); // read a byte, then
Serial.write(c); // print it out the serial monitor
if (c == '\n') { // if the byte is a newline character
// if the current line is blank, you got two newline characters in a row.
// that's the end of the client HTTP request, so send a response:
if (currentLine.length() == 0) {
// Send welcome page to the client
printWelcomePage(client);
break;
} else currentLine = "";
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
}
}
}
// close the connection:
client.stop();
Serial.println(INFO_DISCONNECT_CLIENT);
Serial.println();
}
}
void printWelcomePage(WiFiClient client) {
// Always start the response to the client with the proper headers
client.println(HTTP_HEADER);
// Send the relevant HTML
client.print(HTML_WELCOME);
// The HTTP response ends with another blank line
client.println();
}