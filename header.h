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

int cursor;
bool menu_change = false;
bool isSpeedUpdated = false;
bool speed_val_change = false;

int y_maxspeed ;
int y_speed ;

int z_maxspeed;
int z_speed;

int x_maxspeed ;
int x_speed ;

bool y_maxspeed_selected = false;
bool x_maxspeed_selected = false;
bool z_maxspeed_selected = false;

bool mode_state = false;
bool menu_mode_change = false;

bool mode_updated = false;
bool bnfMode_selected = false;
bool sMode_selected = false;
