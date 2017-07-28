#include <AccelStepper.h>
#define HALFSTEP 8

// initialize the stepper library on pins 8 through 11:
#define motor1Pin1 4
#define motor1Pin2 5
#define motor1Pin3 6
#define motor1Pin4 7
#define motor2Pin1 43
#define motor2Pin2 45
#define motor2Pin3 47
#define motor2Pin4 49
#define ECHO1 3
#define TRIG1 2
#define ECHO2 9
#define TRIG2 8
#define ECHO3 23
#define TRIG3 22

long duration1, distance1, duration2, distance2, duration3, distance3;

//Initialize with pin sequence using AccelStepper
AccelStepper stepper1(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);

void setup()
{
  pinMode(ECHO1, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO3, INPUT);
  pinMode(TRIG3, OUTPUT);
  stepper1.setMaxSpeed(6000.0);
  stepper1.setSpeed(6000.0);
  stepper2.setMaxSpeed(6000.0);
  stepper2.setSpeed(6000.0);
}

void loop()
{
    readsensors();
    stepper1.setSpeed(5000.0);
    stepper2.setSpeed(5000.0);
    stepper1.run();
    stepper2.run();
}

void readsensors()
{
  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1,LOW);
  duration1 = pulseIn(ECHO1, HIGH);
  distance1 = duration1/29.1;
  
  digitalWrite(TRIG2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2,LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 = duration2/29.1;

  digitalWrite(TRIG3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3,LOW);
  duration3 = pulseIn(ECHO3, HIGH);
  distance3 = duration3/29.1; 
}

