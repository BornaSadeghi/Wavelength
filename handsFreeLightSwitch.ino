#include "SR04.h"
#include "Servo.h"

#define PIN_TRIG 12
#define PIN_ECHO 11
#define PIN_SERVO 9


SR04 sr04 = SR04(PIN_ECHO, PIN_TRIG);
Servo myservo;
long distance;
boolean on = false;

const int POS_OFFSET = 45;
const int POS_OFF = 90+POS_OFFSET, POS_ON = 90-POS_OFFSET;
const int DELAY = 800;

void toggle(){
  myservo.write(on ? POS_OFF : POS_ON);
  on = !on;
}

void reset() {
  myservo.write(90);
}

void setup() {
  Serial.begin(9600);//Initialization of Serial Port
  myservo.attach(PIN_SERVO);//connect pin 9 with the control line(the middle line of Servo) 
  reset();
//  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  delay(1000);
}

void loop() {
  distance = sr04.Distance();
  Serial.print(distance);
  Serial.println("cm");

  if(distance < 10){
    toggle();
    delay(DELAY);
    reset();
  }
  
  delay(1);
}
