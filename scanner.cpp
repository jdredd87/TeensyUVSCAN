#include "scanner.h"
#include "settings.h"
#include "menus.h"
#include "comm.h"
#include "pids.h"

void activateblocks(int lastblock)
{
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


String calculate(String formula, float n1, float n2, float n3, float n4)
{
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
  return  String(value, 2);
}

void processData(String inData)
{
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

          switch (bPOS)
          {
            case 0: bPOS = 0; break;
            case 1: bPOS = 2; break;
            case 2: bPOS = 4; break;
            case 3: bPOS = 6; break;
            case 4: bPOS = 8; break;
            case 5: bPOS = 10; break;
          }


          switch (sPIDS.at(idx)._len)
          {
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

          // Serial.println("----------------------------------------------------");
          Serial.print(sPIDS.at(idx)._name);
          Serial.print(" -> ");
          //Serial.print("blockPOS = ");
          //Serial.println(bPOS);
          //Serial.print("v1 = "); Serial.println(v1);
          //Serial.print("v2 = "); Serial.println(v2);
          //Serial.print("v3 = "); Serial.println(v3);
          //Serial.print("v4 = "); Serial.println(v4);
          //Serial.println(sPIDS.at(idx)._blockPOS);
          sPIDS.at(idx)._value = calculate(sPIDS.at(idx)._formula, n1, n2, n3, n4);
          // Serial.print("Result = ");
          Serial.println(sPIDS.at(idx)._value);
          // Serial.println("");
        }
      }
    }
  }
}

void startScanner() {
  send("ATZ", 1000);
  send("ATE0", 1000);
  send("ATL1", 1000);
  send("ATAL", 1000);
  send("ATS0", 1000);
  send("ATH0", 1000);
  send("ATAT0", 1000);
  send("STDI", 1000);
  send("STI", 1000);
  send("ATI", 1000);
  //send("STDIX", 5000);
  send("010D", 1000); // reset some pcm data asking for pids?
  send("0110", 1000); // reset some pcm data asking for pids?
  send("ATSH6C10F1", 1000); // Make sure header is back
  send("3C01", 1000); // VIN 1
  send("3C02", 1000); // VIN 2
  send("3C03", 1000); // VIN 3
  send("3C0A", 1000); // OSID
  send("3C04", 1000); // PCM HW
  //send("ATSP 2",1000); //
  send("20", 1000); // reset pcm calls maybe?
  send("1000", 1000); // reset some pcm data asking for pids?
  send("0100", 1000); // reset some pcm data asking for pids?
  send("STPTO 1000", 1000); // TIMEOUTS
  send("STPTOT 1000", 1000);
  printPIDS();
  BuildPIDS();
  PopulateGrid();
  for (int x = 0; x < sPIDS.size(); x++) {
    if (sPIDS.at(x)._CMD != "") {
      send(sPIDS.at(x)._CMD, 1000);
      delay(250);
    }
  }
  delay(250);
  activateblocks(currentBlock);
  delay(250);
  activateblocks(currentBlock);
  //Serial.flush();
  //serial_flush();
  delay(250);
  unsigned long starttime, checktime, elapsedtime;
  starttime = millis();
  String inData = "";
  delay(500);
  int irV;
  while (1) {
    delay(1);
    if (ir.available()) { // check IR sensor for input
      irV = ir.readPacket();
      if (irV == hexSTAR) { // * key = abort
        break;
      }
    } else if (Serial1.available()) { // dump out Serial1 input.
      char c = Serial1.read();
      if (c == char(10) or c == char(13)) {
        inData.replace(char(10), "");
        inData.replace(char(13), "");
        // Serial.println(inData);
        processData(inData);
        inData = "";
      } else
      {
        inData.concat(c);
      }
    }
    checktime = millis();
    elapsedtime = checktime - starttime;
    if (elapsedtime >= 2500) {
      send("", 50); // force the STN to stop
      delay(50);
      send("3F", 50); // 3F to keep PCM dumping data
      starttime = millis(); // reset clock
    }
  }
  printMenu();
}


void showScanner() {
}

void togglestartupScan() {
  cfg.startupScan = editYesNo(cfg.startupScan);
  saveConfiguration();
}
