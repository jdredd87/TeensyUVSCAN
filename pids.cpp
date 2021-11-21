/*
   pids
   Paramater ID (PID) Structures
*/

#include "pids.h"

// Push the PID Data to extended RAM
// This keeps regular ram for the Teensy device open.

EXTMEM QList <struct TPID> fPIDS; // fixed PID list. What is loaded on bootup.
EXTMEM QList <struct TPID> sPIDS; // Selected PIDs to scan for.

struct TBlockID {
  int value; // -1 for empty
  String PID; // PID stored
};

TBlockID Blocks[8][6];  // 8 rows $FE to $F7 // 6 bytes per row

byte currentBlock;

int getVIEWcount() {
  int counter = 0;
  for (int idx = 0; idx < sPIDS.size(); idx++) {
    if (sPIDS.at(idx)._view) {
      counter++;
    }
  }
 return counter;
}

int AddPIDItem(TPID item) { // add by item object
  item._view = false;
  fPIDS.push_back(item);
  return fPIDS.size();
}

int AddPIDItem(
  String _name,
  String _shortname,
  String _formula,
  String _unit,
  byte   _len,
  String _PID,
  String _format,
  String _mci,
  bool   _selected,
  String _value,
  bool   _fake,
  bool   _duplicate,
  int    _dupeIndex,
  String _CMD,
  String _guid) {

  TPID pidItem;
  pidItem._name = _name;
  pidItem._shortname = _shortname;
  pidItem._formula = _formula;
  pidItem._unit = _unit;
  pidItem._len = _len;
  pidItem._PID = _PID;
  pidItem._format = _format;
  pidItem._mci = _mci;
  pidItem._selected = _selected;
  pidItem._value = _value;
  pidItem._fake = _fake;
  pidItem._duplicate = _duplicate;
  pidItem._dupeIndex = _dupeIndex;
  pidItem._CMD = _CMD;
  pidItem._guid = _guid;
  pidItem._view = false;
  fPIDS.push_back(pidItem);
  return fPIDS.size();
}


void ClearBlocks() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 6; x++) {
      Blocks[y][x].value = -1;
      Blocks[y][x].PID = "";
    }
  }
}

// Generates A simple grid layout to be able to see what PIDS are where in the blocks to send to the PCM

void PopulateGrid() {
  Serial.println("");
  Serial.println("----------------------------------------------------------------------------");
  for (int y = 0; y < 8; y++) {
    switch (y) {
      case 0:
        Serial.print("$FE | ");
        break;
      case 1:
        Serial.print("$FD | ");
        break;
      case 2:
        Serial.print("$FC | ");
        break;
      case 3:
        Serial.print("$FB | ");
        break;
      case 4:
        Serial.print("$FA | ");
        break;
      case 5:
        Serial.print("$F9 | ");
        break;
      case 6:
        Serial.print("$F8 | ");
        break;
      case 7:
        Serial.print("$F7 | ");
        break;
    }
    for (int x = 0; x < 6; x++) {
      Serial.print(" ");
      if (Blocks[y][x].value > -1) {
        Serial.print(" ");
      }
      Serial.print(Blocks[y][x].value);
      Serial.print("(");
      if (Blocks[y][x].PID == "") {
        Serial.print("----");
      } else {
        Serial.print(Blocks[y][x].PID);
      }
      Serial.print(")");
      Serial.print(" |");
    }
    Serial.println("");
  }
  Serial.println("----------------------------------------------------------------------------");
  Serial.println("");
}

