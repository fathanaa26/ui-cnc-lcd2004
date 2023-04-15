
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

int a = -10000;
int b = -20000;

void loop() {
  r.loop();
  btn.loop();

  if (menu_change == true) {
    menu();
  }

  if (isSpeedUpdated == true) {
    axis_selection();
  }
  if (speed_val_change == true) {
    speed_change();
  }

  if (mode_state == true) {
    if (menu_mode_change == true) {
      menu_mode();
    }

    if(mode_updated == true){
      mode_changed();
    }
  }

  stepper_x.setMaxSpeed(x_maxspeed);
  stepper_x.setSpeed(x_speed);

  stepper_y.setMaxSpeed(y_maxspeed);
  stepper_y.setSpeed(y_speed);

  if(bnfMode_selected == true){
    stepper_y.moveTo(a);
    stepper_y.runSpeedToPosition();

    stepper_x.moveTo(a);
    stepper_x.runSpeedToPosition();

    if (stepper_y.currentPosition() && stepper_x.currentPosition() == -10000) {
      a = 10000;
    } else if (stepper_y.currentPosition() && stepper_x.currentPosition() == 10000) {
      a = -10000;
    }
  }

  if(sMode_selected == true){
    stepper_y.moveTo(b);
    stepper_y.runSpeedToPosition();

    stepper_x.moveTo(b);
    stepper_x.runSpeedToPosition();

    if (stepper_y.currentPosition() && stepper_x.currentPosition() == -20000) {
      b = 20000;
    } else if (stepper_y.currentPosition() && stepper_x.currentPosition() == 20000) {
      b = -20000;
    }
  }


}
