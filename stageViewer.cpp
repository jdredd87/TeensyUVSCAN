#include "stageViewer.h"

EXTMEM QList < struct MenuCommandRec > PIDVIEWMENU;

void uncheckALLVIEWPIDS() {
  for (int idx = 0; idx < sPIDS.size(); idx++) {
    sPIDS.at(idx)._view = false;
  }
  beepLong();
}

void setupShowPIDS() {
  String pidName = "";

  PIDVIEWMENU.clear();
  AddMenuItem(&PIDVIEWMENU, "Back to Main Menu", "GT", false, 0, false, & MAINMENU);
  AddMenuItem(&PIDVIEWMENU, "Uncheck All", "VU", false, 0, false, NULL);
  AddMenuItem(&PIDVIEWMENU, "", "SP", true, 0, false, NULL);

  for (int idx = 0; idx < sPIDS.size(); idx++) {
    if (sPIDS.at(idx)._shortname == "") {
      pidName = sPIDS.at(idx)._name;
    } else {
      pidName = sPIDS.at(idx)._shortname;
    }

    Serial.print(pidName);
    Serial.print(" ");
    if (sPIDS.at(idx)._view) {
      Serial.println("TRUE");
    } else {
      Serial.println("FALSE");
    }

    AddMenuItem(&PIDVIEWMENU, pidName, "S!", false, idx, sPIDS.at(idx)._view, NULL);
  }

  currentItem = 0; // first item of menu!
}

void showStageViewer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pick up to 4 pids");
  lcd.setCursor(0, 1);
  lcd.print("to display while");
  lcd.setCursor(0, 2);
  lcd.print("scanning vehicle");
  delay(2000); // set back to 5000

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select 4. * to exit.");
  setupShowPIDS();

  // emulate the "GT" menu call

  if (lastMenu == NULL) {
    lastMenu = currentMenu;
  } else {
    lastMenu = NULL;
  }

  Serial.println("processExitMenu");
  processExitMenu();
  Serial.println("Set currentMenu->");
  currentMenu = & PIDVIEWMENU;
  Serial.println("Manual GT Done");
  serverCountDown = 0; // we moved menus, so lets webserver work again some
}
