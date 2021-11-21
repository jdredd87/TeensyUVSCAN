#include "menus.h"

const int IRPin = 3;
const int hexUP = 0xFF629D;
const int hexDOWN = 0xFFA857;
const int hexLEFT = 0xFF22DD;
const int hexRIGHT = 0xFFC23D;
const int hexOK = 0xFF02FD;
const int hex1 = 0xFF6897;
const int hex2 = 0xFF9867;
const int hex3 = 0xFFB04F;
const int hex4 = 0xFF30CF;
const int hex5 = 0xFF18E7;
const int hex6 = 0xFF7A85;
const int hex7 = 0xFF10EF;
const int hex8 = 0xFF38C7;
const int hex9 = 0xFF5AA5;
const int hex0 = 0xFF4AB5;
const int hexSTAR = 0xFF42BD;
const int hexPOUND = 0xFF52AD;

int currentItem = 0;

// Variable for each MENU we want to build

EXTMEM QList < struct MenuCommandRec > MAINMENU;
EXTMEM QList < struct MenuCommandRec > SETTINGSMENU;
EXTMEM QList < struct MenuCommandRec > PIDMENU;
EXTMEM QList < struct MenuCommandRec > DIAGMENU;

// Simple pointers to the current menu we are on ( and pointing to ) and the last menu ( where we came from... simple 2 level menu system )
// if we want to go three levels or deeper, then have to change up how last menu works then but for now this works ok

struct QList < struct MenuCommandRec > * currentMenu;
struct QList < struct MenuCommandRec > * lastMenu; // user hits * can go back to prev menu

NecDecoder ir; // IR sensor

void irIsr() {
  ir.tick();
}
int AddMenuItem(struct QList < struct MenuCommandRec > * fMenu, MenuCommandRec item) { // add by item object
  fMenu -> push_back(item);
  return fMenu -> size();
}

int AddMenuItem(struct QList < struct MenuCommandRec > * fMenu, String text, String op, bool onExitMenu, int idx, bool selected, struct QList < struct MenuCommandRec > * gotoMenu) {
  MenuCommandRec item;
  item.text = text;
  item.op = op;
  item.onExitMenu = onExitMenu;
  item.idx = idx;
  item.selected = selected;
  item.gotoMenu = gotoMenu;
  fMenu -> push_back(item);
  return fMenu -> size();
}

void ProcessMenuCommand(int idx); // forward declare

void uncheckALLPIDS() {
  ClearBlocks();
  sPIDS.clear();
  for (int idx = 0; idx < fPIDS.size(); idx++) {
    fPIDS.at(idx)._selected = false;
  }
  beepLong();
}

void processExitMenu() {
  for (int idx = 0; idx < currentMenu -> size(); idx++) {
    if (currentMenu -> at(idx).text == "") {
      if (currentMenu -> at(idx).onExitMenu == true) {
        ProcessMenuCommand(idx);
      }
    }
  }
}

