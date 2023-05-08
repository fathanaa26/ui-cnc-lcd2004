
#include "header.h"

void setup() {
  Serial.begin(9600);
  pinMode(clk_pin, INPUT);
  pinMode(dt_pin, INPUT);

  pinMode(ls_x_pin, INPUT);
  pinMode(ls_y_pin, INPUT);
  pinMode(ls_z_pin, INPUT);

  digitalWrite(ls_y_pin, HIGH);

  lcd.init();
  lcd.backlight();

  lastClk = digitalRead(clk_pin);
  lastDt = digitalRead(dt_pin);

  last_x_ls = digitalRead(ls_x_pin);
  last_y_ls = digitalRead(ls_y_pin);
  last_z_ls = digitalRead(ls_z_pin);

  r.setChangedHandler(r_isr);
  btn.begin(sw_pin, INPUT_PULLUP);
  btn.setTapHandler(btn_isr);

  EEPROM.read(0) = x_maxspeed;
  EEPROM.read(1) = y_maxspeed;
  EEPROM.read(2) = z_maxspeed;

  Timer1.initialize(10000);
  Timer1.attachInterrupt(r_isr);

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

  stepper_x.setMaxSpeed(levelSpeed[x_maxspeed]);
  stepper_x.setSpeed(levelSpeed[x_maxspeed]);

  stepper_y.setMaxSpeed(levelSpeed[y_maxspeed]);
  stepper_y.setSpeed(levelSpeed[y_maxspeed]);

  stepper_z.setMaxSpeed(levelSpeed[z_maxspeed]);
  stepper_z.setSpeed(levelSpeed[z_maxspeed]);

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

  if(autohoming_state == true){
    stepper_y.moveTo(b);
    stepper_y.runSpeedToPosition();

    stepper_x.moveTo(b);
    stepper_x.runSpeedToPosition();

    stepper_z.moveTo(b);
    stepper_z.runSpeedToPosition();

    if(digitalRead(ls_x_pin) != last_x_ls){
      stepper_x.stop();
      stepper_x.setCurrentPosition(0);
    }
    if(digitalRead(ls_y_pin) != last_y_ls){
      stepper_y.stop();
      stepper_y.setCurrentPosition(0);
    }
    if(digitalRead(ls_z_pin) != last_z_ls){
      stepper_z.stop();
      stepper_z.setCurrentPosition(0);
    }
  }

}
