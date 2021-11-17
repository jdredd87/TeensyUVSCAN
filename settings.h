/*        
   Settings
   Contains SD card support
   Loading/Saving of files in JSON Format
*/

#ifndef settings_h
#define settings_h

#include "Arduino.h"
#include <SD.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "pids.h"
#include "screen.h"
#include "sdios.h"
#include "menus.h"
#include "io.h"
#include "pids.h"

struct scanConfig {
  bool enableBeep;
  bool startupScan;
  bool useDHCP;
  String IPAddress;
};


void SDinit(bool showStartup);
void loadConfiguration();
void saveConfiguration();
void savePIDSfile();
void loadPIDSfile();
void toggleDHCP();
void initFlashMem(bool showStartup);

String setIP(String IP);
extern scanConfig cfg;
extern File sdStorage;
extern LittleFS_QSPIFlash flashStorage;
// extern LittleFS_QPINAND flashStorage;
extern bool flasheMEMEnabled;

#endif
