void r_isr(){

  if(x_maxspeed_selected == true){
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        x_maxspeed = x_maxspeed + 1000;
        x_speed = x_maxspeed;
      } else {
        if (x_maxspeed < 1000) {
          x_maxspeed = 1000;
        } else {
          x_maxspeed = x_maxspeed - 1000;
          x_speed = x_maxspeed;
        }
      }
      speed_val_change = true;
    }
    lastClk = nowClk;

  }else if(y_maxspeed_selected == true){
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        y_maxspeed = y_maxspeed + 1000;
        y_speed = y_maxspeed;
      } else {
        if (y_maxspeed < 1000) {
          y_maxspeed = 1000;
        } else {
          y_maxspeed = y_maxspeed - 1000;
          y_speed = y_maxspeed;
        }
      }
      speed_val_change = true;
    }
    lastClk = nowClk;

  }else if(z_maxspeed_selected == true){
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        z_maxspeed = z_maxspeed + 1000;
        z_speed = z_maxspeed;
      } else {
        if (z_maxspeed < 1000) {
          z_maxspeed = 1000;
        } else {
          z_maxspeed = z_maxspeed - 1000;
          z_speed = z_maxspeed;
        }
      }
      speed_val_change = true;
    }
    lastClk = nowClk;
    
  }else{
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        if (cursor < 3) {
          cursor++;
        } else {
          cursor = 0;
        }
        menu_change = true;
      } else {
        if (cursor > 0) {
          cursor--;
        } else {
          cursor = 3;
        }
        menu_change = true;
      }
    }
    lastClk = nowClk;
  }
}