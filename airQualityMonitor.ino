#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include  <Adafruit_SSD1306.h>
#include  <DHT.h>
#include "pitches.h"
#define SCREEN_WIDTH 128 
#define  SCREEN_HEIGHT 64 

#define OLED_RESET     4  
Adafruit_SSD1306 display(SCREEN_WIDTH,  SCREEN_HEIGHT, &Wire, OLED_RESET);

#define sensor    A0 
#define DHTPIN  2          
#define DHTTYPE DHT11    

#define led_green 3
#define led_yellow 4
#define led_red 5
#define BUZZER 8

int gasLevel  = 0;         
String quality =""; 
DHT dht(DHTPIN,  DHTTYPE);

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
  Serial.println("Failed  to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity=");
  Serial.print(h);
  Serial.print(",");
  Serial.print("Temperature=");
  Serial.print(t);

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont();
  display.setCursor(0, 35);
  display.println("Temp  :");
  display.setCursor(80, 35);
  display.println(t);
  display.setCursor(114, 35);
  display.println("C");
  display.setCursor(0,  48);
  display.println("RH    :");
  display.setCursor(80, 48);
  display.println(h);
  display.setCursor(114, 48);
  display.println("%");
}

void air_sensor()
{
  gasLevel = analogRead(sensor);

  if(gasLevel<160){
    quality = "  WELL!";
    digitalWrite(led_green, HIGH);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_red, LOW);
  }
  else if (gasLevel >160 && gasLevel<200){
    quality =  "  Poor!";
    digitalWrite(led_green, HIGH);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_red, LOW);
  }
  else if (gasLevel >200 && gasLevel<360){
    quality  = "Very bad!";
    digitalWrite(led_green, LOW);
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_red, LOW);
    tone(BUZZER, 350); 
    delay(1000);
    noTone(BUZZER);
    delay(1000);
    
  }
    else if (gasLevel >360){
    quality  = "deadly!"; 
    digitalWrite(led_green, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_red, HIGH);
    tone(BUZZER, 1500); 
    delay(1000);
    noTone(BUZZER);
    delay(1000);
  }

  Serial.print(", gasLevel=");
  Serial.print(gasLevel);
  Serial.println(" ");
  
  display.setTextColor(WHITE);
  display.setTextSize(1);  
  display.setCursor(1,1);
  display.setFont();
  display.println("Air Quality:");
  display.setTextSize(1);
  display.setCursor(20,20);
  display.setFont(&FreeMonoOblique9pt7b);
  display.println(quality);  
}

void setup() {
  Serial.begin(9600);
  pinMode(sensor,INPUT);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { 
    Serial.println(F("SSD1306 allocation failed"));
}
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_red, OUTPUT);
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_red, LOW);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(50, 0);
  display.println("Air");
  display.setTextSize(1);
  display.setCursor(23, 20);
  display.println("Qulaity monitor");
  display.display();
  delay(1200);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(20, 20);
  display.println("BY AMIN");
  display.display();
  delay(1000);
  display.clearDisplay();    
}

void loop() {
display.clearDisplay();
sendSensor();
air_sensor();
display.display();  
delay(1000);
}