void ProcessMenuCommand(int idx) {
  if (idx == -1) {
    idx = currentItem;
  }
  if (currentMenu -> at(idx).op == "S!") { // P! = PID stage view selection
    currentMenu -> at(idx).selected = !currentMenu -> at(idx).selected; // flip it
    sPIDS.at(currentMenu -> at(idx).idx)._view = !sPIDS.at(currentMenu -> at(idx).idx)._view; // flip it
    if (getVIEWcount() > 4) {
      lcd.setCursor(0, 3);
      lcd.print("4 limit hit!");
      currentMenu -> at(idx).selected = false;
      sPIDS.at(currentMenu -> at(idx).idx)._view = false;
      beepLong();
      return; // we hit our limit of 4 .. so beeeeeep and deselect
    }
  } else if (currentMenu -> at(idx).op == "P!") { // P! = PID toggle true/false option
    currentMenu -> at(idx).selected = !currentMenu -> at(idx).selected;
    if (!currentMenu -> at(idx).selected) {
      int dIDX; // delete index
      String dGUID; // delete index guid
      int rGUID = -1; // remove index
      dIDX = currentMenu -> at(idx).idx; // index of the item in PIDS
      dGUID = fPIDS.at(dIDX)._guid; // GUID for PIDS dIDX
      // find it in sPIDS if there, should be if unselecting it!
      for (int sx = 0; sx < sPIDS.size(); sx++) {
        if (sPIDS.at(sx)._guid == dGUID) {
          rGUID = sx; // we found it.
          break;
        }
      }
      if (rGUID > -1) { // ok so as long as not -1 then remove it from the sPDIS list
        sPIDS.clear(rGUID);
      }
      return;
    } else {
      bool found = false;
      int foundidx = 0;
      float rnd = 0;
      bool isFake;
      int x;
      x = currentMenu -> at(idx).idx;
      for (int y = 0; y < sPIDS.size(); y++) {
        found = false;
        if (sPIDS.at(y)._PID == fPIDS.at(x)._PID) {
          found = true;
          foundidx = y;
          isFake = false;
          break;
        }
      }
      // If Duplicate found then mark it as a duplicate then go to next item
      if (found) {
        sPIDS.push_back(fPIDS.at(x));
        sPIDS.at(sPIDS.size() - 1)._duplicate = true;
        sPIDS.at(sPIDS.size() - 1)._dupeIndex = foundidx;
        sPIDS.at(sPIDS.size() - 1)._selected = true;
        return;
        // we found a duplicate. so add it to the list of scanable pids, but don't add it to the PCM pid table.
      }
      isFake = fPIDS.at(x)._fake; // check for FAKE pids
      // if FAKE then mark it and add it and goto next item
      if (isFake == true) {
        sPIDS.push_back(fPIDS.at(x));
        sPIDS.at(sPIDS.size() - 1)._selected = true;
        // we found a duplicate. so add it to the list of scanable pids, but don't add it to the PCM pid table.
        return;
      }
      sPIDS.push_back(fPIDS.at(x));
      sPIDS.at(sPIDS.size() - 1)._selected = true;
      bool added = BuildPIDS();
      if (added == false) {
        sPIDS.pop_back(); // remove last item
        return;
      }
    }
  } else if (currentMenu -> at(idx).op == "GT") { // GOTO MENU
    if (lastMenu == NULL) {
      lastMenu = currentMenu;
    } else {
      lastMenu = NULL;
    }
    processExitMenu();
    currentMenu = currentMenu -> at(idx).gotoMenu; //[0];
    idx = 0;
    serverCountDown = 0; // we moved menus, so lets webserver work again some
    currentItem = 0;
  } else if (currentMenu -> at(idx).op == "EB") {
    toggleBeep();
  } else if (currentMenu -> at(idx).op == "GV") {
    showVehicleInfo();
  } else if (currentMenu -> at(idx).op == "SI") {
    showSerialInfo();
  } else if (currentMenu -> at(idx).op == "DI") {
    showControllerInfo();
  } else if (currentMenu -> at(idx).op == "AB") {
    showAbout();
  } else if (currentMenu -> at(idx).op == "ST") {
    togglestartupScan();
  } else if (currentMenu -> at(idx).op == "SP") {
    savePIDSfile();
  } else if (currentMenu -> at(idx).op == "SD") {
    getSDCARDINFO();
  } else if (currentMenu -> at(idx).op == "FM") {
    getFLASHMEMINFO();
  } else if (currentMenu -> at(idx).op == "SU") {
    uncheckALLPIDS();
    setupPIDS(); // rebuild table because we unchecked everything!
  } else if (currentMenu -> at(idx).op == "VU") {
    uncheckALLVIEWPIDS();
    setupShowPIDS(); // rebuild menu since we unchecked views?
  } else if (currentMenu -> at(idx).op == "EN") {

    bool ODHCP;
    ODHCP = cfg.useDHCP;
    toggleDHCP();

    if (ODHCP != cfg.useDHCP) {
      saveConfiguration();
      reboot(String("DHCP Change"));
    } else {
      Serial.println("No change to DHCP Mode");
    }

  } else if (currentMenu -> at(idx).op == "NI") {
    String OIP = cfg.IPAddress;
    cfg.IPAddress = setIP(cfg.IPAddress);
    if (OIP != cfg.IPAddress) {
      saveConfiguration();
      reboot(String("IP Change"));
    } else {
      Serial.println("No change to IP Address");
    }
  } else if (currentMenu -> at(idx).op == "NS") {
    showNetworkStatus();
  } else if (currentMenu -> at(idx).op == "SS") {
    startScanner();
  } else if (currentMenu -> at(idx).op == "RT") {
    doRamtest();
  } else if (currentMenu -> at(idx).op == "SV") {
    showStageViewer();
  }
}

