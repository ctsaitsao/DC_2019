#include <Servo.h>
#define FWD 1
#define BACK 0

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int left_wheel_PWM = 9;    // LED connected to digital pin 9
int left_wheel_Dir = 10;
int right_wheel_PWM = 11;
int right_wheel_Dir = 12;


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);

}

void loop() {

  if (Serial.available()) {

  char Key = Serial.read();


  //cases for the movement of the robot, will follow gaming direction (WASD)

   // 'w': both wheels move forward, robot moves forward
  
  
  if (Key == 'w') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, FWD);

      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, FWD);   
  }

     // 's': both wheels move backward, robot moves backward


  if (Key == 's') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, BACK);

      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, BACK);   
  }

     // 'a': left wheel moves backward, right wheel moves forward, robot rotates left

  if (Key == 'a') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, FWD);

      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, BACK);   
  
  }

       // 'd': left wheel moves forward, right wheel moves forward, robot rotates right

   if (Key == 'd') {
    
      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, BACK);

      analogWrite(left_wheel_PWM, 120);
      digitalWrite(left_wheel_Dir, FWD);   
  }

  if (Key == 'f') {
    int PWM_freq = Serial.read();
    PWM_freq = PWM_freq * 255 / 100;
    analogWrite(left_wheel_PWM, PWM_freq);
    analogWrite(right_wheel_PWM, PWM_freq);
  }

  
  //cases for the arm

  // 'k' lowers the arm into "attack" so it can grasp onto the obstacles
  if (Key == 'k') {
  for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }

  // 'i' raises the arm into retreat
  if (Key == 'i') {
  for (pos = 120; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


  }

}
