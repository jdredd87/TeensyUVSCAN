/*
 * screen
 * Contains LCD controlling
 * Simple calls to update screen with information
 */
 
#ifndef screen_h
#define screen_h

#include "Arduino.h"
#include <LiquidCrystal_I2C_Hangul.h>
#include "comm.h"
#include "io.h"
#include "settings.h"
#include "webserver.h"
#include <TeensyID.h>
#include <TimeLib.h>

const String myVersion = "1.0.4";

extern LiquidCrystal_I2C_Hangul lcd;

void lcdSetup();
void setupchars();
void showStep();
void showVIN();
void showOSID();
void showVolts();
void showAbout();
void showVehicleInfo();
void showNetworkStatus();
void getSDCARDINFO();
void updateIP(String IP);
void printStage(String msg);
void getFLASHMEMINFO();
void showSerialInfo();
void showControllerInfo();

String setIP(String IP);

#endif
