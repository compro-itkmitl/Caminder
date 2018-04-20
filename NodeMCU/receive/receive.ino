#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "ohmza"
#define WIFI_PASSWORD "ohmza555"
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
  int minu = Firebase.getInt("time/min");
  int hour = Firebase.getInt("time/hour");
  int day = Firebase.getInt("time/day");
  int month = Firebase.getInt("time/month");
  int year = Firebase.getInt("time/year");
  Serial.println(minu);
  Serial.println(hour);
  Serial.println(day);
  Serial.println(month);
  Serial.println(year);
  delay(1000);
  /*while (NodeSerial.available() > 0){
    int hour_re = NodeSerial.parseInt();
    int minu_re = NodeSerial.parseInt();
    int day_re = NodeSerial.parseInt();
    int month_re = NodeSerial.parseInt();
    int year_re = NodeSerial.parseInt();
    if(NodeSerial.read() == '\n'){
      Serial.println(hour_re);
    }
  }*/
}


