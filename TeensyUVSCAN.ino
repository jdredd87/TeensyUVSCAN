#include "screen.h"
#include "settings.h"
#include "webserver.h"
#include "comm.h"
#include "menus.h"
#include <TimeLib.h>
#include "TeensyThreads.h"

void thread_server() {
  while (1) {
    //threads.delay(1);
    serverloop();
    delay(100);
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void setup() {
  Serial.begin(115200); // monitor output
  beepOnce();
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
  webThreadID = threads.addThread(thread_server, 0, 1024 * 16, 0);
  threads.setTimeSlice(webThreadID,10);
}

void loop() {
  int irV;
  if (ir.available()) {
    irV = ir.readPacket();
    beepOnce();
    processKey(irV);
    irV = 0; // reset it  
  } else
  {
   delay(10);
   //serverloop();
  } 
}
