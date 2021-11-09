/*
   menus
   Simple and ugly menu system
   to handle the different menus that are avaialble to the end user
*/

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

// Menus pushed to extended RAM

struct MenuCommandRec MAINMENU[7] = {
  { .text = "Settings", .op = "GT" },
  { .text = "Select PIDS", .op = "GT" },
  { .text = "Start Scan", .op = "SS" },
  { .text = "Get Vehicle Info", .op = "GV" },
  { .text = "Get Device Info", .op = "GD" },
  { .text = "SD Card Info", .op = "GT" },
  { .text = "About", .op = "AB" }
};

struct MenuCommandRec  SETTINGSMENU[6] =
{
  { .text = "Back to Main Menu", .op = "GT" },
  { .text = "Startup Scan", .op = "ST" },
  { .text = "Enable Beep", .op = "EB"},
  { .text = "Network DHCP", .op = "EN"},
  { .text = "Network IP", .op = "NI"},
  { .text = "Network Status", .op = "NS"}
};

struct MenuCommandRec  SDCARDINFOMENU[2] =
{ { .text = "Back to Main Menu", .op = "GT" },
  { .text = "Get SD Card Info", .op = "SD" },
};

struct MenuCommandRec PIDMENU[NUM_PIDS + 3]; // we add 2 menu options before hand

template< typename T, size_t MainMenuNumberOfSize >
size_t MAINMENUSIZE(T (&) [MainMenuNumberOfSize]) {
  return MainMenuNumberOfSize;
}
int MAINMENUCOUNT = MAINMENUSIZE(MAINMENU) - 1;

template< typename T, size_t SettingsMenuNumberOfSize >
size_t SETTINGSMENUSIZE(T (&) [SettingsMenuNumberOfSize]) {
  return SettingsMenuNumberOfSize;
}
int SETTINGSMENUCOUNT = SETTINGSMENUSIZE(SETTINGSMENU) - 1;

template< typename T, size_t PIDMenuNumberOfSize >
size_t PIDMENUSIZE(T (&) [PIDMenuNumberOfSize]) {
  return PIDMenuNumberOfSize;
}
int PIDMENUCOUNT = PIDMENUSIZE(PIDMENU) - 1;

template< typename T, size_t SDCARDINFOMenuNumberOfSize >
size_t SDCARDINFOMENUSIZE(T (&) [SDCARDINFOMenuNumberOfSize]) {
  return SDCARDINFOMenuNumberOfSize;
}
int SDINFOMENUCOUNT = SDCARDINFOMENUSIZE(SDCARDINFOMENU) - 1;

int currentItem = 0;
int maxItems = 0;

struct MenuCommandRec *currentMenu;
struct MenuCommandRec *lastMenu; // user hits * can go back to prev menu

int pidCounter = 0; // each pid is 1,2,4 bytes big, 40 max.

NecDecoder ir;  // IR sensor

void irIsr() {
  ir.tick();
}

void ProcessMenuCommand(int idx); // forward declare

void uncheckALLPIDS() {
  for (int idx = 0; idx < NUM_PIDS; idx++) {
    PIDS[idx]._selected = false;
  }
  beepLong();
  pidCounter = 0;
}

void processExitMenu() {
  for (int idx = 0; idx < maxItems; idx++) {
    if (currentMenu[idx].text == "") {
      if (currentMenu[idx].onExitMenu == true)
      {
        ProcessMenuCommand(idx);
      }
    }
  }
}

void ProcessMenuCommand(int idx) {
  Serial.println("------------------------------------------------");
  Serial.println(currentMenu[idx].text);
  Serial.println(currentMenu[idx].op);
  Serial.println(currentMenu[idx].onExitMenu);
  Serial.println("------------------------------------------------");
  if (idx == -1) {
    idx = currentItem;
  }
  if (currentMenu[idx].op == "P!") { // !! = PID toggle true/false option
    currentMenu[idx].selected = !currentMenu[idx].selected;
    if (currentMenu[idx].selected) {
      // lets check. if we are to many
      if ( (pidCounter + PIDS[currentMenu[idx].idx]._len) > 40) {
        beepLong();
        lcd.setCursor(0, 3);
        lcd.print("Max PIDS Selected!");
        delay(2500);
        lcd.setCursor(0, 3);
        lcd.print("                  ");
        currentMenu[idx].selected = false;
      } else
      {
        pidCounter = pidCounter + PIDS[currentMenu[idx].idx]._len;
      }
    } else
    {
      pidCounter = pidCounter - PIDS[currentMenu[idx].idx]._len;
    }
    PIDS[currentMenu[idx].idx]._selected = currentMenu[idx].selected;
  } else if (currentMenu[idx].op == "GT") { // GOTO MENU

    if (lastMenu == NULL) {
      lastMenu = &currentMenu[0];
    } else
    {
      lastMenu = NULL;
    }
    processExitMenu();
    currentMenu = &currentMenu[idx].gotoMenu[0];
    idx = 0;
    updateMaxItems();
    serverCountDown = 0; // we moved menus, so lets webserver work again some
  } else if (currentMenu[idx].op == "EB") {
    toggleBeep();
  } else if (currentMenu[idx].op == "GV") {
    showVehicleInfo();
  } else if (currentMenu[idx].op == "GD") {
    showDeviceInfo();
  } else if (currentMenu[idx].op == "AB") {
    showAbout();
  } else if (currentMenu[idx].op == "ST") {
    togglestartupScan();
  } else if (currentMenu[idx].op == "SP") {
    savePIDSfile();
  } else if (currentMenu[idx].op == "SD") {
    getSDCARDINFO();
  } else if (currentMenu[idx].op == "SU") {
    uncheckALLPIDS();
    setupPIDS();// rebuild table because we unchecked everything!
  } else if (currentMenu[idx].op == "EN") {
    toggleDHCP();
    saveConfiguration();
    reboot(String("DHCP Change"));
  } else if (currentMenu[idx].op == "NI") {
    cfg.IPAddress = setIP(cfg.IPAddress);
    saveConfiguration();
    reboot(String("IP Change"));
  } else if (currentMenu[idx].op == "NS") {
    showNetworkStatus();
  } else if (currentMenu[idx].op == "SS") {
    startScanner();
  }
}

