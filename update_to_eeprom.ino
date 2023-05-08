void update_to_eeprom(){
  EEPROM.update(0, levelSpeed[x_maxspeed]);
  EEPROM.update(1, levelSpeed[y_maxspeed]);
  EEPROM.update(2, levelSpeed[z_maxspeed]);
  Serial.println("[WARN] EEPROM writing");
  update_eeprom_state = false;
}