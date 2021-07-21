#include <Servo.h>
#include <BlynkSimpleStream.h>

char auth[] = "mBPzJue5rpK0yZPVpuZrXVQNjapHwJBL";
const int trigger = 7;
const int echo = 6;
const int button = 4;
int pos = 0;    // variable to store the servo position
int state = 0;
int prevPos = 0;
Servo myservo;  // create servo object to control a servo
               // a maximum of eight servo objects can be created

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
//  Serial.println("Distance:");
}
void loop() {
  Blynk.run();
  for(pos = 0; pos <= 180; pos += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree  
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    state = digitalRead(button);
    if (state == 1){
      data(pos);
    }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    state = digitalRead(button);
    if (state == 1){
      data(pos);
    }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void data(int pos)
{
  long duration, cm;
  digitalWrite(trigger, LOW);
  delay(2);
  digitalWrite(trigger, HIGH);
  delay(5);
  digitalWrite(trigger, LOW);
  // estimate distance
  duration = pulseIn(echo, HIGH);
  // convert it to centimeter
  cm = toCm(duration);
  if (cm < 1000 && !(prevPos - pos < 10 && prevPos - pos > -10))
  {
    Blynk.virtualWrite(V2, pos);
    Blynk.virtualWrite(V1, cm);
    prevPos = pos;
  }
}

long toCm(long microseconds)
{
  return microseconds / 29 / 2;
}