void updateMaxItems() {
  if (currentMenu == MAINMENU)
  {
    maxItems = MAINMENUCOUNT;
  } else if (currentMenu == SETTINGSMENU)
  {
    maxItems = SETTINGSMENUCOUNT;
  } else if (currentMenu == PIDMENU)
  {
    maxItems = PIDMENUCOUNT;
  } else if (currentMenu == SDCARDINFOMENU)
  {
    maxItems = SDINFOMENUCOUNT;
  }
  currentItem = 0;
}

void printMenu() {
  bool showpidcount = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  if (currentItem == 0) {
    lcd.write(1); // down arrow
  }
  else if (currentItem == maxItems) {
    lcd.write(0); // up arrow
  }
  else
  {
    lcd.write(0); // up arrow
    lcd.write(1); // down arrow
  }
  if (currentMenu[currentItem].op == "GT") {
    lcd.write(2);
  }
  lcd.print(" ");
  if (currentMenu[currentItem].op == "P!") {
    showpidcount = true;
    if (currentItem == 0) {
      lcd.print(" ");
    }
    if (currentItem == maxItems) {
      lcd.print(" ");
    }
    if (currentMenu[currentItem].selected) {
      lcd.print("[");
      lcd.write(4);
      lcd.print("] ");
    } else
    {
      lcd.print("[ ] ");
    }
    lcd.print(currentMenu[currentItem].text.substring(0, 13));
    lcd.setCursor(0, 1);
    lcd.print(currentMenu[currentItem].text.substring(13));
  }
  else
  {
    lcd.print(currentMenu[currentItem].text);
  }
  if (showpidcount) {
    lcd.setCursor(0, 3);
    lcd.print(pidCounter);
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
    if (currentItem < 0)
    {
      currentItem = 0;
    }
    if (currentMenu[currentItem].text == "") {
      processKey(key); // recursive
      return;
    }
  }
  if (key == hexDOWN) // DOWN
  {
    ++currentItem;
    if (currentItem > maxItems)
    {
      currentItem = maxItems;
    }
    if (currentMenu[currentItem].text == "") {
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
      currentItem = maxItems;
    } else // jump to end
      if (currentItem == maxItems) {
        currentItem = 0;
      } else // jump to top
      {
        currentItem = 0;  // jump to top?
      }
  }
  if (key == hexSTAR) // *
  {
    if (lastMenu != NULL) {
      Serial.println("last menu time...");
      processExitMenu();
      currentMenu = &lastMenu[0];
      currentItem = 0;
      updateMaxItems();
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
  } else
  {
    lcd.print(" YES      >NO ");
  }
  while (1) {
    delay(100);
    if (ir.available()) {
      irV = ir.readPacket();
      beepOnce();
      if (irV == hexLEFT)
      {
        lcd.setCursor(0, 2);
        lcd.print(">YES       NO ");
        option = true;
      }
      if (irV == hexRIGHT)
      {
        lcd.setCursor(0, 2);
        lcd.print(" YES      >NO ");
        option = false;
      }
      if (irV == hexOK)
      {
        break;
      }
      irV = 0; // reset it
    }
  }
  return option;
}

void setupPIDS() {
  PIDMENU[0].text = "Back to Main Menu";
  PIDMENU[0].op = "GT"; // GT MENU
  PIDMENU[0].gotoMenu = &MAINMENU[0];

  PIDMENU[1].text = "Uncheck All";
  PIDMENU[1].op = "SU"; // Save Pids
  PIDMENU[1].onExitMenu = true;


  PIDMENU[2].text = "";
  PIDMENU[2].op = "SP"; // Save Pids
  PIDMENU[2].onExitMenu = true;

  for (int idx = 0; idx < NUM_PIDS; idx++)
  {
    PIDMENU[idx + 3].text = PIDS[idx]._name;
    PIDMENU[idx + 3].op = "P!"; // select mode operation
    PIDMENU[idx + 3].idx = idx;
    PIDMENU[idx + 3].selected = PIDS[idx]._selected;
    PIDMENU[idx + 3].gotoMenu = NULL;
  }
}

void setupMenus() {
  attachInterrupt(IRPin, irIsr, FALLING); // infrared sensor
  lastMenu = NULL;
  setupPIDS();

  MAINMENU[0].gotoMenu = &SETTINGSMENU[0];
  MAINMENU[1].gotoMenu = &PIDMENU[0];
  MAINMENU[5].gotoMenu = &SDCARDINFOMENU[0];

  SETTINGSMENU[0].gotoMenu = &MAINMENU[0];
  SDCARDINFOMENU[0].gotoMenu = &MAINMENU[0];

  currentMenu = &MAINMENU[0];
  updateMaxItems();
  printMenu();
}
