void menu() {
  switch (cursor) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED X");

      lcd.setCursor(0, 1);
      lcd.print("           ");

      lcd.setCursor(0, 2);
      lcd.print("           ");

      lcd.setCursor(0, 3);
      lcd.print("           ");
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED Y");

      lcd.setCursor(0, 1);
      lcd.print("           ");

      lcd.setCursor(0, 2);
      lcd.print("           ");

      lcd.setCursor(0, 3);
      lcd.print("           ");
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("SET SPEED Z");

      lcd.setCursor(0, 1);
      lcd.print("           ");

      lcd.setCursor(0, 2);
      lcd.print("           ");

      lcd.setCursor(0, 3);
      lcd.print("           ");

      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("[ CONFIRM ]");

      lcd.setCursor(0, 1);
      lcd.print("X : Level ");
      lcd.print(x_maxspeed);
      lcd.setCursor(0, 2);
      lcd.print("Y : Level ");
      lcd.print(y_maxspeed);
      lcd.setCursor(0, 3);
      lcd.print("Z : Level ");
      lcd.print(z_maxspeed);

      break;
  }
  menu_change = false;
}