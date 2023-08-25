////////// GESTION ENTETE HTTP
void handleRoot() {
  delay(10);
  server.send(200, "text/html", getPage());
}
//Gestion de l'update des tags affichés sur le site
void handleVal(){
  delay(10);
  server.send(200, "text/html", RfidsLogs);
}


////////// GESTION MODE POINT D'ACCES (si utilisé)
void connect_AP(const char *ssid, const char *password ) {
  Serial.begin(9600);
  delay(500);
  WiFi.mode(WIFI_AP);
  WiFi.softAP( ssid, password ); //8 caractères uniquement !
  Serial.print ( "Connected to access point : " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  MY_IP = WiFi.softAPIP().toString();
  MY_SSID = ssid;
  MY_PWD = password;
  Serial.println ( WiFi.softAPIP() );
}

////////// GESTION DU MODE STATION (si utilisé)
void connect_STA(const char *ssid, const char *password ) {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin ( ssid, password ); // ssid & password private
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println ( "" );
  Serial.print ( "Connected to station : " );
  Serial.println ( MY_SSID );
  Serial.print ( "Password : " );
  Serial.println ( MY_PWD );
  Serial.print ( "IP address: " );
  MY_IP = WiFi.localIP().toString();
  MY_SSID = ssid;
  MY_PWD = password;
  Serial.println ( WiFi.localIP() );
  delay (500);
}
