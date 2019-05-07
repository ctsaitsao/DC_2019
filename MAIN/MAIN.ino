#include <Servo.h>
#include "BluetoothSerial.h"
#include <stdio.h>
#include <math.h>

#define FWD 0
#define BACK 1

BluetoothSerial SerialBT;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int count = 0;
int pos = 45;    // variable to store the servo position
const int left_wheel_PWM = 3;   
const int left_wheel_Dir = 10;
const int right_wheel_PWM = 11;
const int right_wheel_Dir = 12;

void setup() {
  myservo.attach(13);  // attaches the servo on pin 13 to the servo object
  myservo.write(0);
  pinMode(left_wheel_PWM, OUTPUT);
  pinMode(right_wheel_PWM, OUTPUT);
  analogWrite(left_wheel_PWM, 0);
  digitalWrite(left_wheel_Dir, FWD);
  analogWrite(right_wheel_PWM, 0);
  digitalWrite(right_wheel_Dir, FWD); 
  
  //Bluetooth setup 
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  //Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  char c = 0;
  int an = 0;
  int i;
  
  if (SerialBT.available()) {
    //Serial.write(SerialBT.read());
    c = SerialBT.read();
    if(c == 'o'){
      digitalWrite(13,HIGH);
    }
    else if (c == 'p'){
      digitalWrite(13,LOW);
    }
    else if (c == 'a'){
      an = analogRead(A2);
      SerialBT.print("a ");
      SerialBT.println(an);
    }
    else if (c == 'x'){
      count = count + 1;
      for (i=0; i<100; i++){
        SerialBT.print("x ");
        SerialBT.print(i);
        SerialBT.print(" ");
        SerialBT.println(int(50*sin(2*3.14/50*i+count)));
      }
    }
    else if (c == 'c'){
      SerialBT.println("c 1");
    }
  }
  
  if (Serial.available()) {
    char Key = Serial.read();
    //cases for the movement of the robot, will follow gaming direction (WASD)
  
    switch (Key) {
      case 'w':
      {// 'w': both wheels move forward, robot moves forward
        analogWrite(left_wheel_PWM, 120);
        digitalWrite(left_wheel_Dir, FWD);
        analogWrite(right_wheel_PWM, 120);
        digitalWrite(right_wheel_Dir, FWD);   
      }
      case 's':
      {// 's': both wheels move backward, robot moves backward
        analogWrite(left_wheel_PWM, 120);
        digitalWrite(left_wheel_Dir, BACK);
        analogWrite(right_wheel_PWM, 120);
        digitalWrite(right_wheel_Dir, BACK);   
      }
      case 'a':
      {// 'a': left wheel moves backward, right wheel moves forward, robot rotates left
        analogWrite(left_wheel_PWM, 120);
        digitalWrite(left_wheel_Dir, FWD);
        analogWrite(right_wheel_PWM, 120);
        digitalWrite(right_wheel_Dir, BACK);   
      }    
      case 'd':
      { // 'd': left wheel moves forward, right wheel moves forward, robot rotates right
        analogWrite(left_wheel_PWM, 120);
        digitalWrite(left_wheel_Dir, BACK);
        analogWrite(right_wheel_PWM, 120);
        digitalWrite(right_wheel_Dir, FWD);   
      }
      case 'f':
      { // set different speeds (0-100%)
        if (Serial.available()) {
          int PWM_freq = Serial.read();
          PWM_freq = PWM_freq * 255 / 100;
          analogWrite(left_wheel_PWM, PWM_freq);
          analogWrite(right_wheel_PWM, PWM_freq);
          }
       }
      case 'h':
      {
        digitalWrite(left_wheel_PWM, 0);
        digitalWrite(right_wheel_PWM, 0);
       }
      //cases for the arm
      case 'k':
      { // 'k' lowers the arm into "attack" so it can grasp onto the obstacles
        //for (pos = 45; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(180);              // tell servo to go to position in variable 'pos'
        //  delay(15);                       // waits 15ms for the servo to reach the position
        // }
      }
      case 'i':
      {// 'i' raises the arm into retreat
        //for (pos = 180; pos >= 45; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(45);              // tell servo to go to position in variable 'pos'
        // delay(15);                       // waits 15ms for the servo to reach the position
        // }
      }
    }
  }
  delay(20);
}
