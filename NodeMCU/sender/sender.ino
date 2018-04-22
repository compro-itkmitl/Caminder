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
  String minutes = Firebase.getString("time/min");
  String hours = Firebase.getString("time/hour");
  String days = Firebase.getString("time/day");
  String months = Firebase.getString("time/month");
  String years = Firebase.getString("time/year");
  Serial.print(minutes);
  Serial.print(hours);
  Serial.print(days);
  Serial.print(months);
  Serial.print(years);
  Serial.print('\n');
  NodeSerial.print(minutes+hours+days+months+years);
  delay(1000);
}


