#include "Arduino_LED_Matrix.h"
#include "WiFiS3.h"

#define LED1 13
#define LED2 8

ArduinoLEDMatrix matrix;

const uint32_t hi[] = {
  0xcdfcdfcc,
  0x4fc4fc4c,
  0xc4cdfcdf,
  66
};

char ssid[] = "TP-Link_1936"; //Enter your WIFI SSID
char pass[] = "97792710";   //Enter your WIFI password
int keyIndex = 0;      // your network key index number (needed only for WEP)

String output1 = "off";
String output2 = "off";
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  matrix.begin();

  // set the LED pins to OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  // Turn off LEDs initially
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();
  printWifiStatus();
}

void loop() {
  webServer();
  LEDMatrix();
  delay(0.01);
}

void LEDMatrix() {
  matrix.loadFrame(hi);
}

void webServer() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) { // this is triggered when you get to the end of the GET request header
            // Serial.write("test");
            client.println(
              "HTTP/1.1 200 OK"
              "Content-type:text/html"
              "Connection: close"
              "\n"
            );

            if (header.indexOf("GET /ledon1") >= 0) {
              output1 = "on";
              digitalWrite(LED1, HIGH);
            } else if (header.indexOf("GET /ledoff1") >= 0) {
              output1 = "off";
              digitalWrite(LED1, LOW);
            }
            if (header.indexOf("GET /ledon2") >= 0) {
              output2 = "on";
              digitalWrite(LED2, HIGH);
            } else if (header.indexOf("GET /ledoff2") >= 0) {
              output2 = "off";
              digitalWrite(LED2, LOW);
            }

            client.println( 
              "<!DOCTYPE html><html>"
              "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
              "<link rel=\"icon\" href=\"data:,\">"
              "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
              ".on { background-color: #FF0000; border: 5px; color: white; padding: 16px 40px; border-radius: 20px;"
              "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
              ".off {background-color: #000000;border: 5px; color: white; padding: 16px 40px; border-radius: 20px;"
              "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>"
            );

            client.println("<body><h1>technolab electronics</h1>");

            client.println("<p>LED1 " + output1 + "</p>");
            if (output1 == "off") {
              client.println("<p><a href=\"/ledon1\"><button class=\"off\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/ledoff1\"><button class=\"on\">Turn OFF</button></a></p>");
            }
            
            client.println("<p>LED2 " + output2 + "</p>");
            if (output2 == "off") {
              client.println("<p><a href=\"/ledon2\"><button class=\"off\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/ledoff2\"><button class=\"on\">Turn OFF</button></a></p>");
            }

            client.println("</body></html>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("Now open this URL on your browser --> http://");
  Serial.println(ip);
}
