/*
   comm
   Communications for the STN1110 Serial interface to the GM OBD2 PCM
*/

#include "comm.h"

void serial_flush(void) { // flush input buffer if any chars left over
  if (Serial1.available())
  {
    while (Serial1.available()) Serial1.read();
  }
}

String send2(String cmd, bool ignore) {
  Serial.print("SEND2>> ");
  Serial.println(cmd);
  Serial.println(""); // terminal
  Serial1.print(cmd);
  Serial1.print("\r"); // device
  char c;
  String r = "";
  int timeout = 0;

  while (1) {
    timeout++;
    c = 0;

    if (Serial1.available()) {
      c = Serial1.read();
      r = r + c;
    }

    if (c == '?') {
      break;
    }
    if (c == '>') {
      break;
    }
    if (ignore) {
      break; // just jump right out basically
    }
    if (timeout == 100) {
      break; // if really short time
    }
  }

  Serial.println("done");
  return r;
}
String send(String cmd, int D) // send a command to elm327
{
  String inData = "";
  serial_flush();
  inData = "";
  Serial.print("SEND>> ");
  Serial.println(cmd);
  Serial.println(""); // terminal
  Serial1.print(cmd);
  Serial1.print("\r"); // device
  delay(10);
  unsigned long timeoutTime = millis() + D; // time clock as of right now + our D for delay timeout value
  unsigned long checkTime = 0;
  while ( 1 )  //(Serial1.available())
  {
    // very simple check for a timeout
    checkTime = millis();
    if (checkTime > timeoutTime) {
      Serial.println("Timeout!");
      inData = "";
      break;
    }
    delay(1); // i like to wait 1ms for time to happen cause this stuff is slow and not like its super time sensative
    if (Serial1.available()) {
      delay(1);
      char recChar = Serial1.read();
      if (recChar == '>')
      {
        break;
      }
      else {
        if (recChar == char(10)) continue;
        if (recChar == char(13)) continue;
        inData.concat(recChar);
      }
    }
  }
  Serial.print("RECV << ");
  Serial.println(inData);
  Serial.println("");
  inData.trim();
  inData.replace(">", "");
  inData.replace(" ", "");
  return inData;
}

bool initSTN() {
  printStage("STN1110 Init");
  Serial1.begin(9600);
  Serial1.flush();
  serial_flush();
  printStage("SET_ALL_TO_DEFAULTS"); send(SET_ALL_TO_DEFAULTS, 2000);
  printStage("RESET_ALL"); send(RESET_ALL, 3000);
  printStage("LINEFEEDS_ON"); send(LINEFEEDS_ON, 1000);
  printStage("ECHO_OFF"); send(ECHO_OFF, 1000);
  printStage("PRINTING_SPACES_OFF"); send(PRINTING_SPACES_OFF, 1000);
  printStage("ALLOW_LONG_MESSAGES"); send(ALLOW_LONG_MESSAGES, 1000);
  printStage("HEADERS_OFF"); send(HEADERS_OFF, 1000);
  //printStage("DISP_CURRENT_PROTOCOL"); send(DISP_CURRENT_PROTOCOL, 1000);
  printStage("REQUEST_TEST_PID"); send(REQUEST_TEST_PID, 1000);
  printStage("REQUEST_HEADER"); send(REQUEST_HEADER, 1000);
  printStage("");
  return true;
}

bool initSTNScanner() {
  printStage("STN1110 Init for scanning PCM");
  Serial1.flush();
  serial_flush();
  printStage("SET_ALL_TO_DEFAULTS"); send(SET_ALL_TO_DEFAULTS, 1000);
  printStage("RESET_ALL"); send(RESET_ALL, 1000);
  printStage("ECHO_OFF"); send(ECHO_OFF, 1000); // yes ECHO ON
  printStage("LINEFEEDS_ON"); send(LINEFEEDS_ON, 1000);
  printStage("ALLOW_LONG_MESSAGES"); send(ALLOW_LONG_MESSAGES, 1000);
  send("STPT 1000", 1000);
  printStage("PRINTING_SPACES_OFF"); send(PRINTING_SPACES_OFF, 1000);
  printStage("HEADERS_OFF"); send(HEADERS_OFF, 1000);
  printStage("ADAPTIVE_TIMING_OFF"); send(ADAPTIVE_TIMING_OFF, 1000); // very important, with out this incoming data won't flow
  printStage("REQUEST_HEADER"); send(REQUEST_HEADER, 1000);
  return true;
}


//need some verify routines after grabbing data
//to make sure what came back is proper!

bool isOK(String value) { // is string OK
  value.trim();
  if (value == "OK") {
    return true;
  } else
  {
    return false;
  }
}

bool isSTOPPED(String value) { // is string STOPPED
  value.trim();
  if (value == "STOPPED") {
    return true;
  } else
  {
    return false;
  }
}

bool isGOOD(String value, String checkstr, int len) { // we can check the start of a string to make sure it matches
  value.trim();
  if (len != -1) {
     int clen;
     clen = checkstr.length();   
    if (clen > len) {
      Serial.println("length error");
      return false;
    }
  }
  return checkstr.startsWith(value);
}

struct Tdeviceinfo getDeviceInfo() // return info about the STN chipset
{
  struct Tdeviceinfo device;
  device.STDI = send("STDI", 1000); showStep(); // Device hardware ID
  device.STDICES = send("STDICES", 1000); showStep(); // Engine start count
  device.STDICPO = send("STDICPO", 1000); showStep(); // Power on Reset count
  device.STI = send("STI", 1000); showStep(); // Firmware ID
  device.STIX = send("STIX", 1000); showStep(); // Extended firmware ID
  device.STMFR = send("STMFR", 1000); showStep(); // device mfg id
  device.STSN = send("STSN", 1000); showStep(); // device serial #
  device.STPRS = send("STPRS", 1000); showStep(); // current protocol
  return device;
}

String getVOLTS()
{
  String v1 = send("STVR", 1000);
  return v1;
}

String getVIN() // Request PCM stored VIN
{
  String v1 = send(GET_VIN1, 1000);
  if (isGOOD("7C0100", v1, -1) == false) {
    Serial.println("VIN BAD");
    return "BAD";
  }
  String v2 = send(GET_VIN2, 1000);
  String v3 = send(GET_VIN3, 1000);
  String VIN = "";
  v1.remove(0, 6);
  v2.remove(0, 4);
  v3.remove(0, 4);
  VIN.concat(v1);
  VIN.concat(v2);
  VIN.concat(v3);
  VIN = HexToString(VIN);
  return VIN;
}

String getOSID() // Request PCM OSID #
{
  String v1 = send(GET_OSID, 1000);
  long OSID;
  v1.remove(0, 4);
  Serial.print("OSID HEX : ");
  Serial.println(v1);
  OSID = StrToInt(v1);
  return String(OSID, DEC);
}
