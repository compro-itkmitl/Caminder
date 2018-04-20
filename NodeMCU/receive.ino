#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define WIFI_SSID "ohmza"
#define WIFI_PASSWORD "ohmza555"
#define FIREBASE_HOST "carminder-63a0d.firebaseio.com"
#define FIREBASE_AUTH "AEkAhVK9s2as0zvl5b4jLUogp8cV9doVQUrWpLsX"

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);}
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
  String minu = Firebase.getString("time/min");
  String hour = Firebase.getString("time/hour");
  String day = Firebase.getString("time/day");
  String month = Firebase.getString("time/month");
  String year = Firebase.getString("time/year");
  Serial.println(minu);
  Serial.println(hour);
  Serial.println(day);
  Serial.println(month);
  Serial.println(year);
  delay(1000); 
}


