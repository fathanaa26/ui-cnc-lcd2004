#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <AccelStepper.h>
AccelStepper stepper_x(1, 2, 5);
AccelStepper stepper_y(1, 3, 6);
AccelStepper stepper_z(1, 4, 7);

#include "Rotary.h"

#define clk_pin 14
#define dt_pin 15
#define sw_pin 16

#define lw_x 9
#define lw_y 10
#define lw_z 11

Rotary r = Rotary(clk_pin, dt_pin);

int lastClk;
int nowClk;

int lastDt;
int nowDt;

int menuCounter;

int rotaryButtonVal;

int y_maxspeed;
int y_speed;

int z_maxspeed;
int z_speed;

int x_maxspeed;
int x_speed;

bool y_maxspeed_selected = false;
bool x_maxspeed_selected = false;
bool z_maxspeed_selected = false;

bool menuChanged = false;
bool valChanged = false;
bool updateValSel = false;

float RotaryTime1;
float RotaryTime2;

int long_button_pressed_timer;

void setup() {
  pinMode(clk_pin, INPUT);
  pinMode(dt_pin, INPUT);
  pinMode(sw_pin, INPUT_PULLUP);

  pinMode(lw_x, INPUT);
  pinMode(lw_y, INPUT);
  pinMode(lw_z, INPUT);

  lcd.init();
  lcd.backlight();

  lastClk = digitalRead(clk_pin);
  lastDt = digitalRead(dt_pin);

  r.setChangedHandler(rotary_fun);

  stepper_y.setSpeed(y_speed);
  stepper_y.setMaxSpeed(y_maxspeed);

  stepper_x.setMaxSpeed(x_maxspeed);
  stepper_x.setSpeed(x_speed);

  stepper_z.setMaxSpeed(z_maxspeed);
  stepper_z.setSpeed(z_speed);
}

void loop() {
  r.loop();

  if (menuChanged == true) {
    updateMenu();
  }
  if (valChanged == true) {
    updateVal();
  }
  if (updateValSel == true) {
    updateSelect();
  }

  button_pressed();
  limitSwitch();

  stepper_y.runSpeed();
  stepper_x.runSpeed();
  stepper_z.runSpeed();

}

void limitSwitch(){

  if((millis() - lw_intv) > 200){
    if(digitalRead(lw_x) == 0){
      stepper_x.stop();
      lw_intv = millis();
    }else if(digitalRead(lw_y) == 0){
      stepper_y.stop();
      lw_intv = millis();
    }else if(digitalRead(lw_z) == 0){
      stepper_z.stop();
      lw_intv = millis();
    }
  }

}

void updateMenu() {
  lcd.clear();
  switch (menuCounter) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("SET MOTOR SPEED");
      lcd.setCursor(0, 1);
      lcd.print("X-AXIS");

      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("SET MOTOR SPEED");
      lcd.setCursor(0, 1);
      lcd.print("Y-AXIS");

      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("SET MOTOR SPEED");
      lcd.setCursor(0, 1);
      lcd.print("Z-AXIS");

      break;
  }

  menuChanged = false;
}

void rotary_fun() {
  if (x_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        x_maxspeed = x_maxspeed + 100;
        x_speed = x_maxspeed;
      } else {
        if (x_maxspeed < 2) {
          x_maxspeed = 1;
        } else {
          x_maxspeed = x_maxspeed - 100;
          x_speed = x_maxspeed;
        }
      }
      valChanged = true;
    }
    lastClk = nowClk;
  } else if (y_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        y_maxspeed = y_maxspeed + 100;
        y_speed = y_maxspeed;
      } else {
        if (y_maxspeed < 2) {
          y_maxspeed = 1;
        } else {
          y_maxspeed = y_maxspeed - 100;
          y_speed = y_maxspeed;
        }
      }
      valChanged = true;
    }
    lastClk = nowClk;
  } else if (z_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        z_maxspeed = z_maxspeed + 100;
        z_speed = z_maxspeed;
      } else {
        if (z_maxspeed < 2) {
          z_maxspeed = 1;
        } else {
          z_maxspeed = z_maxspeed - 100;
          z_speed = z_maxspeed;
        }
      }
      valChanged = true;
    }
    lastClk = nowClk;
  } else {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        if (menuCounter < 3) {
          menuCounter++;
        } else {
          menuCounter = 0;
        }
        menuChanged = true;
      } else {
        if (menuCounter > 0) {
          menuCounter--;
        } else {
          menuCounter = 3;
        }
        menuChanged = true;
      }
    }
    lastClk = nowClk;
  }
}

void updateSelect() {
  if (x_maxspeed_selected == true) {
    lcd.setCursor(3, 3);
    lcd.print(">");
  } else if (y_maxspeed_selected == true) {
    lcd.setCursor(3, 3);
    lcd.print(">");
  } else if (z_maxspeed_selected == true) {
    lcd.setCursor(3, 3);
    lcd.print(">");
  } else {
    lcd.setCursor(3, 3);
    lcd.print(" ");
  }
  updateValSel = false;
}

void updateVal() {
  switch (menuCounter) {
    case 0:
      stepper_x.setMaxSpeed(x_maxspeed);
      stepper_x.setSpeed(x_speed);
      lcd.setCursor(4, 3);
      lcd.print(x_maxspeed);
      break;
    case 1:
      stepper_y.setMaxSpeed(y_maxspeed);
      stepper_y.setSpeed(y_speed);
      lcd.setCursor(4, 3);
      lcd.print(y_maxspeed);
      break;
    case 2:
      stepper_z.setMaxSpeed(z_maxspeed);
      stepper_z.setSpeed(z_speed);
      lcd.setCursor(4, 3);
      lcd.print(z_maxspeed);
      break;
  }
  valChanged = false;
}

void long_button_pressed(int milis) {
  long_button_pressed_timer = millis();
}

void button_pressed() {
  if (digitalRead(sw_pin) == 0) {
    RotaryTime1 = millis();
    if (RotaryTime1 - RotaryTime2 > 1000) {
      switch (menuCounter) {
        case 0:
          x_maxspeed_selected = !x_maxspeed_selected;
          updateValSel = true;

          break;
        case 1:
          y_maxspeed_selected = !y_maxspeed_selected;
          updateValSel = true;

          break;
        case 2:
          z_maxspeed_selected = !z_maxspeed_selected;
          updateValSel = true;

          break;
      }
      RotaryTime2 = millis();
      menuChanged = true;
    }
  }
}
