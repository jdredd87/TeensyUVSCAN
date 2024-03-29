/*
   comm
   Communications for the STN1110 Serial interface to the GM OBD2 PCM
*/

#include "comm.h"

void serial_flush(void) { // flush input buffer if any chars left over
  if (Serial1.available()) {
    while (Serial1.available()) Serial1.read();
  }
}


void send4(String cmd, int D) // sends data and grabs response, but just eats it.
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
  while (1) //(Serial1.available())
  {
    // very simple check for a timeout
    checkTime = millis();
    if (checkTime > timeoutTime) {    
      inData = "";
      break;
    }
    delay(1); // i like to wait 1ms for time to happen cause this stuff is slow and not like its super time sensative
    if (Serial1.available()) {
      delay(1);
      char recChar = Serial1.read();
      if (recChar == '>') {
        break;
      } else {
        if (recChar == char(10)) continue;
        if (recChar == char(13)) continue;
        inData.concat(recChar);
      }
    }
  }
}

void send3(String cmd) // Send data but that is it
{
  Serial.print("SEND3>> ");
  Serial.println(cmd);
  Serial.println(""); // terminal
  Serial1.print(cmd);
  Serial1.print("\r"); // device
}

String send2(String cmd, bool ignore) { // send data, grab data, no defined timeout by user, 100ms time out hard coded in or break instantly out
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

String send(String cmd, int D) // Send data and get data
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
  while (1) //(Serial1.available())
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
      if (recChar == '>') {
        break;
      } else {
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

bool initSTN(bool withHeader) {
  printStage("STN1110 Init");
  Serial1.begin(9600);
  Serial1.flush();
  serial_flush();
  printStage("SET_ALL_TO_DEFAULTS");  send(SET_ALL_TO_DEFAULTS, 2000);
  printStage("RESET_ALL");            send(RESET_ALL, 3000);
  printStage("LINEFEEDS_ON");         send(LINEFEEDS_ON, 1000);
  printStage("ECHO_OFF");             send(ECHO_OFF, 1000);
  printStage("PRINTING_SPACES_OFF");  send(PRINTING_SPACES_OFF, 1000);
  printStage("ALLOW_LONG_MESSAGES");  send(ALLOW_LONG_MESSAGES, 1000);
  printStage("HEADERS_OFF");          send(HEADERS_OFF, 1000);
  printStage("REQUEST_TEST_PID");     send(REQUEST_TEST_PID, 1000);
  if (withHeader) {
    printStage("REQUEST_HEADER");
    send(REQUEST_HEADER, 1000);
  }
  printStage("");
  return true;
}

void initSTNScanner() {
  printStage("STN1110 Init for scanning PCM");
  Serial1.flush();
  serial_flush();
  printStage("RESET_ALL");            send(SET_ALL_TO_DEFAULTS, 1000);
  printStage("ECHO_OFF");             send(ECHO_OFF, 1000);
  printStage("LINEFEEDS_ON");         send(LINEFEEDS_ON, 1000);
  printStage("ALLOW_LONG_MESSAGES");  send(ALLOW_LONG_MESSAGES, 1000);
  printStage("PRINTING_SPACES_OFF");  send(PRINTING_SPACES_OFF, 1000);
  printStage("HEADERS_OFF");          send(HEADERS_OFF, 1000);
  printStage("ADAPTIVE_TIMING_OFF");  send(ADAPTIVE_TIMING_OFF, 1000);
  printStage("STDI"); send("STDI", 1000);
  printStage("STI");  send("STI", 1000);
  printStage("ATI");  send("ATI", 1000);
  send("010D", 1000); // reset some pcm data asking for pids?
  send("0110", 1000); // reset some pcm data asking for pids?
  send(REQUEST_HEADER, 1000); // Make sure header is back
  send(GET_VIN1, 1000); // VIN 1
  send(GET_VIN2, 1000); // VIN 2
  send(GET_VIN3, 1000); // VIN 3
  send(GET_OSID, 1000); // OSID
  send(GET_HW, 1000); // PCM HW
  send("20", 1000); // reset pcm calls maybe?
  send("1000", 1000); // reset some pcm data asking for pids?
  send("0100", 1000); // reset some pcm data asking for pids?
  
  // printStage("STPTO");  send("STPTO 1000", 1000); // TIMEOUTS
  // printStage("STPTOT"); send("STPTOT 1000", 1000);
}

//need some verify routines after grabbing data
//to make sure what came back is proper!

bool isOK(String value) { // is string OK
  value.trim();
  if (value == "OK") {
    return true;
  } else {
    return false;
  }
}

bool isSTOPPED(String value) { // is string STOPPED
  value.trim();
  if (value == "STOPPED") {
    return true;
  } else {
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
  device.STDI = send("STDI", 1000);
  showStep(); // Device hardware ID
  device.STDICES = send("STDICES", 1000);
  showStep(); // Engine start count
  device.STDICPO = send("STDICPO", 1000);
  showStep(); // Power on Reset count
  device.STI = send("STI", 1000);
  showStep(); // Firmware ID
  device.STIX = send("STIX", 1000);
  showStep(); // Extended firmware ID
  device.STMFR = send("STMFR", 1000);
  showStep(); // device mfg id
  device.STSN = send("STSN", 1000);
  showStep(); // device serial #
  device.STPRS = send("STPRS", 1000);
  showStep(); // current protocol
  return device;
}

String getVOLTS() {
  String v1 = send("STVR", 1000);
  return v1;
}

String getPCMHW() {
  String v1 = send("3C04", 1000);
  long id = 0;
  Serial.println(v1);
  v1.remove(0, 4); // 008EC880
  Serial.println(v1);
  id = StrToInt(v1);
  Serial.println(id, DEC);
  return id;
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
