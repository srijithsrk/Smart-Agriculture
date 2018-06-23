#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#include <ESP8266WiFi.h>
#include "FirebaseArduino.h"
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

#define FIREBASE_HOST "haha-b4263.firebaseio.com"
#define FIREBASE_AUTH "AyKnQnpWgXdVhsx3yCf5jMSCYsZCWsUSDSx0rInV"
#define WIFI_SSID "one plus"
#define WIFI_PASSWORD "asdfghjkl1"
void setup(void)
{ 
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
  delay(700);
  pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(12,OUTPUT);
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
void loop() 
{
  int chk=dht.read(1);
  delay(100);
    float h = dht.readHumidity();
    int hygro=analogRead(A0);
    delay(100);
    Serial.println(hygro);
    float t = dht.readTemperature();   
    if((h<100)&&(t<100))      
    {Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    Firebase.setInt("/humidity", h);
    Firebase.setInt("/temperature", t);}
      // handle error
 /* if (Firebase.failed()) 
  {
      Serial.print("pushing /Temperature failed:");
      Serial.println(Firebase.error());  
      return;
  }*/
  
     if(t>31)
    {
      Firebase.set("/fan","ON");
      digitalWrite( 16,HIGH);
      digitalWrite( 5,LOW);
    }
    else 
    {
      Firebase.set("/fan" ,"OFF");
      digitalWrite( 16,LOW);
    }
    
     
     if(hygro>1000)
     {
      
    Firebase.set("/sprinkler" ,"ON");
      Serial.println("###############");
      digitalWrite( 14,HIGH);
      digitalWrite( 12,LOW);
    }
    else 
     {
     Firebase.set("/fan" ,"OFF");
      digitalWrite( 14,LOW);
      digitalWrite( 12,LOW);
    } 
    
    
  delay(1800);
}
