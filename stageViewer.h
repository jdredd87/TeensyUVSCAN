
#ifndef stageViewer_h
#define stageViewer_h

#include "Arduino.h"
#include "pids.h"
#include "io.h"
#include "screen.h"
#include "menus.h"

void showStageViewer();
void uncheckALLVIEWPIDS();
void setupShowPIDS();
extern QList <struct MenuCommandRec> PIDVIEWMENU;
#endif
