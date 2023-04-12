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
int rotaryButtonVal;

int y_maxspeed = 5000;
int y_speed;

int z_maxspeed = 12000;
int z_speed;

int x_maxspeed = 12000;
int x_speed;

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
  btn.begin(sw_pin,INPUT_PULLUP);
  btn.setTapHandler(btn_f);

  x_speed = 1000;
  y_speed = 1000;
}

void loop() {
  r.loop();
  btn.loop();

  if(menuChanged == true){
    lcd_menu_update();
  }

  if(updateSelected == true){
    selectedMode();
  }

  while(bnfMode){
    stepper_y.setSpeed(5000);
    stepper_y.moveTo(a);  
    stepper_y.runSpeedToPosition();

    stepper_x.setSpeed(12000);
    stepper_x.moveTo(a);
    stepper_x.runSpeedToPosition();

    if(stepper_y.currentPosition() && stepper_x.currentPosition() == -10000){
      a = 10000;
    } else if(stepper_y.currentPosition() && stepper_x.currentPosition() == 10000){
      a = -10000;
    }    
  }

  while(snkMode){
    stepper_y.setSpeed(1000);
    stepper_y.moveTo(a);  
    stepper_y.runSpeedToPosition();

    stepper_x.setSpeed(1000);
    stepper_x.moveTo(a);
    stepper_x.runSpeedToPosition();

    if(stepper_y.currentPosition() && stepper_x.currentPosition() == -10000){
      a = 10000;
    } else if(stepper_y.currentPosition() && stepper_x.currentPosition() == 10000){
      a = -10000;
    }
  }

}

void lcd_menu_update(){
  switch(menuCounter){
    case 0:
      lcd.setCursor(0,0);
      lcd.print("Back n Forth");
      lcd.setCursor(0,1);
      lcd.print("Mode");
      break;

    case 1:
      lcd.setCursor(0,0);
      lcd.print("Snake");
      lcd.setCursor(0,1);
      lcd.print("Mode");
      break;
  }

  menuChanged = false;
}

void selectedMode(){
  if(bnfMode == true){
    lcd.setCursor(0,3);
    lcd.print("SELECTED");

  }else if(snkMode == true){
    lcd.setCursor(0,3);
    lcd.print("SELECTED 2");
  }else{
    lcd.setCursor(0,3);
    lcd.print("          ");
  }
  updateSelected = false;
}

void rotary_f(){

  if(snkMode == true){

  }else if(bnfMode == true){

  }else{
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

  }

}


void btn_f(){

  switch(menuCounter){
    case 0:
      bnfMode = !bnfMode;
      updateSelected = true;
      break;

    case 1:
      snkMode = !snkMode;
      updateSelected = true;
      break;
  }

  menuChanged = true;
}