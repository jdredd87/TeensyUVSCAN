/* 
 * webserver
 * Contains Ethernet and HTTP Webserver
 */

#ifndef webserver_h
#define webserver_h
#include "Arduino.h"
#include <SPI.h>
#include <NativeEthernet.h>
#include <TeensyID.h>
#include "settings.h"
#include "screen.h"
#include "io.h"
#include "pids.h"

void serverloop();
bool serversetup();
String getMACAddress();
bool ServiceClient(EthernetClient * client);
char GetRequestedHttpResource(char * req_line, char * file_name, char * file_type);

extern int serverCountDown;
extern EthernetServer server;
extern bool stopserver;


#endif
