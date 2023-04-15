void speed_change(){
  switch(cursor){
    case 0:
      lcd.setCursor(2,3);
      lcd.print(x_speed);
      break;

    case 1:
      lcd.setCursor(2,3);
      lcd.print(y_speed);
      break;

    case 2:
      lcd.setCursor(2,3);
      lcd.print(z_speed);
      break;
  }

  speed_val_change = false;
}