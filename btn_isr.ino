void btn_isr(){
  switch (cursor) {
    case 0:
      x_maxspeed_selected = !x_maxspeed_selected;
      isSpeedUpdated = true;
      break;
    
    case 1:
      y_maxspeed_selected = !y_maxspeed_selected;
      isSpeedUpdated = true;
      break;
    
    case 2:
      z_maxspeed_selected = !z_maxspeed_selected;
      isSpeedUpdated = true;
      break;

    case 3:
      mode_state = true;
      update_eeprom_state = true;
      break;
    
    case 4:
      bnfMode_selected = !bnfMode_selected;
      mode_updated = true;
      break;
    
    case 5:
      sMode_selected = !sMode_selected;
      mode_updated = true;
      break;

    case 6:
      mode_state = false;
      break; 

    case 7:
      autohoming_state = !autohoming_state;
      mode_updated = true;
      break; 
  }
}