void printMenu() {

  bool showpidcount = false;
  bool showviewcount = false;

  lcd.clear();
  lcd.setCursor(0, 0);
  if (currentItem == 0) {
    lcd.write(1); // down arrow
  } else if (currentItem == currentMenu -> size()) {
    lcd.write(0); // up arrow
  } else {
    lcd.write(0); // up arrow
    lcd.write(1); // down arrow
  }
  if (currentMenu -> at(currentItem).op == "GT") {
    lcd.write(2);
  }
  lcd.print(" ");

  if (currentMenu -> at(currentItem).op == "P!" or currentMenu -> at(currentItem).op == "S!") {

    showpidcount = currentMenu -> at(currentItem).op == "P!";
    showviewcount = currentMenu -> at(currentItem).op == "S!";

    if (currentItem == 0) {
      lcd.print(" ");
    }
    if (currentItem == currentMenu -> size()) {
      lcd.print(" ");
    }

    if (currentMenu -> at(currentItem).op == "S!") {

      Serial.println(sPIDS.at(currentMenu -> at(currentItem).idx)._name);

      if (sPIDS.at(currentMenu -> at(currentItem).idx)._view) {
        lcd.print("[");
        lcd.write(4);
        lcd.print("] ");
      } else {
        lcd.print("[ ] ");
      }
    } else
    { if ( currentMenu -> at(currentItem).selected) {
        lcd.print("[");
        lcd.write(4);
        lcd.print("] ");
      } else {
        lcd.print("[ ] ");
      }
    }

    lcd.print(currentMenu -> at(currentItem).text.substring(0, 13));
    lcd.setCursor(0, 1);
    lcd.print(currentMenu -> at(currentItem).text.substring(13));
  } else {
    lcd.print(currentMenu -> at(currentItem).text);
  }

  if (showpidcount) {
    lcd.setCursor(0, 3);
    lcd.print(sPIDS.size());
  }

  if (showviewcount) {
    lcd.setCursor(0, 3);
    lcd.print(getVIEWcount());
  }

}

void processKey(int key) {

  /*
      Known bug. You can't have a "blank" item yet at position 0 or last position of the menu.
      Not A huge problem but may want to fix this eventually.
      Otherwise stuck in a forever loop.
  */

  if (key == hexUP) // UP
  {
    currentItem--;
    if (currentItem < 0) {
      currentItem = 0;
    }
    if (currentMenu -> at(currentItem).text == "") {
      processKey(key); // recursive
      return;
    }
  }
  if (key == hexDOWN) // DOWN
  {
    ++currentItem;
    if (currentItem > currentMenu -> size() - 1)

    {
      currentItem = 0; // go back to top?
    }

    if (currentMenu -> at(currentItem).text == "") {
      processKey(key); // recursive
      return;
    }
  }
  if (key == hexOK) // OK
  {
    ProcessMenuCommand(currentItem);
  }
  if (key == hexPOUND) {
    if (currentItem == 0) {
      currentItem = currentMenu -> size() - 1;
    } else // jump to end
      if (currentItem == currentMenu -> size() - 1) {
        currentItem = 0;
      } else // jump to top
      {
        currentItem = 0; // jump to top?
      }
  }
  if (key == hexSTAR) // *
  {
    if (lastMenu != NULL) {
      Serial.println("last menu time...");
      processExitMenu();
      currentMenu = lastMenu;
      currentItem = 0;

      lastMenu = NULL;
    }
  }
  printMenu();
}

