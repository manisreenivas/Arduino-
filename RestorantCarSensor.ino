#include<avr/wdt.h>
#define DISTANCE 100

const int trigPin1 = 7;
const int echoPin1 = 6;

const int trigPin2 = 5;
const int echoPin2 = 4;

int MOVE_FLAG = 0;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  MOVE_FLAG = 0;
  wdt_enable(WDTO_8S);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration1, duration2, inches1, inches2, cm1, cm2;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  

  inches1 = microsecondsToInches(duration1);
  cm1 = microsecondsToCentimeters(duration1);

  delay(10);

  pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  // convert the time into a distance
  

  inches2 = microsecondsToInches(duration2);
  cm2 = microsecondsToCentimeters(duration2);

  
  if(cm1 <= DISTANCE && cm2 <= DISTANCE && MOVE_FLAG == 0)
  {

  Serial.println("3");
  MOVE_FLAG = 1;
  }

  if (cm1 > DISTANCE && cm2 > DISTANCE && MOVE_FLAG == 1)
  {
    MOVE_FLAG = 0;
    delay(500);
  }
  
  delay(50);
  wdt_reset();
}

long microsecondsToInches(long microseconds)
{
 
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

