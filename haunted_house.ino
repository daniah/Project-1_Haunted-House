//  Created 01 October 2014 by Daniah Saimaldahar 
//  Modified by: 
//  Glen Zhang 
//  Jenna Li
//  David A. Mellis

//pin which triggers ultrasonic sound
const int pingPin = 13;

//range in cm which is considered safe to enter, anything
//coming within less than 10 cm triggers the servo 
int safeZone = 10 ;

#include <Servo.h> 

Servo myservo1;   // create servo object to control a servo 
Servo myservo2;  // a maximum of eight servo objects can be created 
Servo myservo3;
Servo myservo4;

int pos = 0;

void setup() 
{
  // initialize serial communication
  Serial.begin(9600);
  myservo1.attach(3);
  myservo2.attach(5);
  myservo3.attach(6);
  myservo4.attach(9);   
} 

void loop()
{
  //raw duration in milliseconds, cm is the
  //converted amount into a distance
  long duration, cm;

  //initializing the pin states
  pinMode(pingPin, OUTPUT);


  //sending the signal, starting with LOW for a clean signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  //setting up the input pin, and receiving the duration in
  //microseconds for the sound to bounce off the object infront
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  //printing the current readings to ther serial display
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();


  if (cm > safeZone)
  {

    for(pos = 45; pos>= 0; pos-= 45)  // goes from 0 degrees to 45 degrees 

      myservo1.write(pos);
    myservo2.write(pos+90); 
    myservo3.write(pos);
    myservo4.write(pos); 
  }
  // tell servo to go to position in variable 'pos' 
  else if (cm < safeZone) {
    for(pos = 0; pos <= 45; pos += 45)     // goes from 45 degrees to 0 degrees 
      myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    myservo2.write(pos);
    myservo3.write(pos);
    myservo4.write(pos);
  }
  delay(500);
}


long microsecondsToCentimeters(long microseconds)
{
  
  return microseconds / 29 / 2;
}


