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
extern int serverCountDown;
extern EthernetServer server;

#endif
