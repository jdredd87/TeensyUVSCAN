#include "screen.h"
#include "settings.h"
#include "webserver.h"
#include "comm.h"
#include "menus.h"
#include <TimeLib.h>
#include "TeensyThreads.h"
#include "USBHost_t36.h"
USBHost usbHack; // using USB Host 5v to power LCD screen and such
// NOT as A real USB Host

void thread_server() {
  while (1) {
    //threads.delay(1);
    serverloop();
    delay(10);
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void setup() {
  usbHack.begin(); // We use usbHack to enable 5v output/ground for LCD Screen and IR sensor as 3.3v is iffy.
  Serial.begin(115200); // monitor output

  if ( Serial && CrashReport ) {
    Serial.print(CrashReport);
  }

  beep();
  setSyncProvider(getTeensy3Time);
  delay(500); // charge up time
  lcdSetup(); // stage up LCD screen
  lcdSetup(); // stage up LCD screen a second time. Oddly sometimes 1st try is garbage land.
  SDinit(true); // SD card for storage
  initFlashMem(true);
  InstallPIDS();
  loadConfiguration(); // load JSON settings
  serversetup(); // start up HTTP Server
  initSTN(true); // Setup STN1110 for GM vehicles OBD2
  loadPIDSfile(); // load PID data
  setupMenus(); // Stage up and start menu system
  webThreadID = threads.addThread(thread_server, 0, 1024 * 8, 0);
  threads.setTimeSlice(webThreadID, 10);
}

void loop() {
  int irV;
  if (ir.available()) {
    irV = ir.readPacket();
    beep();
    processKey(irV);
    irV = 0; // reset it
  } else
  {
    delay(10);
    //serverloop();
  }
}
