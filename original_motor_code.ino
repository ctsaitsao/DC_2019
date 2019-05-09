const int PWM1pin = 27; //14
const int DIR1pin = 33; //32

const int PWM2pin = 14; //14
const int DIR2pin = 32; //32

const int PWM1channel = 0;
const int PWM2channel = 1;

void setup() {
  ledcSetup(PWM1channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(PWM1pin,PWM1channel); // pin, pwm channel
  ledcSetup(PWM2channel,5000,8); // pwm channel, frequency, resolution in bits
  ledcAttachPin(PWM2pin,PWM2channel); // pin, pwm channel

  pinMode(DIR1pin,OUTPUT); // set direction pin to output

  ledcWrite(PWM1channel,0); // pwm channel, speed 0-255
  digitalWrite(DIR1pin, LOW); // set direction to cw/ccw

  pinMode(DIR2pin,OUTPUT); // set direction pin to output

  ledcWrite(PWM2channel,0); // pwm channel, speed 0-255
  digitalWrite(DIR2pin, LOW); // set direction to cw/ccw
}

void loop() { 
  ledcWrite(PWM1channel,255); // full speec
  digitalWrite(DIR1pin, LOW); // cw/ccw
  ledcWrite(PWM2channel,255); // full speec
  digitalWrite(DIR2pin, LOW); // cw/ccw

  delay(3000);

  ledcWrite(PWM1channel,255); // full speed
  digitalWrite(DIR1pin, HIGH); // ccw/cw
  
  ledcWrite(PWM2channel,255); // full speed
  digitalWrite(DIR2pin, HIGH); // ccw/cw

  delay(3000);
}
