/* 
 * Settings
 * Contains SD card support
 * Loading/Saving of files in JSON Format
 */

#ifndef settings_h
#define settings_h

#include "Arduino.h"
#include "LittleFS.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include "pids.h"
#include "screen.h"
#include "SdFat.h"
#include "sdios.h"
#include "menus.h"
#include "io.h"

struct scanConfig{
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
extern SdFs sd;
extern cid_t m_cid;
extern csd_t m_csd;
extern LittleFS_QSPIFlash configfs;
extern bool flasheMEMEnabled;

#endif
