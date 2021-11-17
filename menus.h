/*
   menus
   Simple and ugly menu system
   to handle the different menus that are avaialble to the end user
*/

#ifndef menus_h
#define menus_h
#include "Arduino.h"
#include <NecDecoder.h>
#include "screen.h"
#include "settings.h"
#include "scanner.h"
#include "pids.h"
#include "webserver.h"
#include "io.h"
#include "scanner.h"
#include "ramtest.h"
#include "stageViewer.h"

extern const int hexUP;
extern const int hexDOWN;
extern const int hexLEFT;
extern const int hexRIGHT;
extern const int hexOK;
extern const int hex1;
extern const int hex2;
extern const int hex3;
extern const int hex4;
extern const int hex5;
extern const int hex6;
extern const int hex7;
extern const int hex8;
extern const int hex9;
extern const int hex0;
extern const int hexSTAR;
extern const int hexPOUND;
extern NecDecoder ir;

extern void setupPIDS();

struct MenuCommandRec {
  String text;
  String op; // Major Operation to do. Required
  bool onExitMenu; // can use to save data
  struct MenuCommandRec *gotoMenu;
  int idx; // can user for whatever, index to array like PIDS index?
  bool selected; 
};

void processExitMenu();
void irIsr();
void processKey(int key);
void printMenu();
void updateMaxItems();
void ProcessMenuCommand();
void setupMenus();
bool editYesNo(bool option);

#endif
