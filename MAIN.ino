#include <Servo.h>
#define FWD 0
#define BACK 1

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

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

}

void loop() {

  if (Serial.available()) {

  char Key = Serial.read();


  //cases for the movement of the robot, will follow gaming direction (WASD)

   // 'w': both wheels move forward, robot moves forward
  
  
  if (Key == 'w') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, FWD);

      analogWrite(right_wheel_PWM, 120);
      digitalWrite(right_wheel_Dir, FWD);   
  }

     // 's': both wheels move backward, robot moves backward


  if (Key == 's') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, BACK);

      analogWrite(right_wheel_PWM, 120);
      digitalWrite(right_wheel_Dir, BACK);   
  }

     // 'a': left wheel moves backward, right wheel moves forward, robot rotates left

  if (Key == 'a') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, FWD);

      analogWrite(right_wheel_PWM, 120);
      digitalWrite(right_wheel_Dir, BACK);   
  
  }

       // 'd': left wheel moves forward, right wheel moves forward, robot rotates right

   if (Key == 'd') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, BACK);

      analogWrite(right_wheel_PWM, 120);
      digitalWrite(right_wheel_Dir, FWD);   
  }

  if (Key == 'f') {                 // set different speeds (0-100%)
    if (Serial.available()) {
    int PWM_freq = Serial.read();
    PWM_freq = PWM_freq * 255 / 100;
    analogWrite(left_wheel_PWM, PWM_freq);
    analogWrite(right_wheel_PWM, PWM_freq);
    }
  }

  
  if (Key == 'h') {
    digitalWrite(left_wheel_PWM, 0);
    digitalWrite(right_wheel_PWM, 0);
  }
  
  //cases for the arm

  // 'k' lowers the arm into "attack" so it can grasp onto the obstacles
  if (Key == 'k') {
  //for (pos = 45; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(180);              // tell servo to go to position in variable 'pos'
  //  delay(15);                       // waits 15ms for the servo to reach the position
 // }
  }

  // 'i' raises the arm into retreat
  if (Key == 'i') {
  //for (pos = 180; pos >= 45; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(45);              // tell servo to go to position in variable 'pos'
   // delay(15);                       // waits 15ms for the servo to reach the position
 // }
}


  }

}
