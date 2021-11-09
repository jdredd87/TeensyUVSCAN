/*
 * io
 * Simple commands and conversion routines
 */
 
#ifndef io_h
#define io_h

#include "Arduino.h"
#include <ArduinoJson.h>
#include "screen.h"
#include "settings.h"
#include "screen.h"
#include "menus.h"

void beepOnce();
void beepLong();
void toggleBeep();
void reboot(String msg);
void printFile(String fn);
int validate_ip(char *ip);
long StrToInt(String str);
String HexToString(String STR);
String ByteToHex(byte data);
String getValue(String data, char separator, int index);

#endif
