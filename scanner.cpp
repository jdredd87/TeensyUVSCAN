#include "scanner.h"

String CurrentLogFileName = "";

File logFile;
int lastblock;
int maxShow;
int lineCount;
String inData;

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
    send3("2A13FE000000");
  } else if (lastblock == 253) {
    send3("2A13FEFD0000");
  } else

    if (lastblock == 252) {
      send3("2A13FEFDFC00");
    } else

      if (lastblock == 251) {
        send3("2A13FEFDFCFB");
      } else

        if (lastblock == 250) {
          send3("2A13FEFDFCFB");
          send3("2A13FA000000");
        } else

          if (lastblock == 249) {
            send3("2A13FEFDFCFB");
            send3("2A13FAF90000");
          } else

            if (lastblock == 248) {
              send3("2A13FEFDFCFB");
              send3("2A13FAF9F800");
            } else if (lastblock == 247) {
              send3("2A13FEFDFCFB");
              send3("2A13FAF9F8F7");
            }
}

String calculate(String formula, float n1, float n2, float n3, float n4) {

  //Serial.print("Formula = ");  Serial.println(formula);
  //Serial.print("N1 = "); Serial.println(n1);
  //Serial.print("N2 = "); Serial.println(n2);


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

bool processData() {

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

  Serial.print("<< ");  Serial.println(inData);

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
  //Serial.print(">>> "); Serial.println(inData);
  //Serial.println(str);  Serial.println(blockID, DEC);

  // look for pids that match this block
  for (int idx = 0; idx < sPIDS.size(); idx++) {

    if (sPIDS.at(idx)._duplicate) {
      continue;
    }

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


  if (blockID == lastblock)
  {
    return true;
  } else
  {
    return false;
  }
}


bool writeLog(bool Header) {

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
      if (sPIDS.at(idx)._value == "") return false; // if we had blank data, such as first line usually scanned, just jump out.
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


  return true;
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
  int len;
  String line;
  for (int idx = 0; idx < sPIDS.size(); idx++) {
    if (sPIDS.at(idx)._view) {
      Serial.print(sPIDS.at(idx)._PID);
      Serial.print(" - ");
      Serial.println(sPIDS.at(idx)._name);
      line = sPIDS.at(idx)._shortname;
      line.concat(" > ");
      line.concat(sPIDS.at(idx)._value);
      len = 20 - line.length();
      if (line.length() < 20) {
        for (int idx = 0; idx < len; idx++) {
          line.concat(" "); // we want to pad string so its always 20 chars long, so it clears line basically
        }
      }
      lcd.setCursor(0, row);
      lcd.print(line);
      row++;
    }
  }
}

void startScanner() {


  serial_flush();
  Serial1.flush();

  unsigned long KeepAlive_starttime;
  unsigned long KeepAlive_checktime;
  unsigned long KeepAlive_elapsedtime;
  String R;
  char buffer[32];
  char c;
  int irV;
  char fn[64];

  lineCount = 0;
  inData = "";

  GenerateFileName();
  CurrentLogFileName.toCharArray(fn, CurrentLogFileName.length() + 1);

  SD.mkdir("logs");
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

  initSTNScanner();
  printPIDS();
  BuildPIDS();
  PopulateGrid();

  for (int x = 0; x < sPIDS.size(); x++) {
    if (sPIDS.at(x)._CMD != "") {
      String buff = "";

      buff = "Sending PID # ";
      buff.concat(x + 1);
      printStage(buff);
      //sprintf(buffer, "Sending PID # %d", (x + 1) );
      //printStage(buffer);
      R = send(sPIDS.at(x)._CMD, 1000);
      if (R.length() != 6)
      {
        beepLong();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Failed to send pid!");
        delay(5000);
        return;
      }
    }
  }

  printStage("STPTO");  send("STPTO 400", 1110);
  printStage("STPTOT"); send("STPTOT 400", 1110);
  printStage("ADAPTIVE_TIMING_OFF");  send(ADAPTIVE_TIMING_OFF, 1000);

  lastblock = currentBlock;

  activateblocks();

  lcd.clear();

  KeepAlive_starttime = millis();

  setupViewer();

  writeLog(true);

  while (1) {

    if (ir.available()) { // check IR sensor for input
      irV = ir.readPacket();
      if (irV == hexSTAR) { // * key = abort
        break;
      }
    }

    if (Serial1.available()) {
      c = Serial1.read();
      if (c == char(10) or c == char(13))
      {
        inData.replace(char(10), "");
        inData.replace(char(13), "");

        if (inData.length() == 0) { // if 0 byte, just move on
          // Serial.print("<< "); Serial.print(inData); Serial.println(" << Zero length data");
          inData = "";
          continue;
        }

        if (inData.length() != 16) { // if 0 byte, just move on
          // Serial.print("<< ");          Serial.print(inData);          Serial.print(" << Not 16 byte length << ");          Serial.println(inData.length());
          inData = "";
          continue;
        }

        if (!inData.startsWith("6A")) {
          // Serial.print("<< ");          Serial.print(inData);          Serial.println(" << Not 6Axxx packet");
          inData = "";
          continue; // if anything but 6A, then just move on too
        }

        if (processData())
        {
          if (writeLog(false)) {
            lineCount++;
            Serial.println(lineCount);
            showScanner();
            // ok we logged our data, wipe out everything for this block
            for (int idx = 0; idx < sPIDS.size(); idx++) {
              sPIDS.at(idx)._lastvalue = sPIDS.at(idx)._value;
              sPIDS.at(idx)._value = "";
            }
          }
        }

        inData = "";
      }
      else
      {
        inData.concat(c);
      }

    }

    KeepAlive_checktime = millis();
    KeepAlive_elapsedtime = KeepAlive_checktime - KeepAlive_starttime;

    if (KeepAlive_elapsedtime >= 2500) {
      send4("", 50); // force the STN to stop
      delay(50);
      send4("3F", 50); // 3F to keep PCM dumping data
      KeepAlive_starttime = millis(); // reset clock
      //threads.yield();
    }
    delay(1);
  }

  // user exited so back to menu interface!
  CurrentLogFileName = "";
  if (logFile) {
    logFile.close();
  }

  beep();

  // lets make sure we finish off any incoming data
  // probably over kill but wanna make sure buffers are clear.

  serial_flush();
  Serial1.flush();
  int abort = 0;
  while (1) {
    if (Serial1.available())
    {
      char c = Serial1.read();
    } else
    {
      delay(1);
      abort++;
    }
    if (abort > 1000) {
      break;
    }
  }

}

void togglestartupScan() {
  cfg.startupScan = editYesNo(cfg.startupScan);
  saveConfiguration();
}
