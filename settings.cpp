/*
   Settings
   Contains SD card support
   Loading/Saving of files in JSON Format
*/

#include "settings.h"

//#define USE_SDCARD // Use SD CARD if no flash memory installed
#define USE_QSPI // Typical NOR FLASH
//#define USE_QSPI_NAND // NAND Flash

#if defined(USE_QSPI)
LittleFS_QSPIFlash flashStorage;
char szDiskMem[] = "QSPI_DISK";
#endif

#if defined(USE_QSPI_NAND)
char szDiskMem[] = "QSPI_NAND";
LittleFS_QPINAND flashStorage;
#endif

#if defined(USE_SDCARD)
char szDiskMem[] = "SD";
#endif

bool flasheMEMEnabled = false;
#define SD_FAT_TYPE 1

const int pidfilesize = 65536; // allocate 64k of ram for PID file, should be plenty!

void SDinit(bool showStartup) {
  Serial.println("SD Card Init");
  if (showStartup) {
    printStage("SD Card Startup");
  }
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD Card unable to start");
  } else {
    Serial.println("SD Card Initialized");
    Serial.printf("SD Size : %d bytes \n", SD.totalSize());
    Serial.printf("SD Used : %d bytes \n", SD.usedSize());
  }
  if (showStartup) {
    printStage("");
  }
  Serial.println("");
}

void initFlashMem(bool showStartup) {
  // Basically just disable this function if in SD CARD mode

#if!defined(USE_SDCARD)
  if (showStartup) {
    printStage("FlashMEM Init");
  }

  if (!flashStorage.begin()) {
    flasheMEMEnabled = false;
    Serial.printf("Error starting %s\n", szDiskMem);
    if (showStartup) {
      printStage("FlashMEM Error");
    }

  } else {
    flasheMEMEnabled = true;
    Serial.printf("%s enabled! \n", szDiskMem);
    Serial.printf("Flash Size : %d bytes \n", flashStorage.totalSize());
    Serial.printf("Flash Used : %d bytes \n", flashStorage.usedSize());
    printStage("FlashMEM Started");
  }
#endif
}

/******* Configuration Section *******/

EXTMEM scanConfig cfg;

const char * cfgfilename = "config.txt";

void loadConfiguration() {
  Serial.println("");
  printStage("Loading config.txt");

#if!defined(USE_SDCARD)
  Serial.println("loadConfiguration FLASHMEM");
  File file1 = flashStorage.open(cfgfilename);
#else
  Serial.println("loadConfiguration SDCARD");
  File file1 = SD.open(cfgfilename);
#endif

  StaticJsonDocument < 512 > doc;
  DeserializationError error = deserializeJson(doc, file1);

  if (error) {
    Serial.print(F("Failed to read file, using default configuration"));
    printStage("Read config.txt");
    delay(500);
    printStage("Using Defaults");
    delay(2500);
  } else {
    Serial.println("");
    Serial.print(F("File opened "));
    Serial.println(cfgfilename);
  }

  cfg.enableBeep = doc["enableBeep"] | false;
  cfg.startupScan = doc["startupScan"] | false;
  cfg.useDHCP = doc["useDHCP"] | true;
  cfg.IPAddress = doc["IPAddress"] | "192.168.1.10";
  file1.close();
}

void saveConfiguration() {
  Serial.println("");

#if!defined(USE_SDCARD)
  Serial.println("saveConfiguration FLASHMEM");
  flashStorage.remove(cfgfilename);
  File file1 = flashStorage.open(cfgfilename, FILE_WRITE);
#else
  Serial.println("saveConfiguration SDCARD");
  SD.remove(cfgfilename);
  File file1 = SD.open(cfgfilename, FILE_WRITE);
#endif

  if (!file1) {
    Serial.println("");
    Serial.print(F("Failed to create file "));
    Serial.println(cfgfilename);
    return;
  } else {
    Serial.println("");
    Serial.print("Created File ");
    Serial.println(cfgfilename);
  }
  StaticJsonDocument < 256 > doc;
  doc["enableBeep"] = cfg.enableBeep;
  doc["startupScan"] = cfg.startupScan;
  doc["useDHCP"] = cfg.useDHCP;
  doc["IPAddress"] = cfg.IPAddress;

  if (serializeJson(doc, file1) == 0) {
    Serial.println("");
    Serial.print(F("Failed to write file "));
    Serial.println(cfgfilename);
  }
  file1.close();
}

/******* PID File Configuration Section *******/

const char * pidsfilename = "pids.txt";

