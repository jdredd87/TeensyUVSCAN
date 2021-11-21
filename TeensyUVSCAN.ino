#include "screen.h"
#include "settings.h"
#include "webserver.h"
#include "comm.h"
#include "menus.h"
#include <TimeLib.h>
#include "TeensyThreads.h"

void thread_server() {
  delay(1000);
  serversetup(); // start up HTTP Server
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void setup() {
  Serial.begin(115200); // monitor output
  beepOnce();
  setSyncProvider(getTeensy3Time);
  lcdSetup(); // stage up LCD screen
  lcdSetup(); // stage up LCD screen a second time. Oddly sometimes 1st try is garbage land.
  SDinit(true); // SD card for storage
  initFlashMem(true);
  InstallPIDS();
  loadConfiguration(); // load JSON settings
  serversetup(); // start up HTTP Server
  initSTN(); // Setup STN1110 for GM vehicles OBD2
  loadPIDSfile(); // load PID data
  setupMenus(); // Stage up and start menu system
}

void loop() {
  int irV;
  if (ir.available()) {
    irV = ir.readPacket();
    beepOnce();
    processKey(irV);
    irV = 0; // reset it
    serverCountDown = 1024 * 1;  // 8 secondsish
  } else
  {
    // key was pressed, so give http a break
    delay(1);
    serverCountDown--;
    if (serverCountDown < 0) {
      serverCountDown = 0;  // ok we hit our limit, stop
    }
    // if we are at 0 then let the server loop run free until next key press
    if (serverCountDown == 0) {
      serverloop();
    }
  }
}
