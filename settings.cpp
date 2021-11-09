/*
   Settings
   Contains SD card support
   Loading/Saving of files in JSON Format
*/

#include "settings.h"

const int8_t DISABLE_CS_PIN = -1;
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif  // SDCARD_SS_PIN
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16))
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SD_SCK_MHZ(16))
#endif  // HAS_SDIO_CLASS

SdFs sd;
cid_t m_cid;
csd_t m_csd;
uint32_t m_eraseSize;
uint32_t m_ocr;
static ArduinoOutStream cout(Serial);
const int pidfilesize = 32768; // allocate 32k of ram for PID file

bool cidDmp() {
  cout << F("\nManufacturer ID: ");
  cout << uppercase << showbase << hex << int(m_cid.mid) << dec << endl;
  cout << F("OEM ID: ") << m_cid.oid[0] << m_cid.oid[1] << endl;
  cout << F("Product: ");
  for (uint8_t i = 0; i < 5; i++) {
    cout << m_cid.pnm[i];
  }
  cout << F("\nVersion: ");
  cout << int(m_cid.prv_n) << '.' << int(m_cid.prv_m) << endl;
  cout << F("Serial number: ") << hex << m_cid.psn << dec << endl;
  cout << F("Manufacturing date: ");
  cout << int(m_cid.mdt_month) << '/';
  cout << (2000 + m_cid.mdt_year_low + 10 * m_cid.mdt_year_high) << endl;
  cout << endl;
  return true;
}

void clearSerialInput() {
  uint32_t m = micros();
  do {
    if (Serial.read() >= 0) {
      m = micros();
    }
  } while (micros() - m < 10000);
}

bool csdDmp() {
  bool eraseSingleBlock;
  if (m_csd.v1.csd_ver == 0) {
    eraseSingleBlock = m_csd.v1.erase_blk_en;
    m_eraseSize = (m_csd.v1.sector_size_high << 1) | m_csd.v1.sector_size_low;
  } else if (m_csd.v2.csd_ver == 1) {
    eraseSingleBlock = m_csd.v2.erase_blk_en;
    m_eraseSize = (m_csd.v2.sector_size_high << 1) | m_csd.v2.sector_size_low;
  } else {
    cout << F("m_csd version error\n");
    return false;
  }
  m_eraseSize++;
  cout << F("cardSize: ") << 0.000512 * sdCardCapacity(&m_csd);
  cout << F(" MB (MB = 1,000,000 bytes)\n");

  cout << F("flashEraseSize: ") << int(m_eraseSize) << F(" blocks\n");
  cout << F("eraseSingleBlock: ");
  if (eraseSingleBlock) {
    cout << F("true\n");
  } else {
    cout << F("false\n");
  }
  return true;
}

void errorPrint() {
  if (sd.sdErrorCode()) {
    cout << F("SD errorCode: ") << hex << showbase;
    printSdErrorSymbol(&Serial, sd.sdErrorCode());
    cout << F(" = ") << int(sd.sdErrorCode()) << endl;
    cout << F("SD errorData = ") << int(sd.sdErrorData()) << endl;
  }
}

bool mbrDmp() {
  MbrSector_t mbr;
  bool valid = true;
  if (!sd.card()->readSector(0, (uint8_t*)&mbr)) {
    cout << F("\nread MBR failed.\n");
    errorPrint();
    return false;
  }
  cout << F("\nSD Partition Table\n");
  cout << F("part,boot,bgnCHS[3],type,endCHS[3],start,length\n");
  for (uint8_t ip = 1; ip < 5; ip++) {
    MbrPart_t *pt = &mbr.part[ip - 1];
    if ((pt->boot != 0 && pt->boot != 0X80) ||
        getLe32(pt->relativeSectors) > sdCardCapacity(&m_csd)) {
      valid = false;
    }
    cout << int(ip) << ',' << uppercase << showbase << hex;
    cout << int(pt->boot) << ',';
    for (int i = 0; i < 3; i++ ) {
      cout << int(pt->beginCHS[i]) << ',';
    }
    cout << int(pt->type) << ',';
    for (int i = 0; i < 3; i++ ) {
      cout << int(pt->endCHS[i]) << ',';
    }
    cout << dec << getLe32(pt->relativeSectors) << ',';
    cout << getLe32(pt->totalSectors) << endl;
  }
  if (!valid) {
    cout << F("\nMBR not valid, assuming Super Floppy format.\n");
  }
  return true;
}