void loadPIDSfile() {
  ClearBlocks();
  Serial.println("");

#if!defined(USE_SDCARD)
  File file1 = flashStorage.open(pidsfilename);
#else
  File file1 = SD.open(pidsfilename);
#endif

  StaticJsonDocument < pidfilesize > doc;
  DeserializationError error = deserializeJson(doc, file1);

  if (error) {
    Serial.println("");
    Serial.print(F("Failed to open file "));
    Serial.println(pidsfilename);
    return;
  } else {
    Serial.println("");
    Serial.print(F("File opened "));
    Serial.println(pidsfilename);
  }

  for (JsonObject pids_item : doc["pids"].as < JsonArray > ()) {
    const char * pids_item_guid = pids_item["guid"]; // "12e56326-f969-4661-ae59-258cb349ae48", ...
    bool pids_item_selected = pids_item["selected"]; // true, true, false, true
    bool pids_item_fake = pids_item["fake"];
    bool pids_item_duplicate = pids_item["duplicate"];
    int pids_item_dupeIndex = pids_item["dupeIndex"];
    bool pids_item_view = pids_item["view"];

    for (int idx = 0; idx < fPIDS.size(); idx++) {
      //  Serial.println(fPIDS.at(idx)._guid);
      if (fPIDS.at(idx)._guid == pids_item_guid) {
        fPIDS.at(idx)._selected = pids_item_selected;
        if (pids_item_selected == true) {
          sPIDS.push_back(fPIDS.at(idx));
          int x = sPIDS.size() - 1;
          sPIDS.at(x)._fake = pids_item_fake;
          sPIDS.at(x)._duplicate = pids_item_duplicate;
          sPIDS.at(x)._dupeIndex = pids_item_dupeIndex;
          sPIDS.at(x)._view = pids_item_view;
          BuildPIDS();
        }
      }
    }
  }

  printPIDS();
  BuildPIDS();
  PopulateGrid();

  /*

    // repair PIDS
    for (int idx = 0; idx < fPIDS.size(); idx++) {
    byte plen = 0;
    String PID = "";
    plen = fPIDS.at(idx)._PID.length();
    switch (plen) {
    case 3: {
      PID = "0";
      PID.concat(fPIDS.at(idx)._PID);
      fPIDS.at(idx)._PID = PID;
      break;
    }
    case 2: {
      PID = "00";
      PID.concat(fPIDS.at(idx)._PID);
      fPIDS.at(idx)._PID = PID;
      break;
    }
    case 1: {
      PID = "000";
      PID.concat(fPIDS.at(idx)._PID);
      fPIDS.at(idx)._PID = PID;
      break;
    }
    default:
      break;
    }
    }
  */
//  serializeJsonPretty(doc, Serial);
  file1.close();
}

void savePIDSfile() {
  Serial.println("");

#if!defined(USE_SDCARD)
  flashStorage.remove(pidsfilename);
  File file1 = flashStorage.open(pidsfilename, FILE_WRITE);
#else
  SD.remove(pidsfilename);
  File file1 = SD.open(pidsfilename, FILE_WRITE);
#endif

  if (!file1) {
    Serial.println("");
    Serial.print(F("Failed to create file "));
    Serial.println(pidsfilename);
    return;
  } else {
    Serial.println("");
    Serial.print("Created File ");
    Serial.println(pidsfilename);
  }

  StaticJsonDocument < pidfilesize > doc; // 32k memory alloc for PID storage

  JsonArray pids = doc.createNestedArray("pids");

  for (int idx = 0; idx < sPIDS.size(); idx++) {
    JsonObject piddata = pids.createNestedObject();
    if (sPIDS.at(idx)._guid != "") {
      piddata["guid"] = sPIDS.at(idx)._guid;
      piddata["selected"] = sPIDS.at(idx)._selected;
      piddata["fake"] = sPIDS.at(idx)._fake;
      piddata["duplicate"] = sPIDS.at(idx)._duplicate;
      piddata["dupeIndex"] = sPIDS.at(idx)._dupeIndex;
      piddata["view"] = sPIDS.at(idx)._view;
    }
  }

//  serializeJsonPretty(doc, Serial);

  if (serializeJsonPretty(doc, file1) == 0) {
    Serial.println("");
    Serial.print(F("Failed to write file "));
    Serial.println(pidsfilename);

  }
  file1.close();
}

void toggleDHCP() {
  cfg.useDHCP = editYesNo(cfg.useDHCP);
  saveConfiguration();
}
