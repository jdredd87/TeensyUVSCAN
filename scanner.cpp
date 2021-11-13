#include "scanner.h"
#include "settings.h"
#include "menus.h"
#include "comm.h"

int stagepids() {
  String PIDRequest = "";
  int currentBlock = 254; // FE
  int pidCounter = 64;
  int pidPOS = 1;
  int pidCheck = 0;

  serial_flush();
  Serial1.flush();
  for (int idx = 0; idx < NUM_PIDS; idx++) {
    if (PIDS[idx]._selected == true) {

      PIDRequest = "";

      if (idx > 4) {
        if (idx % 4 == 0) {
          send("3F", 100); // keep alive
        }
      }

      pidCheck = pidPOS + PIDS[idx]._len;

      if (pidCheck >= 8) {
        currentBlock--;
        pidPOS = 1;
      }

      pidCounter = 64;

      if ( (1 & PIDS[idx]._len) > 0 ) {
        pidCounter = pidCounter + 1;
      }

      if ( (2 & PIDS[idx]._len) > 0 ) {
        pidCounter = pidCounter + 2;
      }

      if ( (4 & PIDS[idx]._len) > 0 ) {
        pidCounter = pidCounter + 4;
      }

      if ( (1 & pidPOS) > 0 ) {
        pidCounter = pidCounter + 8;
      }

      if ( (2 & pidPOS) > 0 ) {
        pidCounter = pidCounter + 16;
      }

      if ( (4 & pidPOS) > 0 ) {
        pidCounter = pidCounter + 32;
      }

      pidPOS = pidPOS + PIDS[idx]._len;

      if (pidPOS >= 7) {
        currentBlock--;
        pidPOS = 1;
      }

      PIDRequest = "2C";
      PIDRequest.concat(ByteToHex(currentBlock));
      PIDRequest.concat(ByteToHex(pidCounter));
      PIDRequest.concat(PIDS[idx]._PID);
      PIDRequest.concat("FFFF");

      send(PIDRequest, true);
      delay(100);
    }
  }
  delay(500);
  return currentBlock;
}


void activateblocks(int lastblock)
{
 if (lastblock == 254) {
    send("2A14FE000000", 1000);
  } else if (lastblock == 253) {
    send("2A14FEFD0000", 1000);
  } else

    if (lastblock == 252) {
      send("2A14FEFDFC00", 1000);
    } else

      if (lastblock == 251) {
        send("2A14FEFDFCFB", 1000);
      } else

        if (lastblock == 250) {
          send("2A14FEFDFCFB", 1000);
          send("2A24FA000000", 1000);
        } else

          if (lastblock == 249) {
            send("2A14FEFDFCFB", 1000);
            send("2A24FAF90000", 1000);
          } else

            if (lastblock == 248) {
              send("2A14FEFDFCFB", 1000);
              send("2A24FAF9F800", 1000);
            } else if (lastblock == 247) {
              send("2A14FEFDFCFB", 1000);
              send("2A24FAF9F8F7", 1000);
            }
  delay(500);
}


void startScanner() {
  send("ATZ", 1000);
  send("ATE1", 1000);
  send("ATL1", 1000);
  send("ATAL", 1000);
  // send("STPT 1000", 1000); // no longer works after latest firmware
  send("ATS0", 1000);
  send("ATH0", 1000);
  send("ATAT0", 1000);
  send("ATSH6C10F1", 1000); // Make sure header is back
  send("STPTO 500", 1000); // TIMEOUTS
  send("STPTOT 500", 1000);
  
  delay(1000);

  int lastblock = stagepids();
  activateblocks(lastblock);
  unsigned long stime, ftime, etime;

  stime = millis();
  String inData;

  delay(500);
  while (1) {
    int irV;
    if (ir.available()) {
      irV = ir.readPacket();

      if (irV == hexSTAR) {
        break;
      }

    }

    if (Serial1.available()) {
      char c = Serial1.read();
      Serial.print(c);
    }

    ftime = millis();
    etime = ftime - stime;

    if (etime >= 2000) {
      send("", 100);
      delay(100);
      send("3F", 100);
      stime = millis(); // reset clock
    }
  }

  printMenu();
}


void showScanner() {
}


void togglestartupScan() {
  cfg.startupScan = editYesNo(cfg.startupScan);
  saveConfiguration();
}
