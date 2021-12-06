/*
   dtc
   diagnostic trouble codes
*/

#include "dtc.h"

String convertDTCCode(String code) {
  char c;
  String newCode = "";

  if (code == "0000") {
    return "0000";
  }

  c = code[0];
  code.remove(0, 1);
  switch (c)
  {
    case '0': newCode = "P0"; break;
    case '1': newCode = "P1"; break;
    case '2': newCode = "P2"; break;
    case '3': newCode = "P3"; break;
    case '4': newCode = "C0"; break;
    case '5': newCode = "C1"; break;
    case '6': newCode = "C2"; break;
    case '7': newCode = "C3"; break;
    case '8': newCode = "B0"; break;
    case '9': newCode = "B1"; break;
    case 'A': newCode = "B2"; break;
    case 'B': newCode = "B3"; break;
    case 'C': newCode = "U0"; break;
    case 'D': newCode = "U1"; break;
    case 'E': newCode = "U2"; break;
    case 'F': newCode = "U3"; break;
    default: newCode = "??";  break;
  }
  newCode.concat(code);
  return newCode;
}


void readDTCCodes() {
  int codeCount = 0;
  String r;
  String code1;
  String code2;
  String code3;

  String r2;

  initSTN(false);
  r = send("0101", 2000); // how many trouble codes

  if (r.length() == 12) {

    // 41010000E564
    r.remove(0, 4); // remove 4101

    // 00
    codeCount = StrToInt(r.substring(0, 2));

    Serial.println(r.substring(0, 2));
    Serial.print(codeCount, DEC);
    

    if (codeCount > 128) {
      codeCount = -129;

      Serial.print("Codes = ");
      Serial.println(codeCount, DEC);

      r = send("03", 2000); // request trouble codes stored

      /*
        r = "430123456789AB";
        r.concat(char(10));
        r.concat("43013304432211");
        r.concat(char(10));
        r.concat("43111100000000");
      */
      // 43 01 33 00 00 00 00
      Serial.println(r);

      r2 = "";

      if (r.length() > 13) {
        for (int idx = 0; idx < r.length(); idx++)
        {
          if (r[idx] != char(10) and r[idx] != char(13))
          {
            r2.concat(r[idx]);
          } else
          {
            Serial.println(r2);
            r2.remove(0, 2); // remove 43
            Serial.println(r2);

            // 01 23 45 67 89 AB

            code1 = r2.substring(0, 4);
            code2 = r2.substring(4, 8 );
            code3 = r2.substring(8, 12);

            Serial.println(code1);
            Serial.println(code2);
            Serial.println(code3);

            code1 = convertDTCCode(code1);
            code2 = convertDTCCode(code2);
            code3 = convertDTCCode(code3);

            Serial.println(code1);
            Serial.println(code2);
            Serial.println(code3);

            lcd.clear();
            lcd.setCursor(0, 0);
            if (code1 != "0000") lcd.print(code1);
            lcd.setCursor(0, 1);
            if (code2 != "0000") lcd.print(code2);
            lcd.setCursor(0, 2);
            if (code3 != "0000") lcd.print(code3);
            lcd.setCursor(0, 3); lcd.print("Press OK to continue");

            r2 = "";
            waitforOK();
          }
        }
      }
    } else
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("No codes found.");
      beepLong();
      delay(2000);
     }
  } else
  {
    lcd.setCursor(0, 3);
    lcd.print("Failed to get codes.");
    beepLong();
    delay(2000);
  }

  lcd.clear();
}


void clearDTCCodes() {
  bool clearDTC;
  String r;
  clearDTC = editYesNo(false);
  if (clearDTC) {
    initSTN(false);
    r = send("04", 2000);
    lcd.setCursor(0, 3);
    if (r == "44") {
      lcd.print("DTC codes cleared!");
    } else
    {
      lcd.print("Failed to clear!");
    }
    beepLong();
    delay(2000);
  }
}
