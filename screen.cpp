/*
   screen
   Contains LCD controlling
   Simple calls to update screen with information
*/

#include "screen.h"

LiquidCrystal_I2C_Hangul lcd(0x3F, 20, 4);  // LCD 20x4

// arrow up
byte newChar1[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

// arrow down
byte newChar2[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

// arrow right
byte newChar3[8] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
  B00000
};

// arrow left
byte newChar4[8] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B01000,
  B00100,
  B00000,
  B00000
};

// checkmark
byte newChar5[8] = {
  B00001,
  B00001,
  B00010,
  B00010,
  B10010,
  B01010,
  B00100,
  B00100
};

void setupchars() {
  lcd.createChar(0, newChar1);
  lcd.createChar(1, newChar2);
  lcd.createChar(2, newChar3);
  lcd.createChar(3, newChar4);
  lcd.createChar(4, newChar5);
}

void showStep() { // show A dot on screen to represent a step/action taking place
  lcd.print(".");
}

void showVIN() { // show VIN on LCD
  String VIN = getVIN();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(".[ VIN ].");
  lcd.setCursor(0, 1);
  lcd.print(VIN);
  delay(5000);
}

void showOSID() { // show OSID on LCD
  String OSID = getOSID();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(".[ OSID ].");
  lcd.setCursor(0, 1);
  lcd.print(OSID);
  delay(5000);
}


void showVolts() { // show OSID on LCD
  String V = send("ATRV", 1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(".[ Volts ].");
  lcd.setCursor(0, 1);
  lcd.print(V);
  delay(5000);
}

void showAbout() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UVScan v");
  lcd.print(myVersion);
  lcd.setCursor(0, 2);
  lcd.print("Steven Chesser");
  delay(5000);
}

void showSerialInfo() { // Show details about the ELM/STN1110 chip
  lcd.clear();
  lcd.setCursor(0, 0);
  struct Tdeviceinfo device = getDeviceInfo();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 0); lcd.print("STDI: "); lcd.print(device.STDI);
  lcd.setCursor(0, 1); lcd.print("STDICES: "); lcd.print(device.STDICES);
  lcd.setCursor(0, 2); lcd.print("STDICPO: "); lcd.print(device.STDICPO);
  lcd.setCursor(0, 3); lcd.print("STI: "); lcd.print(device.STI);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("STIX");
  lcd.setCursor(0, 1); lcd.print(device.STIX.substring(0, 20));
  lcd.setCursor(0, 2); lcd.print(device.STIX.substring(20));
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("STMFR");
  lcd.setCursor(0, 1); lcd.print(device.STMFR);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("STSN");
  lcd.setCursor(0, 1); lcd.print(device.STSN);
  lcd.setCursor(0, 2); lcd.print("STPRS");
  lcd.setCursor(0, 3); lcd.print(device.STPRS);
  delay(5000);
}

void showControllerInfo(){
  int coreTemp;
  lcd.clear();
  lcd.setCursor(0, 0);  lcd.print("Core Temp : ");  coreTemp = round ( (tempmonGetTemp() * 1.8) + 32 );  lcd.print(coreTemp);  lcd.print("*F");
  lcd.setCursor(0, 1);  lcd.print("USB# : ");  lcd.print(teensyUsbSN());
  lcd.setCursor(0, 2);  lcd.print("MAC Address");
  lcd.setCursor(0, 3);  lcd.print(teensyMAC());
  delay(5000);
}

void showVehicleInfo() { // Show VIN/OSID/Voltage/things like that
  initSTN(); // reset pcm and controller
  lcd.clear();
  lcd.setCursor(0, 0);
  String VIN = getVIN(); showStep();
  String OSID = getOSID(); showStep();
  String volts = getVOLTS(); showStep();
  String PCMHW = getPCMHW(); showStep();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VIN");
  lcd.setCursor(0, 1);
  lcd.print(VIN);
  lcd.setCursor(0, 2);
  lcd.print("OSID: ");
  lcd.print(OSID);
  lcd.setCursor(0, 3);
  lcd.print("HWID: ");
  lcd.print(PCMHW);
  lcd.setCursor(14,0); 
  lcd.print(volts);
  lcd.print("v");
  delay(10000);
}

