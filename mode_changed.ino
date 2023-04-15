void mode_changed(){
  if(bnfMode_selected == true){
    lcd.setCursor(1,3);
    lcd.print("SELECTED");
  }else if(sMode_selected == true){
    lcd.setCursor(1,3);
    lcd.print("SELECTED");
  }else{
    lcd.setCursor(1,3);
    lcd.print("        ");
  }
  mode_updated = false;
}