#include <Servo.h>
#define FWD 0
#define BACK 1

Servo servo1;  // create servo object to control a servo
static const int servoPin = 4;
int pos = 45;    // variable to store the servo position

const int PWMRpin = 14;
const int DIRRpin = 32;

const int PWMLpin = 27;
const int DIRLpin = 33;

static const int PWMRchannel = 2;
static const int PWMLchannel = 3;

void setup() {
  Serial.begin(9600);
  
  // Initialise PWM for wheel motors
  ledcSetup(PWMRchannel,9600,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(PWMRpin,PWMRchannel); // pin, pwm channel
  ledcSetup(PWMLchannel,9600,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(PWMLpin,PWMRchannel); // pin, pwm channel

  pinMode(DIRRpin,OUTPUT); // set direction pin to output
  pinMode(DIRLpin,OUTPUT); // set direction pin to output

  ledcWrite(PWMRchannel,0); // pwm channel, speed 0-255
  digitalWrite(DIRRpin, LOW); // set direction to cw/ccw
  ledcWrite(PWMLchannel,0); // pwm channel, speed 0-255
  digitalWrite(DIRLpin, LOW); // set direction to cw/ccw

  // Initialise Servo motor for arm
  servo1.attach(
      servoPin, 
      Servo::CHANNEL_NOT_ATTACHED, 
      45,
      120
  );
}

void loop() {
  if (Serial.available()) {
  char Key = Serial.read();
  Serial.println(Key);
  //cases for the movement of the robot, will follow gaming direction (WASD)
  switch(Key) {
    case 'w': {// 'w': both wheels move forward, robot moves forward
      ledcWrite(PWMLchannel, 120);
      digitalWrite(DIRLpin, FWD);
      ledcWrite(PWMRchannel, 120);
      digitalWrite(DIRRpin, FWD);  
      break; 
    }
  case 's': {  
      ledcWrite(PWMLchannel, 120);
      digitalWrite(DIRLpin, BACK);
      ledcWrite(PWMRchannel, 120);
      digitalWrite(DIRRpin, BACK); 
      break;   
  }
  case 'a': { // 'a': left wheel moves backward, right wheel moves forward, robot rotates left
      ledcWrite(PWMLchannel, 120);
      digitalWrite(DIRLpin, BACK);
      ledcWrite(PWMRchannel, 120);
      digitalWrite(DIRRpin, FWD);
      break;    
  }
   case 'd': {// 'd': left wheel moves forward, right wheel moves forward, robot rotates right
      ledcWrite(PWMLchannel, 120);
      digitalWrite(DIRLpin, FWD);
      ledcWrite(PWMRchannel, 120);
      digitalWrite(DIRRpin, BACK);
      break;    
  }
  case 'f': {// set different speeds (0-100%)
    if (Serial.available()) {
      int PWM_freq = Serial.read();
      PWM_freq = PWM_freq * 255 / 100;
      ledcWrite(PWMLchannel, PWM_freq);
      ledcWrite(PWMRchannel, PWM_freq);
    }
    break; 
  }
  case 'p': {
      ledcWrite(PWMLchannel, 0);
      ledcWrite(PWMRchannel, 0); 
      break; 
  }
  
    //cases for the arm
  case 'k': {// 'k' lowers the arm into "attack" so it can grasp onto the obstacles
    for(int posDegrees = 0; posDegrees <= 150; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(5);
    }
    break; 
  }
  case 'i': {// 'i' raises the arm into retreat
    for(int posDegrees = 150; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(5);
    }
    break; 
  }
  }
}
}


//#include "BluetoothSerial.h"
//#include <stdio.h>
//#include <math.h>
//
//BluetoothSerial SerialBT;
//
//int count = 0;
//
//void setup() {
////  Serial.begin(115200);
////  SerialBT.begin("ESP32testJCAT"); //Bluetooth device name
////  //Serial.println("The device started, now you can pair it with bluetooth!");
////  pinMode(13,OUTPUT);
////  digitalWrite(13,LOW);
//  Serial.begin(115200);
//  SerialBT.begin("ESP32testJCA"); //Bluetooth device name
//  //Serial.println("The device started, now you can pair it with bluetooth!");
//  pinMode(13,OUTPUT);
//  pinMode(14,OUTPUT);
//  pinMode(15, INPUT);
//  digitalWrite(14,HIGH);
//  digitalWrite(13,LOW);
//  
//}
//
//void loop() {
//  char c = 0;
//  int an = 0;
//  int i;
//  
//  if (Serial.available()) {
//    SerialBT.write(Serial.read());
//  }
//  if (SerialBT.available()) {
//    //Serial.write(SerialBT.read());
//    c = SerialBT.read();
//    if(c == 'o'){
//      digitalWrite(13,HIGH);
//    }
//    else if (c == 'p'){
//      digitalWrite(13,LOW);
//    }
//    else if (c == 'a'){
//      an = analogRead(A2);
//      SerialBT.print("a ");
//      SerialBT.println(an);
//    }
//    else if (c == 'x'){
//      count = count + 1;
//      for (i=0; i<100; i++){
//        SerialBT.print("x ");
//        SerialBT.print(i);
//        SerialBT.print(" ");
//        SerialBT.println(int(50*sin(2*3.14/50*i+count)));
//      }
//    }
//    else if (c == 'c'){
//      SerialBT.println("c 1");
//    }
//  }
//  delay(20);
//}
