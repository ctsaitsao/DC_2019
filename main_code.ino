#include "BluetoothSerial.h"
//#include <Servo.h>
#include <stdio.h>
#include <math.h>

BluetoothSerial SerialBT;

#define FWD 0
#define BACK 1

int count = 0;

//INITIALIZE WHEEL CHANNELS

const int PWMRpin = 14;
const int DIRRpin = 32;

const int PWMLpin = 27;
const int DIRLpin = 33;


static const int PWMRchannel = 2;
static const int PWMLchannel = 3;

// INITIALIZE SERVO

//Servo servo1;  // create servo object to control a servo
//static const int servoPin = 4;
//int pos = 45;    // variable to store the servo position

void setup() {
  Serial.begin(9600); //9600 before
  
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

  // BLUETOOTH:
  Serial.begin(115200);
  SerialBT.begin("ESP32testJCAT"); //Bluetooth device name

  //SERVO: 
//  servo1.attach(
//      servoPin, 
//      Servo::CHANNEL_NOT_ATTACHED, 
//     45,
//      120
//  );

}

void loop() {
  int i;
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char Key = SerialBT.read();
    SerialBT.println(Key);

    
    //cases for the movement of the robot, will follow gaming direction (WASD)
    if (Key == 'x'){
      count = count + 1;
      for (i=0; i<100; i++){
        SerialBT.print("x ");
        SerialBT.print(i);
        SerialBT.print(" ");
        SerialBT.println(int(50*sin(2*3.14/50*i+count)));
      }
    }
    else if (Key == 'w') {
      Serial.println("W entered");
      ledcWrite(PWMLchannel, 250);
      digitalWrite(DIRLpin, FWD);
      ledcWrite(PWMRchannel, 250);
      digitalWrite(DIRRpin, FWD);  
    }
    else if (Key == 's'){
      ledcWrite(PWMLchannel, 250);
      digitalWrite(DIRLpin, BACK);
      ledcWrite(PWMRchannel, 250);
      digitalWrite(DIRRpin, BACK); 
    }
    else if (Key == 'a'){
      ledcWrite(PWMLchannel, 250);
      digitalWrite(DIRLpin, BACK);
      ledcWrite(PWMRchannel, 250);
      digitalWrite(DIRRpin, FWD);
    }
    else if (Key == 'd'){
      ledcWrite(PWMLchannel, 250);
      digitalWrite(DIRLpin, FWD);
      ledcWrite(PWMRchannel, 250);
      digitalWrite(DIRRpin, BACK);
    }

    else if (Key = 'p') {
      ledcWrite(PWMLchannel, 0);
      ledcWrite(PWMRchannel, 0); 
    }

  //  else if (Key = 'k') {
  //    for(int posDegrees = 0; posDegrees <= 150; posDegrees++) 
  //    {
  //      servo1.write(posDegrees);
  //      Serial.println(posDegrees);
  //      delay(5);
  //     }
  //  }
//
//    else if (Key = 'i') {
//      for(int posDegrees = 150; posDegrees >= 0; posDegrees--) 
//      {
//        servo1.write(posDegrees);
//        Serial.println(posDegrees);
//        delay(5);
//       }
//    
//    }
  }
  delay(20);
}
