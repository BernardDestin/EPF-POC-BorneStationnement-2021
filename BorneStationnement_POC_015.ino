#include "Bibliotheques.h"
#include "PinD1.h"
//SoftSerial
SoftwareSerial SoftSerial(RFID_Pin1, RFID_Pin2);

//Affichage LCD
rgb_lcd lcd;
boolean besoin_reset_LCD = false;
long unsigned temps_reset_LCD = 0;
//Définition de la couleur d l'arrière plan
int lcdR = 0;
int lcdG = 0;
int lcdB = 100;

//Serveur et variable sassociées
String MY_IP;
String MY_SSID;
String MY_PWD;
ESP8266WebServer server(80); // Serveur web

//Date et variables associées
WiFiClient espClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);

//Variables loop
String rfidTAG = "";
int distanceDetection = 20;
String RfidsLogs;//Stockes les logs
String etatPlace = "libre";
long unsigned tempsAvantInvalidation = 0;

void setup() {
  // Carte Arduino D1 - RFID
  Serial.begin(9600);
  SoftSerial.begin(9600); // Lecteur RFID

  // Affichage LCD
  lcd.begin(16, 2);
  lcd.setRGB(lcdR, lcdG, lcdB);
  lcd.setCursor(0, 1);
  lcd.print("Place: " + etatPlace);

  // Buzzer
  pinMode (buzzPin, OUTPUT);
  digitalWrite (buzzPin, LOW);

  //////// Gestion SD
  //SD_init();

  //////// GESTION CONNEXION
  connect_STA("Paki", "BernardPaki");  // Donné par l'encadrant

  //////// GESTION Heure
  timeClient.begin();

  //////// GESTION SERVEUR
  server.on( "/", handleRoot );
  server.on ( "/val.txt", handleVal );
  server.begin();
  Serial.println( "Serveur http démarré" );

  //Delay de sécurité
  delay(200);
}

void loop() {
  after(); //Check de la fin du temps buzzer, du changement de couleur LCD...
  if (voitureLA()) { //voitureLA()
    if (!etatPlace.equals("O Q P")) {
      etatPlace = "O Q P";
      lcd.setCursor(0, 1);
      lcd.print("Place: " + etatPlace);
      tempsAvantInvalidation = 5000 + millis();
    }
    lectureRFID();//Recherche d'un tag RFID valide
  } else {
    if (!etatPlace.equals("libre")) {
      etatPlace = "libre";
      lcd.setCursor(0, 1);
      lcd.print("Place: " + etatPlace);
    }
    RFID_clear();
  }

  server.handleClient();
  delay(10);
}

void lectureRFID() {
  rfidTAG = rfidFind();//Recherche d'une donnée venant du module RFID
  if (rfidTAG.length() != 0 && tempsAvantInvalidation!=4294967295) {
    tempsAvantInvalidation=4294967295;
    lcd.clear();
    lcd.setCursor(0, 0);
    if (rfidCheck(rfidTAG)) {
      lcd.setRGB(0, 100, 0);
      lcd.println("Tag valide      ");
      RfidsLogs += "Tag:" + String(rfidTAG) + ":Valide    :" + getDate() + "<br/>\n";
      Serial.println(RfidsLogs);
    } else {
      lcd.setRGB(100, 0, 0);
      lcd.println("Tag invalide    ");
      RfidsLogs += "Tag:" + String(rfidTAG) + ":Invalide:" + getDate() + "<br/>\n";
      Serial.println(RfidsLogs);
      buzz(1);
    }
    lcd.setCursor(0, 1);
    lcd.print("Place: " + etatPlace);
    besoin_reset_LCD = true;
    temps_reset_LCD = millis() / 1000 + 5;
  }
  rfidTAG = "";

  //En cas de temps laissé pour scanner un tag dépassé, considère une invalidité
  if (tempsAvantInvalidation < millis()) {
    tempsAvantInvalidation=4294967295;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.setRGB(100, 0, 0);
    lcd.println("Tag invalide    ");
    RfidsLogs += "Tag: Aucun:Invalide:" + getDate() + "<br/>\n";
    Serial.println(RfidsLogs);
    buzz(1);
    lcd.setCursor(0, 1);
    lcd.print("Place: " + etatPlace);
    besoin_reset_LCD = true;
    temps_reset_LCD = millis() / 1000 + 5;
  }
}
