#include "screen.h"
#include "settings.h"
#include "webserver.h"
#include "comm.h"
#include "menus.h"


void thread_server() {
  serversetup(); // start up HTTP Server
}

void setup() {
  Serial.begin(115200); // monitor output
  beepLong();
  lcdSetup(); // stage up LCD screen
  SDinit(true); // SD card for storage
  initFlashMem(true);
  loadConfiguration(); // load JSON settings

  //Serial.println("Starting Network/WebServer Thread");
  //threads.addThread(thread_server);
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
