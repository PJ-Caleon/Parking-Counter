#include <Servo.h>

const int trigPin = D6;
const int echoPin = D7;

Servo servoPin;
long duration;
int distance;

//traffic counter
int count = 0;
int led0 = D2; 
int led1 = D10;
int led2 = D13;
int button = D15;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  servoPin.attach(D9);

  pinMode(led0,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);

  pinMode(button, INPUT);

  Serial.begin(9600); 
}

void loop() {
  servoPin.write(180);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  //servo Move
  if(distance < 10 && count < 3){
    servoPin.write(0);
    delay(1500);
    while(distance < 10){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);

      distance = (duration * 0.034) / 2;

      Serial.print("Distance: ");
      Serial.println(distance);
      servoPin.write(0);
    }
    count = count + 1;
  }

  //exit button
  if(digitalRead(button)==1 && count > 0){
    count = count - 1;
    servoPin.write(0);
    delay(3000);
  }

  //led count
  switch(count){
    case 0: digitalWrite(led0,0); digitalWrite(led1,0); digitalWrite(led2,0); break;
    case 1: digitalWrite(led0,1); digitalWrite(led1,0); digitalWrite(led2,0); break;
    case 2: digitalWrite(led0,1); digitalWrite(led1,1); digitalWrite(led2,0); break;
    case 3: digitalWrite(led0,1); digitalWrite(led1,1); digitalWrite(led2,1); break;
  }
}

