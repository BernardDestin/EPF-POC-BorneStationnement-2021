//Variables
long duration;
Ultrasonic ultrasonic(distPIN);
int cpt = 0;

//Fonction
int distanceCapteur() {
  //Fonction permettant d'obtenir la distance entre le capteur ultrason et l'objet placé devant
  int a = ultrasonic.MeasureInCentimeters();
  //Serial.print("a:");
  //Serial.println(a);
  return a;
}

boolean voitureLA(){
  //Cette fonction permet de vérifier si une voiture est présente pendant plus de 100 appels du capteur de distance.
  if (distanceCapteur() > 10){
    cpt = 0;
  } else if (cpt < 100){
    cpt++;
  } else {
    return true;
  }
  return false;
}