void dmpVol() {
  cout << F("\nScanning FAT, please wait.\n");
  uint32_t freeClusterCount = sd.freeClusterCount();
  if (sd.fatType() <= 32) {
    cout << F("\nVolume is FAT") << int(sd.fatType()) << endl;
  } else {
    cout << F("\nVolume is exFAT\n");
  }
  cout << F("sectorsPerCluster: ") << sd.sectorsPerCluster() << endl;
  cout << F("clusterCount:      ") << sd.clusterCount() << endl;
  cout << F("freeClusterCount:  ") << freeClusterCount << endl;
  cout << F("fatStartSector:    ") << sd.fatStartSector() << endl;
  cout << F("dataStartSector:   ") << sd.dataStartSector() << endl;
  if (sd.dataStartSector() % m_eraseSize) {
    cout << F("Data area is not aligned on flash erase boundary!\n");
    cout << F("Download and use formatter from www.sdcard.org!\n");
  }
}

void printCardType() {
  cout << F("\nCard type: ");
  switch (sd.card()->type()) {
    case SD_CARD_TYPE_SD1:
      cout << F("SD1\n");
      break;
    case SD_CARD_TYPE_SD2:
      cout << F("SD2\n");
      break;
    case SD_CARD_TYPE_SDHC:
      if (sdCardCapacity(&m_csd) < 70000000) {
        cout << F("SDHC\n");
      } else {
        cout << F("SDXC\n");
      }
      break;
    default:
      cout << F("Unknown\n");
  }
}

void printConfig(SdSpiConfig config) {
  if (DISABLE_CS_PIN < 0) {
    cout << F(
           "\nAssuming the SD is the only SPI device.\n"
           "Edit DISABLE_CS_PIN to disable an SPI device.\n");
  } else {
    cout << F("\nDisabling SPI device on pin ");
    cout << int(DISABLE_CS_PIN) << endl;
    pinMode(DISABLE_CS_PIN, OUTPUT);
    digitalWrite(DISABLE_CS_PIN, HIGH);
  }
  cout << F("\nAssuming the SD chip select pin is: ") << int(config.csPin);
  cout << F("\nEdit SD_CS_PIN to change the SD chip select pin.\n");
}

void printConfig(SdioConfig config) {
  (void)config;
  cout << F("Assuming an SDIO interface.\n");
}

void SDinit(bool showStartup)
{ // Read any existing Serial data.
  // F stores strings in flash to save RAM

  if (showStartup) {
    printStage("SD Card Startup");
  }

  cout << F("\ntype any character to start\n");
  uint32_t t = millis();
  if (!sd.cardBegin(SD_CONFIG)) {
    cout << F(
           "\nSD initialization failed.\n"
           "Do not reformat the card!\n"
           "Is the card correctly inserted?\n"
           "Is there a wiring/soldering problem?\n");
    if (isSpi(SD_CONFIG)) {
      cout << F(
             "Is SD_CS_PIN set to the correct value?\n"
             "Does another SPI device need to be disabled?\n"
           );
    }
    errorPrint();

    if (showStartup) {
      printStage("SD Card Fail Init");
    }

    return;
  }
  t = millis() - t;
  cout << F("init time: ") << t << " ms" << endl;

  if (!sd.card()->readCID(&m_cid) ||
      !sd.card()->readCSD(&m_csd) ||
      !sd.card()->readOCR(&m_ocr)) {
    cout << F("readInfo failed\n");
    errorPrint();
    if (showStartup) {
      printStage("SD Read Info Failed");
    }
    return;
  }
  printCardType();
  cidDmp();
  csdDmp();
  cout << F("\nOCR: ") << uppercase << showbase;
  cout << hex << m_ocr << dec << endl;
  if (!mbrDmp()) {
    return;
  }
  if (!sd.volumeBegin()) {
    cout << F("\nvolumeBegin failed. Is the card formatted?\n");
    errorPrint();
    if (showStartup) {
      printStage("SD Not Formatted?");
    }
    return;
  }
  dmpVol();

  if (showStartup) {
    printStage("");
  }
}
/******* Configuration Section *******/

