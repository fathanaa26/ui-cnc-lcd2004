void menu_mode(){
  switch(cursor){
    case 4:
      lcd.setCursor(0,0);
      lcd.print("Back n Forth");
      lcd.setCursor(0,1);
      lcd.print("Mode");
      break;

    case 5:
      lcd.setCursor(0,0);
      lcd.print("Snake");
      lcd.setCursor(0,1);
      lcd.print("Mode");
      break;
  }
  menu_mode_change = false;
}