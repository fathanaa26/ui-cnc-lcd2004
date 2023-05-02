void menu_mode(){
  switch(cursor){
    case 4:
      lcd.setCursor(0,0);
      lcd.print("              ");
      lcd.setCursor(0,1);
      lcd.print("              ");
      lcd.setCursor(0,2);
      lcd.print("              ");
      lcd.setCursor(0,3);
      lcd.print("              ");

      lcd.setCursor(0,0);
      lcd.print("1.");
      lcd.setCursor(2,0);
      lcd.print("Back n Forth");
      lcd.setCursor(2,1);
      lcd.print("Mode");
      break;

    case 5:
      lcd.setCursor(0,0);
      lcd.print("              ");
      lcd.setCursor(0,1);
      lcd.print("              ");
      lcd.setCursor(0,2);
      lcd.print("              ");
      lcd.setCursor(0,3);
      lcd.print("              ");

      lcd.setCursor(0,0);
      lcd.print("2.");
      lcd.setCursor(2,0);
      lcd.print("Snake");
      lcd.setCursor(2,1);
      lcd.print("Mode");
      break;

    case 6:
      lcd.setCursor(0,0);
      lcd.print("              ");
      lcd.setCursor(0,1);
      lcd.print("              ");
      lcd.setCursor(0,2);
      lcd.print("              ");
      lcd.setCursor(0,3);
      lcd.print("              ");

      lcd.setCursor(0,0);
      lcd.print("[ BACK ]");      
      break;

    case 7:
      lcd.setCursor(0,0);
      lcd.print("              ");
      lcd.setCursor(0,1);
      lcd.print("              ");
      lcd.setCursor(0,2);
      lcd.print("              ");
      lcd.setCursor(0,3);
      lcd.print("              ");

      lcd.setCursor(0,0);
      lcd.print("3.");
      lcd.setCursor(2,0);
      lcd.print("Auto");
      lcd.setCursor(2,1);
      lcd.print("Homing");
      break;
      
  }
  menu_mode_change = false;
}