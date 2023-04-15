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
  }
}