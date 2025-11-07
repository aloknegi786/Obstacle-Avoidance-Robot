// functional code : 

#include <NewPing.h>  // Ultrasonic sensor library

// Motor driver pins
const int LeftMotorForward = 2;
const int LeftMotorBackward = 3;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// Ultrasonic sensor pins
#define trigPin A1
#define echoPin A2
#define MAX_DISTANCE 200

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
int distance = 0;
int count = 0;

void setup() {
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
}

void loop() {
  distance = readDistance();


  if (distance <= 20 && count != 1) {
    //mov right check distance, mov left check distance, then go the the side where the obstacle is farther
    moveStop();
    delay(200);
    moveBackward();
    delay(500);
    turnRight();
    delay(400);
    moveStop();
    delay(500);
    int distRight = readDistance();
    turnLeft();
    delay(800);
    moveStop();
    delay(500);
    int distLeft = readDistance();
    turnRight();
    delay(400);
    if(distLeft < 20 && distRight < 20){
      moveStop();
      count++;
    }
    else if(distLeft <= distRight){
      turnRight();
      delay(400);
    }
    else{
      turnLeft();
      delay(400);
    }
    moveStop();
  } else if(distance >= 20) {
    moveForward();
    count = 0;
  }

}

int readDistance() {
  delay(50);
  int cm = sonar.ping_cm();
 
  return cm;
}

void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnLeft() {
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
}

void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
