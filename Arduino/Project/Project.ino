#include <SoftwareSerial.h>
#include <Wire.h>
#include <ds3231.h>
#include <LiquidCrystal_I2C.h>
#define BUFF_MAX 128

#define I2C_ADDR    0x3f
#define Rs_pin  0
#define Rw_pin  1
#define En_pin  2
#define BACKLIGHT_PIN  3
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define  LED_OFF  0
#define  LED_ON  1

SoftwareSerial ArduinoSerial(9, 8);
/*-----( Declare objects )-----*/  
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
//************************************ END LCD DISPLAY *******************************************

uint8_t time[8];
char recv[BUFF_MAX];
unsigned int recv_size = 0;
unsigned long prev, interval = 1000;
unsigned int lenAlarmSize = 13;
String val;
char* alarm;
char* p;
int minute;
int mon;
int year;
int day;
int hour;

void setup()
{
  char* dateAndTime = "504316122042018";
    Serial.begin(9600);
    Wire.begin();
    DS3231_init(DS3231_INTCN);
    memset(recv, 0, BUFF_MAX);
    Serial.println("GET time");
    ArduinoSerial.begin(4800);
  //Set the lcd
   lcd.begin (16,2);  // initialize the lcd 
   // make the blacklight turn on
   lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
   lcd.setBacklight(LED_ON);
    
    Serial.println("Setting time");
    setTheTime(dateAndTime);     // ssmmhhWDDMMYYYY set time once in the given format
    pinMode(4, OUTPUT);
  
}

void loop()
{
  while (ArduinoSerial.available() > 0){
    minute = ArduinoSerial.parseInt();
    hour = ArduinoSerial.parseInt();
    day = ArduinoSerial.parseInt();
    mon = ArduinoSerial.parseInt();
    year = ArduinoSerial.parseInt();
    if (ArduinoSerial.read() == '\n')
    {
      Serial.println(minute);
      Serial.println(hour);
      Serial.println(day);
      Serial.println(mon);
      Serial.println(year);
    }
  }
    char tempF[6]; 
    float temperature;
    char buff[BUFF_MAX];
    unsigned long now = millis();
    struct ts t;
    struct ts d;
    // show time once in a while
    if (now - prev > interval){
        DS3231_get(&t); //Get time
        temperature = DS3231_get_treg(); //Get temperature
        dtostrf(temperature, 5, 1, tempF);

        lcd.clear();
        lcd.setCursor(0,0); //First line
        
        lcd.print(t.mday); //Print day
        
        printMonth(t.mon); // Print Month
        
        lcd.print(t.year); // Print Year
        
        lcd.setCursor(0,1); //Second line
        lcd.print(t.hour); // Print Hour
        lcd.print(":");
        if(t.min<10)
        {
          lcd.print("0"); // Print Min <10
        }
        lcd.print(t.min); // Print Min >=10
        lcd.print(":");
        if(t.sec<10)
        {
          lcd.print("0");
        }
        lcd.print(t.sec);
        
        lcd.print(' ');
        lcd.print(tempF);
        lcd.print((char)223);
        lcd.print("C ");
        prev = now;
    }
    if(t.min == minute && t.hour == hour && t.mday == day && t.mon == mon && t.year == year){
      digitalWrite(4, HIGH);
      delay(60000);
    }
    digitalWrite(4, LOW);
}

void setTheTime(char* cmd)
{
    struct ts t;

    // ssmmhhWDDMMYYYY  set time

        t.sec = inp2toi(cmd, 0);
        t.min = inp2toi(cmd, 2);
        t.hour = inp2toi(cmd, 4);
        t.wday = inp2toi(cmd, 6);
        t.mday = inp2toi(cmd, 7);
        t.mon = inp2toi(cmd, 9);
        t.year = inp2toi(cmd, 11) * 100 + inp2toi(cmd, 13);
        DS3231_set(t);
        Serial.println("OK");
}

void printMonth(int month)
{
  switch(month)
  {
    case 1: lcd.print(" January ");break;
    case 2: lcd.print(" February ");break;
    case 3: lcd.print(" March ");break;
    case 4: lcd.print(" April ");break;
    case 5: lcd.print(" May ");break;
    case 6: lcd.print(" June ");break;
    case 7: lcd.print(" July ");break;
    case 8: lcd.print(" August ");break;
    case 9: lcd.print(" September ");break;
    case 10: lcd.print(" October ");break;
    case 11: lcd.print(" November ");break;
    case 12: lcd.print(" December ");break;
    default: lcd.print(" Error ");break;
  } 
}

