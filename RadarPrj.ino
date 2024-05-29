#include <Servo.h>
const int trigPin = 2;
const int echoPin = 3;
long duration;
int distance;
Servo myServo;
double totalDistance;
void setup() 
 {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  myServo.attach(9); 
  }
  
void loop() {
  for(int i=10;i<=170;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  
  Serial.print(i); 
  Serial.print(","); 
  Serial.print(distance);
  Serial.print(".");
  }
  for(int i=170;i>10;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}
int calculateDistance(){ 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
 
  duration = pulseIn(echoPin, HIGH); 
  totalDistance= (double)duration*0.034;
  distance= totalDistance/2;
  return distance;
}
