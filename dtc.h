/*
 * dtc
 * diagnostic trouble codes
 */
 
#ifndef dtc_h
#define dtc_h

#include "Arduino.h"
#include <ArduinoJson.h>
#include "screen.h"
#include "settings.h"
#include "screen.h"
#include "menus.h"
#include "comm.h"

void readDTCCodes();
void clearDTCCodes();

#endif
