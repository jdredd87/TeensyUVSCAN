#include "scanner.h"

String CurrentLogFileName = "";

File logFile;
int lastblock;
int maxShow;

void GenerateFileName() {
  time_t t = now();
  CurrentLogFileName = "/logs/";
  CurrentLogFileName.concat(month());
  CurrentLogFileName.concat("-");
  CurrentLogFileName.concat(day());
  CurrentLogFileName.concat("-");
  CurrentLogFileName.concat(year());
  CurrentLogFileName.concat(" ");
  CurrentLogFileName.concat(hour());
  CurrentLogFileName.concat("-");
  CurrentLogFileName.concat(minute());
  CurrentLogFileName.concat("-");
  CurrentLogFileName.concat(second());
  CurrentLogFileName.concat(".csv");
}

void activateblocks() {
  printStage("activateblocks");
  if (lastblock == 254) {
    send("2A13FE000000", 1000);
  } else if (lastblock == 253) {
    send("2A13FEFD0000", 1000);
  } else

    if (lastblock == 252) {
      send("2A13FEFDFC00", 1000);
    } else

      if (lastblock == 251) {
        send("2A13FEFDFCFB", 1000);
      } else

        if (lastblock == 250) {
          send("2A13FEFDFCFB", 1000);
          send("2A13FA000000", 1000);
        } else

          if (lastblock == 249) {
            send("2A13FEFDFCFB", 1000);
            send("2A13FAF90000", 1000);
          } else

            if (lastblock == 248) {
              send("2A13FEFDFCFB", 1000);
              send("2A13FAF9F800", 1000);
            } else if (lastblock == 247) {
              send("2A13FEFDFCFB", 1000);
              send("2A13FAF9F8F7", 1000);
            }
}

String calculate(String formula, float n1, float n2, float n3, float n4) {
  formula.toUpperCase();
  //Serial.print("Original Formula : ");
  //Serial.println(formula);
  formula.replace("N0", n1); // n0 and n1 are the same
  formula.replace("N1", n1);
  formula.replace("N2", n2);
  formula.replace("N3", n2);
  formula.replace("N4", n4);
  // Serial.print("Variables filled in Formula : "); Serial.println(formula);
  char f[255];
  formula.toCharArray(f, 255);
  double value = parse_expression(f);
  return String(value, 2);
}

bool processData(String inData) {

  int blockID;

  String str;

  String v1;
  String v2;
  String v3;
  String v4;

  double n1;
  double n2;
  double n3;
  double n4;

  if (inData.length() == 16) {
    if (inData.startsWith("6A") == true) { // length good, and 6A starts
      inData.replace(" ", "");
      inData.trim();
      inData.remove(0, 2); // delete 6A
      str = inData.substring(0, 2); // FE, FD, FC, ect
      if (str == "FE") blockID = 254;
      if (str == "FD") blockID = 253;
      if (str == "FC") blockID = 252;
      if (str == "FB") blockID = 250;
      if (str == "FA") blockID = 251;
      if (str == "F9") blockID = 250;
      if (str == "F8") blockID = 249;
      if (str == "F7") blockID = 248;
      inData.remove(0, 2); // Delte FE
      //Serial.print("inData Packet ID = ");      Serial.print(blockID, HEX);      Serial.print(" , data = ");      Serial.println(inData);

      // look for pids that match this block
      for (int idx = 0; idx < sPIDS.size(); idx++) {
        if (sPIDS.at(idx)._duplicate) continue;
        if (sPIDS.at(idx)._blockID == blockID) {

          v1 = "";
          v2 = "";
          v3 = "";
          v4 = "";

          n1 = 0;
          n2 = 0;
          n3 = 0;
          n4 = 0;

          int bPOS = sPIDS.at(idx)._blockPOS;

          switch (bPOS) {
            case 0:
              bPOS = 0;
              break;
            case 1:
              bPOS = 2;
              break;
            case 2:
              bPOS = 4;
              break;
            case 3:
              bPOS = 6;
              break;
            case 4:
              bPOS = 8;
              break;
            case 5:
              bPOS = 10;
              break;
          }

          switch (sPIDS.at(idx)._len) {
            case 1: {
                v1 = inData.substring(bPOS, bPOS + 2); // 00
                n1 = StrToInt(v1);
                break;
              }
            case 2: {
                v1 = inData.substring(bPOS, bPOS + 2); // 00
                v2 = inData.substring(bPOS + 2, bPOS + 4); // 00
                n1 = StrToInt(v1);
                n2 = StrToInt(v2);
                break;
              }
            case 4: {
                v1 = inData.substring(bPOS, bPOS + 2); // 00
                v2 = inData.substring(bPOS + 2, bPOS + 4); // 0001
                v3 = inData.substring(bPOS + 4, bPOS + 6); // 00
                v4 = inData.substring(bPOS + 6, bPOS + 8); // 00

                n1 = StrToInt(v1);
                n2 = StrToInt(v2);
                n3 = StrToInt(v3);
                n4 = StrToInt(v4);
                break;
              }
          }
          //Serial.print(sPIDS.at(idx)._name);
          //Serial.print(" -> ");
          sPIDS.at(idx)._value = calculate(sPIDS.at(idx)._formula, n1, n2, n3, n4);

          for (int dIDX = 0; dIDX < sPIDS.size(); dIDX++)
          {
            if (dIDX == idx) continue; // skip cause we just did it above
            if (sPIDS.at(dIDX)._PID == sPIDS.at(idx)._PID and sPIDS.at(dIDX)._duplicate == true) {
              sPIDS.at(dIDX)._value = calculate(sPIDS.at(dIDX)._formula, n1, n2, n3, n4);
            }
          }
        }
      }
    }
  }

  if (blockID == lastblock)
  {
    return true;
  } else
  {
    return false;
  }
}


