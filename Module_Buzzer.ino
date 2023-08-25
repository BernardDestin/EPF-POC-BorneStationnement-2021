//Variables du reset
boolean besoin_reset_BUZZER = false;
long unsigned temps_reset_BUZZER = 0;

void buzz(int nbsec) {
  //Fonction permettant d'activier le buzzer et de définir son temps avant désactivation
  tone(buzzPin, 1000);
  besoin_reset_BUZZER = true;
  temps_reset_BUZZER = millis()/1000 + nbsec;
}

void buzzEND(){
  //Fonction permettant de mettre fin au son émit par le buzzer
  digitalWrite (buzzPin, LOW);
}
