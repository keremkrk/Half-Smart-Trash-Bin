
#include <Servo.h>    //servo library
Servo servo;     
int trigPin = 5;      //defining distance sensor 
int echoPin = 6;      //defining distance sensor
int servoPin = 7;     //defining the servo motor
int led = 10;          //defining led
long duration, dist, average;  
long aver[3];         //array for average


void setup() {       
    Serial.begin(9600);
    servo.attach(servoPin);  
    pinMode(10,OUTPUT);
    pinMode(trigPin, OUTPUT); //defining the pin of the distance sensor 
    pinMode(echoPin, INPUT);  //defining the pin of the distance sensor  
    servo.write(0);           //close cap on power on
    delay(100);
    servo.detach(); 
} 

void measure() {                  //turns on the led
 digitalWrite(trigPin, LOW);       // starts the measuring process
 delayMicroseconds(5);        
 digitalWrite(trigPin, HIGH); 
 delayMicroseconds(15);
 digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);              //defines echo pin as INPUT
 duration = pulseIn(echoPin, HIGH);    //calculates the time
 dist = (duration/2) / 29.1;           //obtain distance
}
void loop() { 
  for (int i=0;i<=2;i++) {      //average distance
    measure();               
   aver[i]=dist;            
    delay(10);                 //delay between measurements
  }
 dist = (aver[0]+aver[1]+aver[2])/3;    

if ( dist<50 ) {            //Change distance as per your need
 digitalWrite(10,HIGH);
 servo.attach(servoPin);
  delay(1);
 servo.write(0);            //the servo motor comes to the starting position
 delay(3000);       
 servo.write(150);          //rotates motor gear 150 degrees 
 delay(1000);
 servo.detach();   
 digitalWrite(10,LOW);   
}
Serial.print(dist);
}