int findspot(byte len, String PID) {
  bool found;
  int PID_Position = -1; // will return this at the end

  for (int by = 0; by < 8; by++) {
    for (int bx = 0; bx < 6; bx++) {
      found = false;

      if (Blocks[by][bx].value == -1) {
        switch (len) {
          case 1: {
              found = true;
              break;
            }
          case 2: {
              if (bx < 5) { // fits 0,1,2,3,4,x
                if (Blocks[by][bx + 1].value == -1) {
                  found = true;
                }
              }
              break;
            }
          case 4: {
              if (bx < 3) { // fits 0,1,2,x,x,x
                if (Blocks[by][bx + 1].value == -1 &&
                    Blocks[by][bx + 2].value == -1 &&
                    Blocks[by][bx + 3].value == -1) {
                  found = true;
                }
              }
              break;
            }
        }

        if (found == true) {
          PID_Position = bx; // 0 based array
          switch (by) {
            case 0: {
                currentBlock = 254;
                break;
              }
            case 1: {
                currentBlock = 253;
                break;
              }
            case 2: {
                currentBlock = 252;
                break;
              }
            case 3: {
                currentBlock = 251;
                break;
              }
            case 4: {
                currentBlock = 250;
                break;
              }
            case 5: {
                currentBlock = 249;
                break;
              }
            case 6: {
                currentBlock = 248;
                break;
              }
            case 7: {
                currentBlock = 247;
                break;
              }
          }

          switch (len) {
            case 1: {
                Blocks[by][bx].value = len;
                Blocks[by][bx].PID = PID;
                break;
              }
            case 2: {
                Blocks[by][bx].value = len;
                Blocks[by][bx].PID = PID;
                Blocks[by][bx + 1].value = len;
                Blocks[by][bx + 1].PID = PID;
                break;
              }
            case 4: {
                Blocks[by][bx].value = len;
                Blocks[by][bx + 1].value = len;
                Blocks[by][bx + 2].value = len;
                Blocks[by][bx + 3].value = len;
                Blocks[by][bx].PID = PID;
                Blocks[by][bx + 1].PID = PID;
                Blocks[by][bx + 2].PID = PID;
                Blocks[by][bx + 3].PID = PID;
                break;
              }
          }
          return PID_Position; // get out of here, we found a spot!
        }
      }
    }
  }

  Serial.print("PID_Position(b) = ");
  Serial.println(PID_Position);

  return PID_Position;
}

String addpid(String PID, byte len, byte PID_Position) {

  /*
    Serial.print(pItem.PID);
    Serial.print("-");
    Serial.print(pItem.len);
    Serial.print("-");
    Serial.println(PID_Position);
  */

  byte count;
  String pidcmd;
  count = 64; // start position in the GM memory for a block
  pidcmd = "";

  if ((1 & len) > 0) {
    count = count + 1;
  }

  if ((2 & len) > 0) {
    count = count + 2;
  }

  if ((4 & len) > 0) {
    count = count + 4;
  }

  if ((1 & (PID_Position + 1)) > 0) {
    count = count + 8;
  }

  if ((2 & (PID_Position + 1)) > 0) {
    count = count + 16;
  }

  if ((4 & (PID_Position + 1)) > 0) {
    count = count + 32;
  }

  //Serial.println(pItem.name); // left side memo, show name
  //                   6C10F1
  //  pidcmd.concat("0A6C10F12C");
  pidcmd.concat("2C");
  pidcmd.concat(ByteToHex(currentBlock));
  pidcmd.concat(ByteToHex(count));
  pidcmd.concat(PID);
  pidcmd.concat("FFFF");

  return pidcmd;
}

bool BuildPIDS() {
  ClearBlocks();
  //currentBlock = 254; // $FE
  int PID_Position = -1;
  Serial.println("");

  for (int idx = 0; idx < sPIDS.size(); idx++) {
    PID_Position = -1;

    if (sPIDS.at(idx)._duplicate == true) {
      Serial.print("Dupe at ");
      Serial.print(idx);
      Serial.print(" PID = ");
      Serial.println(sPIDS.at(idx)._PID);
    } else if (sPIDS.at(idx)._fake == true) {
      Serial.print("Fake at ");
      Serial.print(idx);
      Serial.print(" PID = ");
      Serial.println(sPIDS.at(idx)._PID);
    } else {
      PID_Position = findspot(sPIDS.at(idx)._len, sPIDS.at(idx)._PID);
      Serial.print(idx);
      Serial.print(" - ");
      Serial.print(sPIDS.at(idx)._PID);
      Serial.print(" - ");
      Serial.println(PID_Position);

      if (PID_Position > -1) {
        String CMD = addpid(sPIDS.at(idx)._PID, sPIDS.at(idx)._len, PID_Position);
        sPIDS.at(idx)._CMD = CMD;
        sPIDS.at(idx)._blockID = currentBlock;
        sPIDS.at(idx)._blockPOS = PID_Position;
      } else {
        Serial.print("Removed ");
        Serial.print(idx);
        Serial.print(" ");
        Serial.print(sPIDS.at(idx)._PID);
        return false; // should be only the last item
      }
    }
  }

  return true; // ok it worked it added
  Serial.println("");
  Serial.println("-----------------------------------------------");
}