bool editYesNo(bool option) {
  int irV = 0;
  lcd.setCursor(0, 2);
  if (option) {
    lcd.print(">YES       NO ");
  } else {
    lcd.print(" YES      >NO ");
  }
  while (1) {
    delay(100);
    if (ir.available()) {
      irV = ir.readPacket();
      beepOnce();
      if (irV == hexLEFT) {
        lcd.setCursor(0, 2);
        lcd.print(">YES       NO ");
        option = true;
      }
      if (irV == hexRIGHT) {
        lcd.setCursor(0, 2);
        lcd.print(" YES      >NO ");
        option = false;
      }
      if (irV == hexOK) {
        break;
      }
      irV = 0; // reset it
    }
  }
  return option;
}

void setupPIDS() {
  String pidName = "";
  PIDMENU.clear();
  AddMenuItem( & PIDMENU, "Back to Main Menu", "GT", false, 0, false, & MAINMENU);
  AddMenuItem( & PIDMENU, "Uncheck All", "SU", false, 0, false, NULL);
  AddMenuItem( & PIDMENU, "", "SP", true, 0, false, NULL);
  for (int idx = 0; idx < fPIDS.size(); idx++) {
    if (fPIDS.at(idx)._shortname == "") {
      pidName = fPIDS.at(idx)._name;
    } else {
      pidName = fPIDS.at(idx)._shortname;
    }
    AddMenuItem( & PIDMENU, pidName, "P!", false, idx, fPIDS.at(idx)._selected, NULL);
  }
}

void setupMenus() {
  attachInterrupt(IRPin, irIsr, FALLING); // infrared sensor
  lastMenu = NULL;

  MAINMENU.clear();
  AddMenuItem( & MAINMENU, "Settings", "GT", false, 0, false, & SETTINGSMENU);
  AddMenuItem( & MAINMENU, "Select PIDS", "GT", false, 0, false, & PIDMENU);
  AddMenuItem( & MAINMENU, "Stage View", "SV", false, 0, false, NULL);
  AddMenuItem( & MAINMENU, "Start Scan", "SS", false, 0, false, NULL);
  AddMenuItem( & MAINMENU, "Get Vehicle Info", "GV", false, 0, false, NULL);
  AddMenuItem( & MAINMENU, "Device Diag", "GT", false, 0, false, & DIAGMENU);
  AddMenuItem( & MAINMENU, "About", "AB", false, 0, false, NULL);

  SETTINGSMENU.clear();
  AddMenuItem( & SETTINGSMENU, "Back to Main Menu", "GT", false, 0, false, & MAINMENU);
  AddMenuItem( & SETTINGSMENU, "Startup Scan", "ST", false, 0, false, NULL);
  AddMenuItem( & SETTINGSMENU, "Enable Beep", "EB", false, 0, false, NULL);
  AddMenuItem( & SETTINGSMENU, "Network DHCP", "EN", false, 0, false, NULL);
  AddMenuItem( & SETTINGSMENU, "Network IP", "NI", false, 0, false, NULL);
  AddMenuItem( & SETTINGSMENU, "Network Status", "NS", false, 0, false, NULL);

  DIAGMENU.clear();
  AddMenuItem( & DIAGMENU, "Back to Main Menu", "GT", false, 0, false, & MAINMENU);
  AddMenuItem( & DIAGMENU, "RAM Test", "RT", false, 0, false, NULL);
  AddMenuItem( & DIAGMENU, "Get SD Card Info", "SD", false, 0, false, NULL);
  AddMenuItem( & DIAGMENU, "Get Flash Info", "FM", false, 0, false, NULL);
  AddMenuItem( & DIAGMENU, "Get Serial Info", "SI", false, 0, false, NULL);
  AddMenuItem( & DIAGMENU, "Get Device Info", "DI", false, 0, false, NULL);

  setupPIDS(); // do logic to build PIDS menu
  currentMenu = & MAINMENU;
  printMenu();
}
