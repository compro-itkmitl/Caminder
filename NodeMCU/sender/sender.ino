#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "naive555"
#define WIFI_PASSWORD "12345678"
#define FIREBASE_HOST "carminder-63a0d.firebaseio.com"
#define FIREBASE_AUTH "AEkAhVK9s2as0zvl5b4jLUogp8cV9doVQUrWpLsX"

SoftwareSerial NodeSerial(D2, D3); // Rx || TX

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
  pinMode(D0, INPUT);
  pinMode(D1, OUTPUT);
  NodeSerial.begin(4800);
}
void loop() {
  int minutes = Firebase.getInt("time/min");
  int hours = Firebase.getInt("time/hour");
  int days = Firebase.getInt("time/day");
  int months = Firebase.getInt("time/month");
  int years = Firebase.getInt("time/year");
  Serial.println(minutes);
  Serial.println(hours);
  Serial.println(days);
  Serial.println(months);
  Serial.println(years);
  delay(1000);
}


