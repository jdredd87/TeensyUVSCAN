#ifndef scanner_h
#define scanner_h

#include "Arduino.h"
#include "menus.h"
#include "expression_parser.h"
#include "settings.h"
#include "menus.h"
#include "comm.h"
#include "pids.h"
#include "webserver.h"
#include <TimeLib.h>
#include "TeensyThreads.h"


void togglestartupScan();
void startScanner();
extern String CurrentLogFileName;

#endif
