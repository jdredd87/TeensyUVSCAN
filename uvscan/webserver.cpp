/*
   webserver
   Contains Ethernet and HTTP Webserver
*/

#include "webserver.h"

int serverCountDown = 0;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Static IP Address for defaults

int ip1 = 192;
int ip2 = 168;
int ip3 = 50;
int ip4 = 10;

EthernetServer server(80);

String getMACAddress()
{
  String addr = "";
  byte macBuffer[6];
  Ethernet.MACAddress(macBuffer);
  for (byte octet = 0; octet < 6; octet++) {
    addr.concat(ByteToHex(macBuffer[octet]));
    if (octet < 5) {
      addr.concat("-");
    }
  }
  return addr;
}

bool serversetup() {
  printStage("TCPIP Init");
  teensyMAC(mac);
  String IP;
  IP = cfg.IPAddress; // will use this to split up IP Address later on

  if (cfg.useDHCP) {
    cfg.IPAddress = "1.1.1.1"; // default cause we are DHCP mode
    printStage("DHCP Startup");
    Ethernet.begin(mac);
    if (Ethernet.begin(mac) == 0) {
      printStage("DHCP FAILED");
      Serial.println("Failed to configure Ethernet using DHCP");
      if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        printStage("Hardware not found");
      } else if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("Ethernet cable is not connected.");
        printStage("Cable not connected");
      }
      return false;
    }
  } else
  {
    printStage("Static IP Startup");
    ip1 = getValue(IP, '.', 0).toInt();
    ip2 = getValue(IP, '.', 1).toInt();
    ip3 = getValue(IP, '.', 2).toInt();
    ip4 = getValue(IP, '.', 3).toInt();
    IPAddress ip(ip1, ip2, ip3, ip4);
    Ethernet.begin(mac, ip);
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      printStage("Hardware not found");
      return false;
    }
  }

  for (int ex=0; ex<100; ex++){
   delay(100);
   if (Ethernet.linkStatus() == LinkON) break; 
  }
  
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    printStage("Cable not connected");
    return false;
  }

  // update config and save the IP Address
  // will happen if DHCP or Static, lazy I know.

  cfg.IPAddress =  String() + Ethernet.localIP()[0] + "." +
                   Ethernet.localIP()[1] + "." +
                   Ethernet.localIP()[2] + "." +
                   Ethernet.localIP()[3];

  
  
  saveConfiguration();
  printStage("HTTP Server Startup");
  server.begin();
  Serial.println("");
  Serial.println("HTTP Server Startup");
  Serial.println("");
  Serial.print("IP Address ");
  Serial.println(Ethernet.localIP());
  Serial.print("MAC Address ");
  Serial.println(getMACAddress());
  Serial.println("");
  
  printStage("");
  return true;
}

int serverloopidx = 0;
int serverloopstep = 0;

void serverloop() {
  delay(1);
  serverloopidx++;

  if (serverloopidx >= (1024 * 512)) {
    Serial.print(".");
    serverloopidx = 0;
    serverloopstep++;
    if (serverloopstep >= 32) {
      Serial.println("");
      serverloopstep = 0;
    }
  }

  EthernetClient client = server.available();
  if (client) {
    Serial.println("HTTP Client Connection");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      delay(1);
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {

          /// come back to this later to make a better looking page

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 1");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<head>");
          client.println("<style>");
          client.println("table, th, td {");
          client.println("border: 0px solid black;");
          client.println("  border-collapse: collapse;");
          client.println("}");
          client.println("table.center {");
          client.println("margin-left: auto; ");
          client.println("margin-right: auto;");
          client.println("}");
          client.println("@media screen and (min-width: 1000px) {  div.mysize { font-size: 80px;  }}");
          client.println("@media screen and (max-width: 800px)  {  div.mysize { font-size: 60px;  }}");
          client.println("@media screen and (min-width: 600px)  {  div.mysize { font-size: 40px;  }}");
          client.println("@media screen and (max-width: 300px)  {  div.mysize { font-size: 30px;  }}");
          client.println("@media screen and (max-width: 0px)    {  div.mysize { font-size: 15px;  }}");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<table class=\"center\">");
          for (int idx = 0; idx < NUM_PIDS; idx++) {
            if (PIDS[idx]._selected == true) {
              client.println("<tr>");
              client.print("<td>");
              client.print("<div class=\"mysize\">");
              client.print(PIDS[idx]._name);
              client.print("</div>");
              client.print("</td>");
              client.print("<td>");
              client.print("<div class=\"mysize\">");
              client.print(random(9999)); // PIDS[idx]._value);
              client.print("</div>");
              client.print("</td>");
              client.print("</tr>");
            }
          }
          client.println("</table>");
          client.println("</body>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}
