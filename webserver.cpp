/*
  webserver
  Contains Ethernet and HTTP Webserver
*/

#include "webserver.h"
#include "scanner.h"

#define FILE_NAME_LEN 64 // maximum length of file name including path

// HTTP request type
#define HTTP_invalid 0
#define HTTP_GET 1
#define HTTP_POST 2

// file types
#define FT_HTML 0
#define FT_ICON 1
#define FT_CSS 2
#define FT_JAVASCRIPT 3
#define FT_JPG 4
#define FT_PNG 5
#define FT_GIF 6
#define FT_TEXT 7
#define FT_CSV 8
#define FT_INVALID 9


int webThreadID;

bool stopserver = false; // hack to just trick the loop during RAM test. Seems to be no STOP to server once started?

int serverCountDown = 0;
byte mac[] = {
  0xDE,
  0xAD,
  0xBE,
  0xEF,
  0xFE,
  0xED
};

// Static IP Address for defaults

int ip1 = 192;
int ip2 = 168;
int ip3 = 50;
int ip4 = 10;


const char * file_types[] = {
  "text/html", // 0
  "image/x-icon", // 1
  "text/css", // 2
  "application/javascript", // 3
  "image/jpeg", // 4
  "image/png", // 5
  "image/gif", // 6
  "text/plain", // 7
  "text/csv"
}; // 8

// Threads::Mutex weblock;

EXTMEM EthernetServer server(80);