void writeLog(bool Header) {

  int state;
  String DataLine = "";

  //weblock.lock(500);

  if (Header) { // only write the header
    for (int idx = 0; idx < sPIDS.size(); idx++) {
      if (idx == 0)
      {
        DataLine = sPIDS.at(idx)._shortname;
      } else {
        DataLine.concat(',');
        DataLine.concat(sPIDS.at(idx)._shortname);
      }
    }
  } else
  {
    for (int idx = 0; idx < sPIDS.size(); idx++) {
      if (sPIDS.at(idx)._value == "") return; // if we had blank data, such as first line usually scanned, just jump out.

      if (idx == 0)
      {
        DataLine = sPIDS.at(idx)._value;
      } else {
        DataLine.concat(',');
        DataLine.concat(sPIDS.at(idx)._value);
      }
    }
  }

  if (logFile) {
    logFile.println(DataLine);
    //Serial.println(DataLine);
  }

  // ok we logged our data, wipe out everything for this block
  for (int idx = 0; idx < sPIDS.size(); idx++) {
    sPIDS.at(idx)._lastvalue = sPIDS.at(idx)._value;
    sPIDS.at(idx)._value = "";

  }
  delay(1);
  //weblock.unlock();
}

void setupViewer() {
  // if not selected, pick first 4
  int count = 0;

  for (int idx = 0; idx < sPIDS.size(); idx++) {
    if (sPIDS.at(idx)._view) {
      count++;
      if (count >= 5) return; // don't need to bother
    }
  }

  if ( count == 0) {
    Serial.println("Zero pids selected for viewer, so selecting for first four.... ");
    for (int idx = 0; idx < sPIDS.size(); idx++)
    {
      sPIDS.at(idx)._view = true;
      count++;
      if (count >= 5) return; // don't need to bother
    }
  }

  maxShow = 0;
  for (int idx = 0; idx < sPIDS.size(); idx++) {
    if (sPIDS.at(idx)._view) {
      maxShow ++;
    }
  }


}

void showScanner() {
  int row = 0;
  for (int idx = 0; idx < sPIDS.size(); idx++) {
    if (sPIDS.at(idx)._view) {
      //lcd.setCursor(0, row);
      //lcd.print("                    ");

      lcd.setCursor(0, row);
      lcd.print(sPIDS.at(idx)._shortname);
      lcd.print(" > "); lcd.print("                    ");
      lcd.setCursor(sPIDS.at(idx)._shortname.length() + 3, row);
      lcd.print(sPIDS.at(idx)._value);
      //Serial.print(sPIDS.at(idx)._shortname);
      //Serial.print(" > ");
      //Serial.println(sPIDS.at(idx)._value);
      row++;
    }
    if (row >= 4) return; // don't need to bother
    if (idx > maxShow) return;
  }
}

void startScanner() {
  unsigned long

  KeepAlive_starttime,
  KeepAlive_checktime,
  KeepAlive_elapsedtime;


  char buffer[32];
  initSTNScanner();
  printPIDS();
  BuildPIDS();
  PopulateGrid();

  for (int x = 0; x < sPIDS.size(); x++) {
    if (sPIDS.at(x)._CMD != "") {
      sprintf(buffer, "Sending PID # %d", (x + 1) );
      printStage(buffer);
      send(sPIDS.at(x)._CMD, 1000);
      delay(250);
    }
  }

  delay(250);
  lastblock = currentBlock;
  activateblocks();
  lcd.clear();
  delay(100);
  KeepAlive_starttime = millis();
  String inData = "";
  int irV;
  GenerateFileName();
  char fn[64];
  CurrentLogFileName.toCharArray(fn, CurrentLogFileName.length() + 1);

  logFile = SD.open(fn, FILE_WRITE);

  if (!logFile) {
    Serial.println("");
    Serial.print(F("Failed to create file "));
    Serial.println(fn);
    return;
  } else {
    Serial.println("");
    Serial.print("Created File ");
    Serial.println(fn);
  }

  setupViewer();
  writeLog(true);

  while (1) {
    if (ir.available()) { // check IR sensor for input
      irV = ir.readPacket();
      if (irV == hexSTAR) { // * key = abort
        break;
      }
    }
    else if (Serial1.available())
    {
      char c = Serial1.read();

      if (c == char(10) or c == char(13))
      {
        inData.replace(char(10), "");
        inData.replace(char(13), "");
        Serial.println(inData);
        if (processData(inData))
        {

          showScanner();
          writeLog(false);
        }

        inData = "";
      }
      else
      {
        inData.concat(c);
      }
    } else
    {
      // serverloop();
    }

    KeepAlive_checktime = millis();
    KeepAlive_elapsedtime = KeepAlive_checktime - KeepAlive_starttime;

    if (KeepAlive_elapsedtime >= 2500) {
      send("", 50); // force the STN to stop
      delay(50);
      send("3F", 50); // 3F to keep PCM dumping data
      KeepAlive_starttime = millis(); // reset clock
      threads.yield();
    }
  }
  // user exited so back to menu interface!
  CurrentLogFileName = "";
  if (logFile) {
    logFile.close();
  }  printMenu();
}

void togglestartupScan() {
  cfg.startupScan = editYesNo(cfg.startupScan);
  saveConfiguration();
}
