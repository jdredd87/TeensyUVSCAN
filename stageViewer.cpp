#include "stageViewer.h"
#include "menus.h"

struct MenuCommandRec PIDMENU[NUM_PIDS + 3]; // we add 2 menu options before hand

template< typename T, size_t SelectPIDMenuNumberOfSize >
size_t SelectPIDMENUSIZE(T (&) [SelectPIDMenuNumberOfSize]) {
  return PIDMenuNumberOfSize;
}
int SelectPIDMENUCOUNT = SelectPIDMENUSIZE(SelectPIDMENU) - 1;

void showStageViewer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pick up to 4 pids");
  lcd.setCursor(0, 1);
  lcd.print("to display while");
  lcd.setCursor(0, 2);
  lcd.print("scanning vehicle");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select 4. * to exit.");
  

  
}
