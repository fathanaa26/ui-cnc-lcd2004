
#include "header.h"

void setup() {

  pinMode(clk_pin, INPUT);
  pinMode(dt_pin, INPUT);

  lcd.init();
  lcd.backlight();

  lastClk = digitalRead(clk_pin);
  lastDt = digitalRead(dt_pin);

  r.setChangedHandler(r_isr);
  btn.begin(sw_pin, INPUT_PULLUP);
  btn.setTapHandler(btn_isr);

}

void loop() {
  r.loop();
  btn.loop();

  if(menu_change == true){
    menu();
  }

  if(isSpeedUpdated == true){
    axis_selection();
  }

  if(speed_val_change == true){
    speed_change();
  }

  

}