// Generates the list of selected PIDS and their position / states
void printPIDS() {
  Serial.println("");
  Serial.println("");
  Serial.print("Select PID Count #");
  Serial.println(sPIDS.size());
  Serial.println("");
  Serial.println("-----------------------------------------------");

  for (int x = 0; x < sPIDS.size(); x++) {
    Serial.print(x);
    Serial.print(" - ");
    Serial.print(sPIDS.at(x)._PID);
    Serial.print(" - ");
    Serial.print(sPIDS.at(x)._len);
    Serial.print(" - ");

    if (sPIDS.at(x)._fake == true) {
      Serial.print("Fake User PID ");
      Serial.print(sPIDS.at(x)._PID);
      Serial.print("    ");
    } else

      if (sPIDS.at(x)._duplicate == true) {
        Serial.print("duplicate to index ");
        Serial.print(sPIDS.at(x)._dupeIndex);
        Serial.print("  ");
      } else {
        Serial.print(sPIDS.at(x)._CMD);
      }
    Serial.print("  -  ");
    Serial.println(sPIDS.at(x)._name);
  }
}

void InstallPIDS() {
  TPID pidItem;
  // not sure I like this flavor of having each pid on 1 line. Very hard to read.

  // Idea maybe is to have A "master.pid" file to read from instead? then can just read that JSON file structure
  // and populate fPIDS via that. Then NOTHING has to be hard coded anymore!

  AddPIDItem( "ENGINE SPEED",  "RPM",  "((N1 << 8) +N2) *0.25",  "RPM",  2,  "000C", "", "%RPM%",  false,  "", false,  false,  -1, "", "8aab80aa-86bc-4845-a093-78ffb2ad16c6");
  AddPIDItem( "Injector PW", "IPW",  "(((N1<<8)+N2)/65.535)",  "ms", 2,  "1193", "%f", "%IPW%",  false,  "", false,  false,  -1, "", "bf2a5b80-9a55-4583-80a5-9342683fc1da");
  AddPIDItem( "ECT (ENGINE COOLANT TEMPERATURE)",  "ECT",  "N0-40",  "ºC", 1,  "0005", "", "%ECT%",  false,  "", false,  false,  -1, "", "8c34e085-9aa5-4b2e-a1c1-b905c2a962d4");
  AddPIDItem( "MASS AIR FLOW RAW INPUT FREQUENCY", "MAF",  "((N1 << 8) + N2) / 2.048", "Hz", 2,  "1250", "%f", "%MAF%",  false,  "", false,  false,  -1, "", "ffbb3e60-5694-497a-8e76-3c97993b2f9d");
  AddPIDItem( "SHORT TERM FUEL TRIM BANK 1", "STFT", "(N0-128)/1.28",  "%",  1,  "0006", "%f", "%STF%",  false,  "", false,  false,  -1, "", "a7ae6e3e-34ed-48da-8031-38686d3bb2ed");
  AddPIDItem( "LONG TERM FUEL TRIM BANK 1",  "LTFT", "(N0-128)/1.28",  "%",  1,  "0007", "%f", "%LTF%",  false,  "", false,  false,  -1, "", "8f28352c-6902-4520-a2b0-c6094977543d");
  AddPIDItem( "MAP (kPa)", "MAP(kPa)", "N0", "kPa",  1,  "000B", "", "%MAP%",  false,  "", false,  false,  -1, "", "e15cc0ae-f8e3-44b9-9546-dd93bbdb9d7e");
  AddPIDItem( "VEHICLE SPEED", "MPH",  "N0/1.609", "MPH",  1,  "000D", "%f", "%MPH%",  false,  "", false,  false,  -1, "", "2eb011bb-2e13-475c-8ba4-e1aa632cb602");
  AddPIDItem( "SPARK ADVANCE", "Spark",  "((N0/2) - 64) *",  "Degrees",  1,  "000E", "", "%SPK%",  false,  "", false,  false,  -1, "", "c3cb7b54-b469-4a91-8108-75ea36793ca4");
  AddPIDItem( "INTAKE AIR TEMPERATURE",  "IAT",  "N0-40",  "ºC", 1,  "000F", "", "%IAT%",  false,  "", false,  false,  -1, "", "01fa99de-b9b9-4d3e-9917-84b33eeb9f52");
  AddPIDItem( "TP Angle %",  "TP %", "N0/2.55",  "%",  1,  "0011", "", "%TPS%",  false,  "", false,  false,  -1, "", "59d2572d-deca-4ef9-8cc5-ba4e86084eb8");
  AddPIDItem( "Ignition 1 Voltage",  "IGN V",  "N0/10",  "V",  1,  "1141", "", "%IGV%",  false,  "", false,  false,  -1, "", "c014ff51-cd13-4f8b-8649-5a3fff42967b");
  AddPIDItem( "H02S Sensor 1", "O2", "0.434*N0*10",  "mV", 1,  "1145", "", "%HO1%",  false,  "", false,  false,  -1, "", "adcaf210-fa13-484a-b75d-ea23fc5384db");
  AddPIDItem( "Knock Retard",  "KR", "22.5*N0/256",  "Degrees",  1,  "11A6", "", "%KRS%",  false,  "", false,  false,  -1, "", "9fc93aab-6728-436c-bf86-21b67bbaa280");
  AddPIDItem( "Current Gear",  "Gear", "N0", "", 1,  "199A", "", "%CGS%",  false,  "", false,  false,  -1, "", "f332b968-6e48-45ae-8ddb-42a980937476");
  AddPIDItem( "Misfire Cyl. 6 History",  "Mis6His", "(N1 << 8) + N2", "Count",  2,  "11F9", "", "%MH6%",  false,  "", false,  false,  -1, "", "fc690c1a-bf1c-4257-b1fe-7ff84ae634c4");
  AddPIDItem( "Misfire Cyl. 6 Current",  "Mis6Cur", "N0", "Count",  1,  "11EB", "", "%MC6%",  false,  "", false,  false,  -1, "", "c4883231-98ce-48d4-9b5c-ef7c7f5d8f2f");
  AddPIDItem( "Misfire Cyl. 5 History",  "Mis5His", "(N1 << 8) + N2", "Count",  2,  "11F8", "", "%MH5%",  false,  "", false,  false,  -1, "", "daebe262-e160-47b3-a701-50508c714e73");
  AddPIDItem( "Misfire Cyl. 5 Current",  "Mis5Cur", "N0", "Count",  1,  "11EA", "", "%MC5%",  false,  "", false,  false,  -1, "", "c031f279-9da7-4127-a91b-5f7676b79ef5");
  AddPIDItem( "Misfire Cyl. 4 History",  "Mis4His", "(N1 << 8) + N2", "Count",  2,  "1204", "", "%MH4%",  false,  "", false,  false,  -1, "", "2652dceb-f799-4f23-96a6-372a63a523c0");
  AddPIDItem( "Misfire Cyl. 4 Current",  "Mis4Cur", "N0", "Count",  1,  "1208", "", "%MC4%",  false,  "", false,  false,  -1, "", "a55067cc-279a-4537-a911-2178a88dff6c");
  AddPIDItem( "Misfire Cyl. 3 History",  "Mis3His", "(N1 << 8) + N2", "Count",  2,  "1203", "", "%MH3%",  false,  "", false,  false,  -1, "", "7b4b138c-6c24-4bde-9b55-06f686cd111e");
  AddPIDItem( "Misfire Cyl. 3 Current",  "Mis3Cur", "N0", "Count",  1,  "1207", "", "%MC3%",  false,  "", false,  false,  -1, "", "061a4d5d-89d1-4d46-8c58-b2cc704a5ba0");
  AddPIDItem( "Misfire Cyl. 2 History",  "Mis2His", "(N1 << 8) + N2", "Count",  2,  "1202", "", "%MH2%",  false,  "", false,  false,  -1, "", "ac38524e-ecb8-467e-a44d-f98fc5b90549");
  AddPIDItem( "Misfire Cyl. 2 Current",  "Mis2Cur", "N0", "Count",  1,  "1205", "", "%MC2%",  false,  "", false,  false,  -1, "", "32184d23-901b-41b6-950b-023a2ec83cab");
  AddPIDItem( "Misfire Cyl. 1 History",  "Mis1His", "(N1 << 8) + N2", "Count",  2,  "1201", "", "%MH1%",  false,  "", false,  false,  -1, "", "170196a6-467f-4dca-bd64-d2930b6d2f47");
  AddPIDItem( "Misfire Cyl. 1 Current",  "Mis1Cur", "N0", "Count",  1,  "1206", "", "%MC1%",  false,  "", false,  false,  -1, "", "ca73abd9-5f13-4302-8323-693444374900");
  AddPIDItem( "Fuel Trim Cell",  "FT Cell",  "N0", "", 1,  "1190", "", "%FTC%",  false,  "", false,  false,  -1, "", "46fb70be-acda-432a-972f-b025e88215d6");
  AddPIDItem( "MAF Flow Rate", "MAF(g/s)", "((N1 << 8) + N2) / 100", "g/s",  2,  "0010", "", "%MAFGmPerSec%",  false,  "", false,  false,  -1, "", "70f4a51d-2a15-4304-8b77-24f88d0a5c02");
  AddPIDItem( "AFR (Commanded)", "AFR",  "N0 / 10",  ":1", 1,  "119E", "", "%AFRCommanded%", false,  "", false,  false,  -1, "", "9434baad-40f3-4065-ba1f-1c18f22d5868");
  AddPIDItem( "Last Shift Time", "Shift Time", "N0 / 40",  "Seconds",  1,  "1992", "", "%LST%",  false,  "", false,  false,  -1, "", "ba26df82-1b29-4e90-9d1e-031624790c4e");
  AddPIDItem( "1-2 Shift Time",  "1-2 Time", "N0 / 40",  "Seconds",  1,  "1993", "", "%ST12%", false,  "", false,  false,  -1, "", "def6d735-28a9-4a08-8f88-8fd0f8a3aa16");
  AddPIDItem( "2-3 Shift Time",  "2-3 Time", "N0 / 40",  "Seconds",  1,  "1994", "", "%ST23%", false,  "", false,  false,  -1, "", "7efc4f28-90e7-4681-adbb-261554fe5ff7");
  AddPIDItem( "3-4 Shift Time",  "3-4 Time", "N0 / 40",  "Seconds",  1,  "1995", "", "%ST34%", false,  "", false,  false,  -1, "", "6e72a4d6-c54d-46cb-9b5c-7b9f4ca65edd");
  AddPIDItem( "1-2 Shift Error", "1-2 Error",  "N0 / 40",  "Seconds",  1,  "1997", "", "%SE12%", false,  "", false,  false,  -1, "", "ebce1f27-e727-495f-8244-ee9a00d89aef");
  AddPIDItem( "2-3 Shift Error", "2-3 Error",  "N0 / 40",  "Seconds",  1,  "1998", "", "%SE23%", false,  "", false,  false,  -1, "", "848956fb-d823-421b-8293-3489ef9e1c3e");
  AddPIDItem( "3-4 Shift Error", "3-4 Error",  "N0 / 40",  "Seconds",  1,  "1999", "", "%SE34%", false,  "", false,  false,  -1, "", "042e1930-52c3-429a-a591-0de561fb045d");
  AddPIDItem( "Fuel Loop Status",  "Loop", "((N0 >> 3) & 1)",  "", 1,  "1105", "", "%FuelLoopStatus%", false,  "", false,  false,  -1, "", "3306c7f1-0764-472e-b4dc-e4c5308c919a");
  AddPIDItem( "Perf Shift Mode", "Perf Shift", "((N0 >> 2) & 1)",  "", 1,  "110C", "%o", "%BitShiftMode%", false,  "", false,  false,  -1, "", "f8132555-7f06-4592-8f80-db3e3db11ceb");
  AddPIDItem( "Desired Idle Speed",  "Desired Idle", "N0 * 12.5",  "RPM",  1,  "1192", "", "%DesiredIdle%",  false,  "", false,  false,  -1, "", "adc672e0-0c84-45d6-8d3c-f7da6e137529");
  AddPIDItem( "IAC Position",  "IAC Position", "N0", "", 1,  "1172", "", "%IACCounts%",  false,  "", false,  false,  -1, "", "442e8f0b-3070-4ca4-983b-e1219078ec55");
  AddPIDItem( "Power Enrichment Mode", "PE Mode",  "((N0 >> 2) & 1)",  "", 1,  "1106", "%o", "%BitPEMode%",  false,  "", false,  false,  -1, "", "0d17a501-6034-4948-ac8a-d10ec889b4a1");
  AddPIDItem( "Decel Fuel Mode", "DFCO Mode",  "((N0 >> 3) & 1)",  "", 1,  "1106", "%o", "%BitDFCOMode%",  false,  "", false,  false,  -1, "", "aff05d96-9f95-45db-ab3b-0c9071b71561");
  AddPIDItem( "Transmission ISS",  "ISS Speed",  "((N1 << 8) + N2) * 0.125", "RPM",  2,  "1941", "", "", false,  "", false,  false,  -1, "", "c88d4440-1868-4ed6-8f93-33d5f414d0e1");
  AddPIDItem( "Transmission OSS",  "OSS Speed",  "((N1 << 8) + N2) * 0.125", "RPM",  2,  "1942", "", "", false,  "", false,  false,  -1, "", "fd324323-84f7-485a-842d-bcb7965a64e0");
  AddPIDItem( "TCC Slip Speed",  "TCC Slip RPM", "((N1 << 8) + N2) * 0.125", "RPM",  2,  "1991", "", "", false,  "", false,  false,  -1, "", "e7c620e8-7248-4c42-a63b-f87428e9bf89");
  AddPIDItem( "Transmission Fluid Temp", "Trans Temp", "N0 - 40",  "ºC", 1,  "1940", "", "", false,  "", false,  false,  -1, "", "cfac07e0-f4ee-4df7-ae28-98098c86b71b");
  AddPIDItem( "TCC Duty Cycle",  "TCC %",  "N0 / 2.55",  "%",  1,  "1970", "", "", false,  "", false,  false,  -1, "", "c5adba8c-9aec-48ff-9485-73892774731e");
  AddPIDItem( "PC Solenoid Duty Cycle",  "PC %", "N0 / 2.55",  "%",  1,  "1972", "", "", false,  "", false,  false,  -1, "", "52f59431-067e-48b0-9fe9-c9e6070e1e14");
  AddPIDItem( "PC Solenoid Actual Current",  "PC Sol Amp", "N0 * 0.0195",  "Amps", 1,  "199E", "", "", false,  "", false,  false,  -1, "", "84bd58d7-b5f6-42ed-804f-cd8c1d61e861");
  AddPIDItem( "PC Solenoid Reference Current", "PC Sol Ref Amp", "N0 * 0.0195",  "Amps", 1,  "199F", "", "", false,  "", false,  false,  -1, "", "83a85b6a-0781-439d-9a0a-0d0f4c316c30");
  AddPIDItem( "18X Crank Sensor",  "18X Crank",  "1310720 / (((N1 << 8) + N2) * 6)", "Pulses", 2,  "1256", "", "", false,  "", false,  false,  -1, "", "8cad9bce-34a8-46c8-83f2-47b2be96d65b");
  AddPIDItem( "3X Crank Sensor", "3X Crank", "1310720 / ((N1 << 8) + N2)", "Pulses", 2,  "124F", "", "", false,  "", false,  false,  -1, "", "0d9981d0-caee-4687-a26c-1fb7833892f6");
  AddPIDItem( "Fans Low Speed",  "Fans Low", "((N0 >> 6) & 1)",  "", 1,  "1103", "%o", "", false,  "", false,  false,  -1, "", "8bc78dde-9082-419e-a4d0-9b6049c7fc6a");
  AddPIDItem( "Fans High Speed", "Fans High",  "((N0 >> 7) & 1)",  "", 1,  "1103", "%o", "", false,  "", false,  false,  -1, "", "d8c0f558-10d8-47cb-ade4-17cf74560b2a");
  AddPIDItem( "Gear Ratio",  "Gear Ratio", "N0 * 0.01563", ":1", 1,  "19A1", "", "", false,  "", false,  false,  -1, "", "7d32d171-4445-4512-8668-319fe6bdada1");
  AddPIDItem( "SPARK ADVANCE (Alt)", "Spark",  "((-1 * N0 / 2) + 64) * -1",  "Degrees",  1,  "000E", "", "%SPK%",  false,  "", false,  false,  -1, "", "ce51ecd9-8f59-4851-a3e7-65d3fb2f0e0e");
  AddPIDItem( "HO2 Bank 1 Sensor 2", "HO2 B1S2", "0.434 * N0 * 10",  "mV", 1,  "1146", "", "", false,  "", false,  false,  -1, "", "e76c4258-c72f-473f-83c8-99c8e38beebe");
  AddPIDItem( "Traction Control Desired Torque", "Trac CTRL Trq", "((N1 << 8) + N2) * 5 / 256", "%",  2,  "160C", "%f", "", false,  "", false,  false,  -1, "", "01594c60-2504-409c-aca9-cc7212381004");
  AddPIDItem( "Fuel Level",  "Fuel Level", "((N1 << 8) + N2) * 0.01953125",  "%",  2,  "12C5", "", "", false,  "", false,  false,  -1, "", "35663a1f-5a55-43bf-aed9-167151b0d59c");
  AddPIDItem( "Transmission Range Switch A", "TR A", "N0 & 1", "", 1,  "1100", "", "", false,  "", false,  false,  -1, "", "7eaea396-26f5-4ada-932a-6bd638cb9f77");
  AddPIDItem( "Transmission Range Switch B", "TR B", "((N0 >> 1) & 1)",  "", 1,  "1100", "", "", false,  "", false,  false,  -1, "", "572dd54c-0699-4f02-bad7-e9110b392c29");
  AddPIDItem( "Transmission Range Switch C", "TR C", "((N0 >> 2) & 1)",  "", 1,  "1100", "", "", false,  "", false,  false,  -1, "", "021a982a-c79f-478b-83cc-b72840f3affa");
  AddPIDItem( "Transmission Range Switch P", "TR P", "((N0 >> 3) & 1)",  "", 1,  "1100", "", "", false,  "", false,  false,  -1, "", "ded10be8-25ce-479f-b320-37cc26f4d47f");
  AddPIDItem( "Transmission Range",  "TR", "N0 & 15",  "", 1,  "1100", "", "", false,  "", false,  false,  -1, "", "8e9c0fee-d630-4933-ac2d-b64c63ec648a");
  AddPIDItem( "Boost Solenoid PWM",  "Boost Solenoid", "((N1 > 4) & 2) + ((N2 > 5) & 3)",  "", 2,  "1108", "", "%BoostPWM%", false,  "", false,  false,  -1, "", "cd6e8e77-c23a-4dd9-8058-62899c6e9adb");
  AddPIDItem( "Engine Torque", "Engine Torque",  "((N1 << 8) + N2) * 0.33895", "N-m",  2,  "19DE", "", "", false,  "", false,  false,  -1, "", "c824f1dd-6dea-4747-bbc3-6cf3d62116a7");
  AddPIDItem( "EGR %", "EGR %",  "N0 / 2.55",  "%",  1,  "1152", "", "", false,  "", false,  false,  -1, "", "e8deae0f-0d3f-4166-a0e6-4422b3041360");
  AddPIDItem( "EGR Duty Cycle",  "EGR %",  "N0 / 2.55",  "%",  1,  "1171", "", "", false,  "", false,  false,  -1, "", "f619397b-f61d-4db5-b946-cd08cbc243e7");
  AddPIDItem( "Desired EGR %", "Desired EGR %",  "N0 / 2.55",  "%",  1,  "119B", "", "", false,  "", false,  false,  -1, "", "939cc26a-2a48-4184-811b-954d13edef39");
  AddPIDItem( "EGR Closed Valve Pintle Position",  "EGR Pintle V", "N0 / 51",  "V",  1,  "11BB", "", "", false,  "", false,  false,  -1, "", "9443a8c6-e12c-4b65-9b38-c818783c96be");
  AddPIDItem( "EGR Flow Test Count", "EGR Flow Count", "N0", "", 1,  "11BD", "", "", false,  "", false,  false,  -1, "", "bdd1520b-15fe-4d44-8e03-4c37a0ecc55e");
  AddPIDItem( "EGR Position Error",  "EGR Error V",  "(N0 - 128) / 1.28",  "V",  1,  "11C1", "", "", false,  "", false,  false,  -1, "", "f21234d1-99f1-4a36-bac9-31be48814af1");
  AddPIDItem( "Commanded EGR", "Commanded EGR",  "N0 / 2.55",  "%",  1,  "002C", "", "", false,  "", false,  false,  -1, "", "50de21a7-9dde-4a66-ad52-20b179b9cee0");
  AddPIDItem( "EGR Error %", "EGR Error",  "N0 * 0.78125 - 100", "%",  1,  "002D", "", "", false,  "", false,  false,  -1, "", "af21e635-3870-4c3e-8ba0-852d0fb48786");
  AddPIDItem( "TP Sensor Voltage", "TP V", "N0 / 51",  "V",  1,  "1143", "", "", false,  "", false,  false,  -1, "", "300db759-4f46-488d-a447-db5109ab7cfc");
  AddPIDItem( "CMP Sensor Signal Present", "CMP Present",  "((N0 >> 1) & 1)",  "", 1,  "1107", "", "", false,  "", false,  false,  -1, "", "7c694ddc-4d01-4e11-b2f1-882caa8df1ed");

}
