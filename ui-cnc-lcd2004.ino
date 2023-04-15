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

Rotary r = Rotary(clk_pin, dt_pin);

#include "Button2.h"

Button2 btn;

int lastClk;
int nowClk;

int lastDt;
int nowDt;

int menuCounter;
bool menuChanged = false;
bool updateSelected = false;
bool valChanged = false;
int rotaryButtonVal;

int y_maxspeed ;
int y_speed ;

int z_maxspeed;
int z_speed;

int x_maxspeed ;
int x_speed ;

bool bnfMode = false;
bool snkMode = false;

bool y_maxspeed_selected = false;
bool x_maxspeed_selected = false;
bool z_maxspeed_selected = false;

int a = -10000;

void setup() {

  pinMode(clk_pin, INPUT);
  pinMode(dt_pin, INPUT);

  lcd.init();
  lcd.backlight();

  lastClk = digitalRead(clk_pin);
  lastDt = digitalRead(dt_pin);

  stepper_y.setMaxSpeed(y_maxspeed);
  stepper_y.setCurrentPosition(0);

  stepper_x.setMaxSpeed(x_maxspeed);
  stepper_x.setCurrentPosition(0);

  r.setChangedHandler(rotary_f);
  btn.begin(sw_pin, INPUT_PULLUP);
  btn.setTapHandler(btn_f);
}

void loop() {
  r.loop();
  btn.loop();

  if (menuChanged == true) {
    lcd_menu_update();
  }

  if (updateSelected == true) {
    selectedMode();
  }

  if(valChanged == true){
    val_speed_change();
  }

  if (bnfMode == true) {

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

  if (snkMode == true) {

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
}

void val_speed_change(){
  switch (menuCounter) {
    case 3:
      stepper_x.setMaxSpeed(x_maxspeed);
      stepper_x.setSpeed(x_speed);
      lcd.setCursor(4, 3);
      lcd.print(x_maxspeed);
      break;

    case 4:
      stepper_y.setMaxSpeed(y_maxspeed);
      stepper_y.setSpeed(y_speed);
      lcd.setCursor(4, 3);
      lcd.print(y_maxspeed);
      break;

    case 5:
      stepper_z.setMaxSpeed(z_maxspeed);
      lcd.setCursor(4, 3);
      lcd.print(z_maxspeed);
      break;
  }
  valChanged = false;
}

void lcd_menu_update() {
  switch (menuCounter) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("Back n Forth");
      lcd.setCursor(0, 1);
      lcd.print("Mode");
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Snake");
      lcd.setCursor(0, 1);
      lcd.print("Mode");
      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED X");
      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED Y");
      break;

    case 5:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED Z");
      break;

  }

  menuChanged = false;
}

void selectedMode() {
  if (bnfMode == true) {
    lcd.setCursor(0, 3);
    lcd.print("SELECTED");

  } else if (snkMode == true) {
    lcd.setCursor(0, 3);
    lcd.print("SELECTED");

  } else if (y_maxspeed_selected == true) {
    lcd.setCursor(0, 3);
    lcd.print(">");

  } else if (x_maxspeed_selected == true) {
    lcd.setCursor(0, 3);
    lcd.print(">");

  } else if (z_maxspeed_selected == true) {
    lcd.setCursor(0, 3);
    lcd.print(">");

  } else {
    lcd.setCursor(0, 3);
    lcd.print("          ");
    
  }

  updateSelected = false;
}

void rotary_f() {
  if (snkMode == true) {

    nowClk = digitalRead(clk_pin);

    if (nowClk != lastClk && nowClk == 1) {

      if (digitalRead(dt_pin) != nowClk) {
        if (menuCounter < 1) {
          menuCounter++;
        } else {
          menuCounter = 0;
        }
        menuChanged = true;
        lcd.setCursor(0,0);
        lcd.print("            ");

      } else {
        if (menuCounter > 0) {
          menuCounter--;
        } else {
          menuCounter = 1;
        }
        menuChanged = true;
        lcd.setCursor(0,0);
        lcd.print("            ");
      }
    }

    lastClk = nowClk;

  } else if (bnfMode == true) {

    nowClk = digitalRead(clk_pin);

    if (nowClk != lastClk && nowClk == 1) {

      if (digitalRead(dt_pin) != nowClk) {
        if (menuCounter < 1) {
          menuCounter++;
        } else {
          menuCounter = 0;
        }
        menuChanged = true;

      } else {
        if (menuCounter > 0) {
          menuCounter--;
        } else {
          menuCounter = 1;
        }
        menuChanged = true;
      }
    }

    lastClk = nowClk;

  } else if (x_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        x_maxspeed = x_maxspeed + 1000;
        x_speed = x_maxspeed;
      } else {
        if (x_maxspeed < 1000) {
          x_maxspeed = 1000;
        } else {
          x_maxspeed = x_maxspeed - 1000;
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
        y_maxspeed = y_maxspeed + 1000;
        y_speed = y_maxspeed;
      } else {
        if (y_maxspeed < 1000) {
          y_maxspeed = 1000;
        } else {
          y_maxspeed = y_maxspeed - 1000;
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
        z_maxspeed = z_maxspeed + 1000;
        z_speed = z_maxspeed;
      } else {
        if (z_maxspeed < 1000) {
          z_maxspeed = 1000;
        } else {
          z_maxspeed = z_maxspeed - 1000;
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
        if (menuCounter < 5) {
          menuCounter++;
        } else {
          menuCounter = 2;
        }
        menuChanged = true;

      } else {
        if (menuCounter > 2) {
          menuCounter--;
        } else {
          menuCounter = 5;
        }
        menuChanged = true;
      }
    }

    lastClk = nowClk;
  }
}


void btn_f() {

  switch (menuCounter) {
    case 0:
      bnfMode = !bnfMode;
      updateSelected = true;
      break;

    case 1:
      snkMode = !snkMode;
      updateSelected = true;
      break;
    
    case 3:
      x_maxspeed_selected = !x_maxspeed_selected;
      updateSelected = true;

    case 4:
      y_maxspeed_selected = !y_maxspeed_selected;
      updateSelected = true;

    case 5:
      z_maxspeed_selected = !z_maxspeed_selected;
      updateSelected = true;            
  }

  menuChanged = true;
}