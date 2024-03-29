/*
   io
   Simple commands and conversion routines
*/

#include "io.h"

const byte tweeterPin = 2;
const int note = 4699;

void beep()
{
  if (!cfg.enableBeep) return;
  tone(tweeterPin, note, 125);
  delay(60);
  noTone(tweeterPin);
}

void beepLong()
{
  if (!cfg.enableBeep) return;
  tone(tweeterPin, note, 125);
  delay(500);
  noTone(tweeterPin);
}

void toggleBeep() {
  cfg.enableBeep = editYesNo(cfg.enableBeep);
  saveConfiguration();
}

String ByteToHex(byte data)
{
  String c;
  byte b;
  b = ((byte)(data >> 4));
  c.concat( (char)(b > 9 ? b + 0x37 : b + 0x30));
  b = ((byte)(data & 0xF));
  c.concat( (char)(b > 9 ? b + 0x37 : b + 0x30));
  return c;
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
long StrToInt(String str) // take 008F46BF and return 9389759
{
  char buf[str.length() + 1];
  str.toCharArray(buf, str.length() + 1);
  return (long) strtol(buf, 0, 16);
}

String HexToString(String STR) { // convert HEX to Char/String
  String val1; /// stores 2 char HEX code "32"
  String value = ""; // entire decoded string
  int i1 = 0; // conversion of HEX to Integer "32" = 50
  int len = STR.length();
  for (int idx = 0; idx < len; idx += 2) {
    val1 = STR.substring(idx, idx + 2);
    i1 = StrToInt(val1);
    value.concat(char(i1)); // 50 = ascii char 2
  }
  return value;
}

int validate_number(char *str) {
  while (*str) {
    if (!isdigit(*str)) { //if the character is not a number, return false
      return 0;
    }
    str++; //point to next character
  }
  return 1;
}

int validate_ip(char *ip) { //check whether the IP is valid or not
  Serial.print("validate_ip = ");
  Serial.println(ip);

  int  num, dots = 0;
  char *ptr;
  if (ip == NULL)
    return 0;
  ptr = strtok(ip, "."); //cut the string using dor delimiter
  if (ptr == NULL)
    return 0;
  while (ptr) {
    if (!validate_number(ptr)) //check whether the sub string is holding only number or not
      return 0;
    num = atoi(ptr); //convert substring to number
    if (num >= 0 && num <= 255) {
      ptr = strtok(NULL, "."); //cut the next part of the string
      if (ptr != NULL)
        dots++; //increase the dot count
    } else
      return 0;
  }
  if (dots != 3) //if the number of dots are not 3, return false
    return 0;
  return 1;
}

void reboot(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rebooting...");
  lcd.setCursor(0, 1);
  lcd.print(msg);
  delay(1000);
  _reboot_Teensyduino_();
}

void printFile(String fn) {
  /*
    File file1 = SD.open(fn);
    if (!file1) {
    Serial.print(F("Failed to read file"));
    Serial.print(" == ");
    Serial.println(fn);
    return;
    }
    while (file1.available()) {
    Serial.print((char)file1.read());
    }
    Serial.println();
    file1.close();
  */
}



char * strremove(char * str, const char * sub) {
  char * p, * q, * r;
  if ( * sub && (q = r = strstr(str, sub)) != NULL) {
    size_t len = strlen(sub);
    while ((r = strstr(p = r + len, sub)) != NULL) {
      while (p < r)
        *
        q++ = * p++;
    }
    while (( * q++ = * p++) != '\0')
      continue;
  }
  return str;
}

void StrClear(char * str, char length) {
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}

char StrContains(char * str, char * sfind) {
  char found = 0;
  char index = 0;
  char len;
  len = strlen(str);
  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    } else {
      found = 0;
    }
    index++;
  }
  return 0;
}


String urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

String urldecode(String str)
{

  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == '+') {
      encodedString += ' ';
    } else if (c == '%') {
      i++;
      code0 = str.charAt(i);
      i++;
      code1 = str.charAt(i);
      c = (h2int(code0) << 4) | h2int(code1);
      encodedString += c;
    } else {

      encodedString += c;
    }

    yield();
  }

  return encodedString;
}

unsigned char h2int(char c)
{
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}

void waitforOK(){
  int irV;
  while (1) {
  if (ir.available()) {
    irV = ir.readPacket();
    beep();
    if (irV == hexOK) return; // exit out
    irV = 0; // reset it  
  } else
   delay(10); 
  }
}