String getMACAddress() {
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

  if (IP == "") {
    Serial.println("Static IP is BLANK. Switching to DHCP instead.");
    cfg.useDHCP = true;
  }

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
  } else {
    printStage("Static IP Startup");
    Serial.print("Static IP ");
    Serial.println(IP);

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

  for (int ex = 0; ex < 100; ex++) {
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

  cfg.IPAddress = String() + Ethernet.localIP()[0] + "." +
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

bool ServiceClient(EthernetClient * client) {
  static boolean currentLineIsBlank = true;
  char cl_char;
  File webFile;
  // file name from request including path + 1 of null terminator
  char file_name[FILE_NAME_LEN + 1] = {
    0
  }; // requested file name
  char http_req_type = 0;
  char req_file_type = FT_INVALID;

  static char req_line_1[40] = {
    0
  }; // stores the first line of the HTTP request
  static unsigned char req_line_index = 0;
  static bool got_line_1 = false;

  if (client -> available()) { // client data available to read
    cl_char = client -> read();

    if ((req_line_index < 39) && (got_line_1 == false)) {
      if ((cl_char != '\r') && (cl_char != '\n')) {
        req_line_1[req_line_index] = cl_char;
        req_line_index++;
      } else {
        got_line_1 = true;
        req_line_1[39] = 0;
      }
    }

    if ((cl_char == '\n') && currentLineIsBlank) {
      // get HTTP request type, file name and file extension type index
      http_req_type = GetRequestedHttpResource(req_line_1, file_name, & req_file_type);

      String URLFN = urldecode(file_name);

      URLFN.toCharArray(file_name, URLFN.length() + 1);

      Serial.print("req file name = ");
      Serial.println(file_name);
      Serial.print("req file req_line_1 = ");
      Serial.println(req_line_1);



      if (http_req_type == HTTP_GET) { // HTTP GET request
        //  if (req_file_type < FT_INVALID) {      // valid file type
        if (1 == 1) { // valid file type

          Serial.print("Incoming > ");
          Serial.println(file_name);

          // Ajax request - send XML file
          if (StrContains(file_name, "/ajax_inputs")) {
            int MPH;
            int RPM;
            MPH = random(200);
            RPM = random(7000);
            client -> println("HTTP/1.1 200 OK");
            client -> println("Content-Type: text/xml");
            client -> println("Access-Control-Allow-Origin: null");
            client -> println("Connection: keep-alive");
            client -> println("");
            client -> println("<?xml version = \"1.0\" ?>");
            client -> println("<scanner>");

            for (int idx = 0; idx < sPIDS.size(); idx++) {
              client -> print("<");

              String shortname;
              shortname = sPIDS.at(idx)._shortname;

              shortname.replace("(", "");
              shortname.replace(")", "");
              shortname.replace(" ", "");

              client -> print(shortname);

              client -> print(">");
              client -> print(sPIDS.at(idx)._lastvalue);
              client -> print("</");
              client -> print(shortname);
              client -> println(">");
            }

            client -> println("</scanner>");
          }  else if (strstr(file_name, "/remove/")) { /// delete file request

            Serial.println("Remove found!");
            char fn[256];
            char logfn[256];
            strncpy(fn, file_name, strlen(file_name) + 1);
            strremove(fn, "/remove/");
            if (fn != "") {
              strncpy(logfn, "/logs/", 6);
              strcat(logfn, fn);             
              if (strcmp(logfn, "/logs/yes-all-files.csv") == 0) { // yes to delete all csv log files
                Serial.println("Removing all Files!");
                File root;
                root = SD.open("/logs");
                while (true) {
                  File entry = root.openNextFile();
                  if (!entry) {
                    break;
                  }
                  char CFN[CurrentLogFileName.length() + 1];
                  char longFN[64];
                  CurrentLogFileName.toCharArray(CFN, CurrentLogFileName.length() + 1);
                  sprintf(longFN, "%s%s", "/logs/", entry.name());
                  if (strcmp(CFN, longFN) == 0)
                  {
                    Serial.println("Skipping");  // skip deleting file we are scanning on
                    continue;
                  }               
                  SD.remove(longFN);
                  entry.close();
                }
                root.close();

              } else
              {
                SD.remove(logfn);
              }
            }
            client -> println(F("HTTP / 1.1 200 OK"));
            client -> println("Access-Control-Allow-Origin: null");
            client -> print(F("Content - Type: "));
            client -> println(file_types[req_file_type]);
            client -> println(F("Connection: close"));
            client -> println();
            client -> println("<head>");
            client -> println("<meta http-equiv=\"Refresh\" content=\"0; URL=..\\\">");
            client -> println("</head>");
          } else

            if (strcmp(file_name, "index.htm") == 0) {
              Serial.println("loading....");

              client -> println(F("HTTP / 1.1 200 OK"));
              client -> print(F("Content - Type: "));
              client -> println("Access-Control-Allow-Origin: null");
              client -> println(file_types[req_file_type]);
              client -> println(F("Connection: close"));
              client -> println();

              client -> println("<!DOCTYPE html>");
              client -> println("<html lang=\"en\">");
              client -> println("<head>");
              client -> println("<title>UVScanner Web Server");
              client -> println("</title>");
              client -> println("<meta charset=\"utf-8\">");
              client -> println("    <link rel=\"stylesheet\" href=\"styles.css\">");
              client -> println("</head>");
              client -> println("  <body>");

              client -> println("<script>");
              client -> println("function deleteFile(fn) { ");
              client -> println(" if (confirm('Are you sure you want to delete log?')) { ");
              client -> println(" window.location.href = '/remove/'+fn;");
              client -> println("   } ");
              client -> println("}");
              client -> println("</script>");

              client -> println("<h1 align=\"center\">UVScanner");
              client -> println("</h1>");
              client -> println("<h1 align=\"center\"><a href=\"live.htm\">Live Data View");
              client -> println("</a>");
              client -> println("</h1>");
              client -> println("<h1 align=\"center\">Log Files");
              client -> println("</h1>");
              client -> println("<p align=\"center\">&nbsp;");

              client -> print("<button onclick=\"deleteFile('");
              client -> print("yes-all-files.csv");
              client -> print("')\"");
              client -> println(" type=\"button\">Remove All Logs</button>");
              client -> print("<br><br>");


              File root;
              root = SD.open("/logs");
              while (true) {
                File entry = root.openNextFile();
                if (!entry) {
                  break;
                }
                String FN;
                FN = entry.name();
                if (!FN.endsWith(".csv")) {
                  continue;
                }

                String CFN;
                CFN = CurrentLogFileName;
                CFN.remove(0, 6);
                Serial.println(FN);
                Serial.println(CFN);

                if (FN == CFN) {
                  client -> print("Activly Scanning");
                  client -> print("&nbsp;&nbsp;&nbsp;");
                  client -> print(entry.name());
                  client -> print("&nbsp;&nbsp;&nbsp;");
                  client -> print("<br><br>");
                } else
                {
                  client -> print("<button onclick=\"window.location.href='./view.htm?logfile=/logs/");
                  client -> print(entry.name());
                  client -> print("' \"");
                  client -> println("type=\"button\">View</button>");
                  client -> print("&nbsp;&nbsp;&nbsp;");
                  client -> println("&nbsp;&nbsp;&nbsp;");
                  client -> print("<a href=\"\\logs\\");
                  client -> print(entry.name());
                  client -> print("\">");
                  client -> print(entry.name());
                  client -> println("</a>");
                  client -> print("&nbsp;&nbsp;&nbsp;");
                  client -> println("&nbsp;&nbsp;&nbsp;");
                  client -> print("<button onclick=\"deleteFile('");
                  client -> print(entry.name());
                  client -> print("')\"");
                  client -> println(" type=\"button\">Remove</button>");
                  client -> print("<br><br>");
                }
                entry.close();
              }
              root.close();

              client -> println("</p>");
              client -> println("</body>");
              client -> println("</html>");
            } else {
              Serial.println("");
              Serial.println("webFile");
              Serial.println(file_name);
              webFile = SD.open(file_name); // open requested file
              if (webFile) {
                client -> println(F("HTTP/1.1 200 OK"));
                client -> println("Access-Control-Allow-Origin: null");
                client -> print(F("Content-Type: "));
                client -> println(file_types[req_file_type]);
                client -> println(F("Connection: close"));
                client -> println();
                // send web page
                while (webFile.available()) {
                  int num_bytes_read;
                  char byte_buffer[64];
                  // get bytes from requested file
                  num_bytes_read = webFile.read(byte_buffer, 64);
                  // send the file bytes to the client
                  client -> write(byte_buffer, num_bytes_read);
                }
                webFile.close();
              } else {
                Serial.println("INVALID REQUEST!");
              }
            }
        } else {
          Serial.println("INVALID FILE TYPE");
        }
      } else if (http_req_type == HTTP_POST) {
        Serial.println("POST REQUEST NOT SUPPORTED");
      } else {
        Serial.println("UNSUPPORTED REQUEST NOT SUPPORTED");
      }
      req_line_1[0] = 0;
      req_line_index = 0;
      got_line_1 = false;
      return 1;
    }
    if (cl_char == '\n') {
      currentLineIsBlank = true;
    } else if (cl_char != '\r') {
      currentLineIsBlank = false;
    }
  }
  return 0;
}

char GetRequestedHttpResource(char * req_line, char * file_name, char * file_type) {
  char request_type = HTTP_invalid;
  char *str_token;
  *file_type = FT_INVALID;

  str_token = strtok(req_line, " ");

  if (strcmp(str_token, "GET") == 0) {
    request_type = HTTP_GET;
    str_token = strtok(NULL, " ");
    if (strcmp(str_token, "/") == 0) {
      strcpy(file_name, "index.htm");
      *file_type = FT_HTML;
    } else if (strlen(str_token) <= FILE_NAME_LEN) {
      str_token = strtok(str_token, "?");
      strcpy(file_name, str_token);
      Serial.print("fn = ");
      Serial.println(file_name);
      str_token = strtok(str_token, ".");
      str_token = strtok(NULL, ".");

      if (strcmp(str_token, "htm") == 0) {
        * file_type = 0;
      } else if (strcmp(str_token, "ico") == 0) {
        * file_type = 1;
      } else if (strcmp(str_token, "css") == 0) {
        * file_type = 2;
      } else if (strcmp(str_token, "js") == 0) {
        * file_type = 3;
      } else if (strcmp(str_token, "jpg") == 0) {
        * file_type = 4;
      } else if (strcmp(str_token, "png") == 0) {
        * file_type = 5;
      } else if (strcmp(str_token, "gif") == 0) {
        * file_type = 6;
      } else if (strcmp(str_token, "txt") == 0) {
        * file_type = 7;
      } else if (strcmp(str_token, "csv") == 0) {
        * file_type = 8;
      } else {
        * file_type = 9;
      }
    } else {
      Serial.println("Invalid File. Too long?");
    }
  } else if (strcmp(str_token, "POST") == 0) {
    request_type = HTTP_POST;
  }
  return request_type;
}

void serverloop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      Serial.println("incoming client...");
      if (ServiceClient(&client)) {
        break;
      }
    }
    client.stop();
  }
}
