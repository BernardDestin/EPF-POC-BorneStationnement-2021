
String getDate() {
  //FOnction eprmettant d'obtenir la date et l'heure du jour
  timeClient.update();
  return String(timeClient.getEpochTime())+":"+String(timeClient.getFormattedTime());
}