void showNetworkStatus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP: ");
  Serial.println(cfg.IPAddress);
  lcd.print(cfg.IPAddress);
  lcd.setCursor(0, 1);
  lcd.print(getMACAddress());
  lcd.setCursor(0, 2);
  if (cfg.useDHCP == true) {
    lcd.print("DHCP MODE");
  } else
  {
    lcd.print("STATIC IP MODE");
  }
  lcd.setCursor(0, 3);
  auto link = Ethernet.linkStatus();
  lcd.print("Link: ");
  switch (link) {
    case Unknown:
      lcd.print("Unknown");
      break;
    case LinkON:
      lcd.print("ON");
      break;
    case LinkOFF:
      lcd.print("OFF");
      break;
  }
  lcd.print(" HW: ");
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    lcd.print("None");
  } else if (Ethernet.hardwareStatus() == EthernetW5100) {
    lcd.print("W5100");
  } else if (Ethernet.hardwareStatus() == EthernetW5200) {
    lcd.print("W5200");
  } else if (Ethernet.hardwareStatus() == EthernetW5500) {
    lcd.print("W5500");
  } else
  {
    lcd.print("????");
  }
  delay(5000);
}

void lcdSetup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  setupchars();
  lcd.setCursor(0, 0);
  lcd.print("Starting up");
  lcd.setCursor(0, 1);
}

void getSDCARDINFO()  {
  SDinit(false); // re-init incase of card swapped and get updated info
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printf("SD Card");
  lcd.setCursor(0, 1);
  lcd.printf("Size : %d", SD.totalSize());
  lcd.setCursor(0, 2);
  lcd.printf("Used : %d", SD.usedSize());
  delay(5000);
}

void getFLASHMEMINFO()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printf("Flash MEM ");
  if (flasheMEMEnabled == true) {
    lcd.print("Enabled");
    lcd.setCursor(0, 1);
    lcd.printf("Size : %d", flashStorage.totalSize());
    lcd.setCursor(0, 2);
    lcd.printf("Used : %d", flashStorage.usedSize());   
  } else
  {
    lcd.print("Disabled");
  }
  delay(5000);
}


void updateIP(String IP) {
  IP.trim();
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print(IP);
}

String setIP(String IP) {
  int irV = 0;
  int len = 0;
  String OIP;
  OIP = IP;
  IP.trim();
  lcd.setCursor(0, 1);
  lcd.print("IP Address");
  lcd.setCursor(0, 2);
  lcd.print(cfg.IPAddress);
  len = cfg.IPAddress.length();
  lcd.cursor();
  lcd.setCursor(len, 2);
  while (1) {
    delay(100);
    if (ir.available()) {
      irV = ir.readPacket();
      beepOnce();

      if (irV == hexLEFT) // delete
      {
        IP.remove(IP.length() - 1);
      } else if (irV == hex1)
      {
        IP.concat("1");
      } else if (irV == hex2)
      {
        IP.concat("2");
      } else if (irV == hex3)
      {
        IP.concat("3");
      } else  if (irV == hex4)
      {
        IP.concat("4");
      } else  if (irV == hex5)
      {
        IP.concat("5");
      } else  if (irV == hex6)
      {
        IP.concat("6");
      }  else if (irV == hex7)
      {
        IP.concat("7");
      }  else if (irV == hex8)
      {
        IP.concat("8");
      } else  if (irV == hex9)
      {
        IP.concat("9");
      }  else if (irV == hex0)
      {
        IP.concat("0");
      } else if (irV == hexSTAR)
      {
        IP.concat(".");
      }
      if (irV == hexPOUND)
      {
       Serial.println("Aborting IP Setting");
       irV = 0;
       IP = OIP;
       break; 
      }
      if (irV == hexOK)
      {
        char IPC[16];
        IP.toCharArray(IPC, IP.length() + 1);
        if (validate_ip(IPC)) {
          break;
        } else
        {
          beepLong();
        }
      }
      len = IP.length(); // update length no matter what
      updateIP(IP);
      irV = 0; // reset it
    }
  }
  lcd.noCursor();
  return IP;
}

void printStage(String msg) {
  lcd.setCursor(0, 2);
  for (int x = 0; x < 20; x++)
  {
    lcd.print(" ");
  }
  lcd.setCursor(0, 2);
  if (msg.length() > 20) {
    for (int x = 0; x < 20; x++)
      lcd.print(msg[x]);
  } else
  {
    lcd.print(msg);
  }
  delay(50);
}
