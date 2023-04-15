void axis_selection(){
  if(x_maxspeed_selected == true){
    lcd.setCursor(0,3);
    lcd.print(">");
  }else if(y_maxspeed_selected == true){
    lcd.setCursor(0,3);
    lcd.print(">");
  }else if(z_maxspeed_selected == true){
    lcd.setCursor(0,3);
    lcd.print(">");
  }else{
    lcd.setCursor(0,3);
    lcd.print("          ");
  }

  isSpeedUpdated = false;
}