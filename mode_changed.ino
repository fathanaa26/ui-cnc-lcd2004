void mode_changed(){
  if(bnfMode_selected == true){
    lcd.setCursor(0,3);
    lcd.print("[1]");
    lcd.setCursor(3,3);
    lcd.print("MODE SELECTED");
  }else if(sMode_selected == true){
    lcd.setCursor(0,3);
    lcd.print("[2]");
    lcd.setCursor(3,3);
    lcd.print("MODE SELECTED");
  }else if(autohoming_state == true){
    lcd.setCursor(0,3);
    lcd.print("[3]");
    lcd.setCursor(3,3);
    lcd.print("PLEASE WAIT");
  } else{
    lcd.setCursor(0,3);
    lcd.print("                  ");
  }
  mode_updated = false;
}