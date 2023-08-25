void after() {
  //Fonction permettant de mettre fin à des actions à des moments précis sans mettre en pause le code
  if (besoin_reset_BUZZER == true && temps_reset_BUZZER <= millis()/1000) {
    buzzEND();
    besoin_reset_BUZZER = false;
  }
  if (besoin_reset_LCD == true && temps_reset_LCD <= millis()/1000) {
    lcd.clear();
    lcd.setRGB(lcdR, lcdG, lcdB);
    lcd.setCursor(0, 1);
    lcd.print("Place: "+etatPlace);
    besoin_reset_LCD = false;
  }
}
