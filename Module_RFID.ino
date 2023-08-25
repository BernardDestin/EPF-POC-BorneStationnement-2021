//CartesRFIDvalides
const String tagsRFID[3] = {"0026C881", "bbb", "3615"};
const int nbTags = 3;

//Variables
String bufferString = "";
uint8_t count = 0;

//Fonctions
String rfidFind() {
  //Fonction qui permet d'obtenir un tag RFID lu par le lecteur RFID
  bufferString = ""; // On vide le buffer
  if ( SoftSerial.available() ) { // Si des données ont été envoyées du lecteur RFID...
    count = 0; // On remet le compteur à 0
    while (SoftSerial.available()) { // Tant que l'on a des données disponible
      delay(5); // Petite pause de ms
      char newChar = SoftSerial.read(); // On lit un octet et on le stocke dans newChar
      if (count > 2 && count < 11) { // si c'est l'ocet 3,4,5,6,7,8,9 ou 11...
        bufferString += newChar; //...on l'ajoute au contenu de bufferString
      }
      count++; // On incrémente count
      if (bufferString.length() == 14) {
        //Serial.println(bufferString); // On affiche le contenu de bufferString dans le moniteur série (l'ID donc)
        break;  // Si on a 14 bits, on a fini et on passe à la suite du programme
      }
    }
  }
  return bufferString;
}

bool rfidCheck(String tag) {
  //Fonction permettant de vérfier si un Tag fait partie de la liste des tags autorisés
  for (int i = 0; i < nbTags; i++) {
    //Serial.println(tag + " : " + tagsRFID[i]);
    if (tag.equals(tagsRFID[i])) {
      return true;
    }
  }
  return false;
}


void RFID_clear(){
  //Fonction permettant de supprimer les variables du buffer du module RFID
  while (SoftSerial.available()) { // Tant que l'on a des données disponible
      SoftSerial.read();
  }
}
