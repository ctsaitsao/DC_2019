#include "BluetoothSerial.h"
#include <Servo.h>
#include <stdio.h>
#include <math.h>
#include <Wire.h>
#include <VL53L1X.h>

BluetoothSerial SerialBT;

#define FWD 1
#define BACK 0

int count = 0;

//INITIALIZE DRIVE VARIABLES:

const int PWMRpin = 14;
const int DIRRpin = 32;

int isitmoving = 0;

const int PWMLpin = 27;
const int DIRLpin = 33;

const int right_read = 12;
const int left_read = 4;

static const int PWMRchannel = 2;
static const int PWMLchannel = 3;

int const pressed_pin = 26;

// INITIALIZE DIST SENSOR:

VL53L1X sensor;

// INITIALIZE SERVO:

Servo servo1;  // create servo object to control a servo
static const int servoPin = 15;
int pos = 45;    // variable to store the servo position

// INITIALIZE VIVE:

char message1[50];
int m1 = 0;
float xpos1 = 0, ypos1 = 0, xpos2 = 0, ypos2 = 0;

// INITIALIZE LIGHT SENSOR: 

const int light_output_pin = 13;
const int light_input_pin = 34;  // analog pin A2


void setup() {
  Serial.begin(115200); //9600 before, WORKED WITH 115200. Refers to serial communication thru USB when MCU is being programmed
  
  // Initialise PWM for wheel motors
  ledcSetup(PWMRchannel,9600,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(PWMRpin,PWMRchannel); // pin, pwm channel
  ledcSetup(PWMLchannel,9600,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(PWMLpin,PWMRchannel); // pin, pwm channel

  pinMode(DIRRpin,OUTPUT); // set direction pin to output
  pinMode(DIRLpin,OUTPUT); // set direction pin to output

   pinMode(right_read,INPUT); // set direction pin to input
   pinMode(left_read,INPUT); // set direction pin to input
   pinMode(pressed_pin,OUTPUT); // set pin to input, which will tell us whether the button has been pressed or not

  ledcWrite(PWMRchannel,0); // pwm channel, speed 0-255
  digitalWrite(DIRRpin, LOW); // set direction to cw/ccw
  ledcWrite(PWMLchannel,0); // pwm channel, speed 0-255
  digitalWrite(DIRLpin, LOW); // set direction to cw/ccw

  // BLUETOOTH:
  SerialBT.begin("ESP32test_main_code"); //Bluetooth device name

  // SERVO: 
  servo1.attach(
      servoPin, 
      Servo::CHANNEL_NOT_ATTACHED, 
      45,
      120
  );

  // DIST SENSOR:
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  sensor.setTimeout(1000);
  if (!sensor.init())   // if no sensor
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);

  // VIVE:
  Serial2.begin(9600,SERIAL_8N1, 16, 17); // for teensy. Tx1 = pin 17, Rx1 = pin 16

  // LIGHT SENSOR:
  pinMode(light_output_pin,OUTPUT);
  digitalWrite(light_output_pin,HIGH);
  pinMode(light_input_pin, INPUT); 
}


void loop() {
  int i;
  
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    int Key = SerialBT.read();   // IMPORTANT DO NOT DELETE
    Serial.println(Key);
    Key = char(Key);   // IMPORTANT DO NOT DELETE
    SerialBT.println(Key);

    
    //cases for the movement of the robot, will follow gaming direction (WASD)
    switch (Key) {
      case 'x': { // sine wave plotter for debugging
      count = count + 1;
      for (i=0; i<100; i++){
        SerialBT.print("x ");
        SerialBT.print(i);
        SerialBT.print(" ");
        SerialBT.println(int(50*sin(2*3.14/50*i+count)));
      }
      break;
      }
      
      case 'w': {
        if (isitmoving== 1 && digitalRead(right_read) == FWD && digitalRead(left_read) == FWD) {;}
        else {
          isitmoving = 1;
          digitalWrite(DIRLpin, FWD);
          digitalWrite(DIRRpin, FWD);  
          int dutycycle=30;
          for (dutycycle=30; dutycycle<250; dutycycle+=10) {
            ledcWrite(PWMLchannel, dutycycle);
            ledcWrite(PWMRchannel, dutycycle);
            delay(50);
          }
        }
        break;
      }
      case 's': {
        isitmoving = 1;
        ledcWrite(PWMLchannel, 140);
        digitalWrite(DIRLpin, BACK);
        ledcWrite(PWMRchannel, 140);
        digitalWrite(DIRRpin, BACK); 
        break;
      }
      case 'a': {
        isitmoving = 1;
        ledcWrite(PWMLchannel, 170);
        digitalWrite(DIRLpin, BACK);
        ledcWrite(PWMRchannel, 170);
        digitalWrite(DIRRpin, FWD);
        break;
      }
      case 'd': {
        isitmoving = 1;
        ledcWrite(PWMLchannel, 170);
        digitalWrite(DIRLpin, FWD);
        ledcWrite(PWMRchannel, 170);
        digitalWrite(DIRRpin, BACK);
        break;
      }
      case 't': {
        for(int posDegrees = 120; posDegrees >= 100; posDegrees--) 
        {
          servo1.write(posDegrees);
          delay(5);
        }
        break;
      }
      case 'g': {
        for(int posDegrees = 100; posDegrees <= 120; posDegrees++) 
        {
          servo1.write(posDegrees);
          delay(5);
        }
        break;
      }
      case 'p': {// for STOP
        ledcWrite(PWMLchannel, 0);
        ledcWrite(PWMRchannel, 0); 
        isitmoving = 0;
        break;
      }

      case 'z': {
          isitmoving = 1;
          digitalWrite(DIRLpin, FWD);
          digitalWrite(DIRRpin, FWD);  
          int dutycycle=0;
          for (dutycycle=0; dutycycle<130; dutycycle+=5) {
            ledcWrite(PWMLchannel, dutycycle);
            ledcWrite(PWMRchannel, dutycycle);
            delay(20);
          }
          isitmoving = 0;
        break;
      }

      
      case 'n': // for mouse, original no-increment forward code
        ledcWrite(PWMLchannel, 250);
        digitalWrite(DIRLpin, FWD);
        ledcWrite(PWMRchannel, 250);
        digitalWrite(DIRRpin, FWD); 
        isitmoving = 1;
    }
  }

  // DIST SENSOR:
  int distance = sensor.read();
  SerialBT.print("a ");
  SerialBT.println(distance);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  // VIVE:
  checkVive();
//  Serial.println(xpos1);
//  Serial.println(" ");
//  Serial.println(ypos1);
  SerialBT.print("c ");
  SerialBT.println((xpos1+xpos2)/2);
  SerialBT.print("d ");
  SerialBT.println((ypos1+ypos2)/2);


  // pressed pin: 
  int pressed = digitalRead(pressed_pin);
//  Serial.println(pressed);
   SerialBT.print("e ");
   SerialBT.println(pressed);

  // LIGHT SENSOR:
  int light = analogRead(light_input_pin)-1000;
  SerialBT.print("b ");
  SerialBT.println(light);
  
  delay(20);
}

void checkVive(){
  char type = ' ';
  float val1 = 0, val2 = 0;
  
  while(Serial2.available()){
    message1[m1] = Serial2.read();
    if (message1[m1] == '\n'){
      sscanf(message1,"%c %f %f", &type, &val1, &val2);
      if (type == 'a'){
        xpos1 = val1;
        ypos1 = val2;
      }
      else if (type == 'b'){
        xpos2 = val1;
        ypos2 = val2;
      }
      m1 = 0;
      int iii;
      for(iii=0;iii<50;iii++){
        message1[iii] = 0;
      }
    }
    else {
      m1++;
    }
  }
}
