void r_isr() {

  if (x_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        x_maxspeed = x_maxspeed + 1;
        x_speed = x_maxspeed;
      } else {
        if (x_maxspeed < 1) {
          x_maxspeed = 1;
        } else {
          x_maxspeed = x_maxspeed - 1;
          x_speed = x_maxspeed;
        }
      }
      speed_val_change = true;
    }
    lastClk = nowClk;

  } else if (y_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        y_maxspeed = y_maxspeed + 1;
        y_speed = y_maxspeed;
      } else {
        if (y_maxspeed < 1) {
          y_maxspeed = 1;
        } else {
          y_maxspeed = y_maxspeed - 1;
          y_speed = y_maxspeed;
        }
      }
      speed_val_change = true;
    }
    lastClk = nowClk;

  } else if (z_maxspeed_selected == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        z_maxspeed = z_maxspeed + 1;
        z_speed = z_maxspeed;
      } else {
        if (z_maxspeed < 1) {
          z_maxspeed = 1;
        } else {
          z_maxspeed = z_maxspeed - 1;
          z_speed = z_maxspeed;
        }
      }
      speed_val_change = true;
    }
    lastClk = nowClk;

  } else if (mode_state == true) {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        if (cursor < 7) {
          cursor++;
        } else {
          cursor = 4;
        }
        menu_mode_change = true;
        mode_updated = true;
      } else {
        if (cursor > 4) {
          cursor--;
        } else {
          cursor = 7;
        }
        menu_mode_change = true;
        mode_updated = true;
      }
    }
    lastClk = nowClk;

  } else if(bnfMode_selected == true || sMode_selected == true || autohoming_state == true){
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        if (cursor < 1) {
          cursor++;
        } else {
          cursor = 1;
        }
        menu_mode_change = true;
        mode_updated = true;
      } else {
        if (cursor > 1) {
          cursor--;
        } else {
          cursor = 1;
        }
        menu_mode_change = true;
        mode_updated = true;
      }
    }
    lastClk = nowClk;

  }else {
    nowClk = digitalRead(clk_pin);
    if (nowClk != lastClk && nowClk == 1) {
      if (digitalRead(dt_pin) != nowClk) {
        if (cursor < 4) {
          cursor++;
        } else {
          cursor = 0;
        }
        menu_change = true;
      } else {
        if (cursor > 0) {
          cursor--;
        } else {
          cursor = 4;
        }
        menu_change = true;
      }
    }
    lastClk = nowClk;
  }
}