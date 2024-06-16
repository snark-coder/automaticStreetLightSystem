#include <Wire.h>
#include <RTClib.h>
#include <SolarCalculator.h>
#include<time.h>

RTC_DS3231 rtc;

const int ledPin = LED_BUILTIN; 

float latitude = 17.319891;   
float longitude = 78.65896; 
int timeZoneOffset = 0;      


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);


  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
  }

}

void loop() {
   DateTime now = rtc.now();
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  
  double transit, sunrise, sunset;
  calcSunriseSunset(now.year(), now.month(), now.day(), transit, sunrise, sunset);
  int currentTime = now.hour()*60+now.minute();  
  int minutes = now.minute();
  int currentTimeH = currentTime/60; 
  int remainder = currentTime % 60;
  float decimal_part = (float)remainder / 60.0;
  float currentTimeHours = currentTimeH+decimal_part;
  

  Serial.println(currentTimeHours);
  Serial.println(sunset);

  if (currentTimeHours >= sunrise && currentTimeHours < sunset) {
    digitalWrite(ledPin,  LOW); 
  } else {
    digitalWrite(ledPin, HIGH); 
  }


  delay(60000);  
}