const char *filename = "/config.txt";
EXTMEM scanConfig cfg;

void loadConfiguration() {
  printStage("Loading config.txt");
  FsFile file1 = sd.open(filename);
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, file1);

  if (error)
  {
    Serial.print(F("Failed to read file, using default configuration"));
    printStage("Read config.txt");
    delay(500);
    printStage("Using Defaults");
    delay(2500);
  }
  cfg.enableBeep = doc["enableBeep"] | false;
  cfg.startupScan = doc["startupScan"] | false;
  cfg.useDHCP = doc["useDHCP"] | true;
  cfg.IPAddress = doc["IPAddress"] | "192.168.1.10";
  file1.close();
}

void saveConfiguration() {
  sd.remove(filename);
  FsFile file1 = sd.open(filename, FILE_WRITE);
  if (!file1) {
    Serial.print(F("Failed to create file"));
    Serial.println(filename);
    return;
  }
  StaticJsonDocument<256> doc;
  doc["enableBeep"] = cfg.enableBeep;
  doc["startupScan"] = cfg.startupScan;
  doc["useDHCP"] = cfg.useDHCP;
  doc["IPAddress"] = cfg.IPAddress;

  if (serializeJson(doc, file1) == 0) {
    Serial.println(F("Failed to write to file"));
  }
  file1.close();
}

/******* PID File Configuration Section *******/

const char *pidsfilename = "/pids.txt";

void loadPIDSfile() {

  pidCounter = 0;
  FsFile file1 = sd.open(pidsfilename);
  StaticJsonDocument<pidfilesize> doc;
  DeserializationError error = deserializeJson(doc, file1);
  if (error) {
    Serial.print(F("Failed to read file, using default configuration"));
    Serial.println(pidsfilename);
    return;
  }
  
  for (JsonObject pids_item : doc["pids"].as<JsonArray>()) {
    const char* pids_item_guid = pids_item["guid"]; // "12e56326-f969-4661-ae59-258cb349ae48", ...
    bool pids_item_selected = pids_item["selected"]; // true, true, false, true
    for (int idx = 0; idx < NUM_PIDS; idx++) {
      if (PIDS[idx]._guid == pids_item_guid) {
        PIDS[idx]._selected = pids_item_selected;
        if (pids_item_selected == true) {
          pidCounter = pidCounter + PIDS[idx]._len;
        }
      }
    }
  }

// repair PIDS 
  for (int idx = 0; idx < NUM_PIDS; idx++) {
    byte plen = 0;
    String PID = "";
    plen = PIDS[idx]._PID.length();
    switch (plen) {
      case 3: {
          PID = "0";
          PID.concat(PIDS[idx]._PID);
          PIDS[idx]._PID = PID;
          break;
        }
      case 2: {
          PID = "00";
          PID.concat(PIDS[idx]._PID);
          PIDS[idx]._PID = PID;
          break;
        }
      case 1: {
          PID = "000";
          PID.concat(PIDS[idx]._PID);
          PIDS[idx]._PID = PID;
          break;
        }
      default: break;
    }
  }
  file1.close();
}

void savePIDSfile() {
  sd.remove(pidsfilename);
  FsFile file1 = sd.open(pidsfilename, FILE_WRITE);
  if (!file1) {
    Serial.print(F("Failed to create file"));
    Serial.println(pidsfilename);
    return;
  }
  StaticJsonDocument<pidfilesize> doc; // 32k memory alloc for PID storage
  JsonArray pids = doc.createNestedArray("pids");
  for (int idx = 0; idx < NUM_PIDS; idx++) {
    JsonObject piddata = pids.createNestedObject();
    if (PIDS[idx]._guid != "") {
      piddata["guid"] = PIDS[idx]._guid;
      piddata["selected"] = PIDS[idx]._selected;
    }
  }
  if (serializeJsonPretty(doc, file1) == 0) {
    Serial.println(F("Failed to write to file"));
  }
  file1.close();
}
void toggleDHCP() {
  cfg.useDHCP = editYesNo(cfg.useDHCP);
  saveConfiguration();
}
