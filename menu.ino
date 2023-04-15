void menu(){
  switch (cursor) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED X");
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED Y");
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED Z");
    break;

    case 3:
      lcd.setCursor(0, 4);
      lcd.print("[ CONFIRM ]");

      lcd.setCursor(0,1);
      lcd.print("X : ");
      lcd.print(x_speed);
      lcd.setCursor(0,2);
      lcd.print("Y : ");
      lcd.print(y_speed);
      lcd.setCursor(0,3);
      lcd.print("Z : ");
      lcd.print(z_speed);
    break;
    
  }
  menu_change = false;
}