/******************************************************************************
BLACKPINKBOT.cpp
M. Alief Faisal Hakim @ TRKB UNAIR
12/26/23
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Digunakan sebagai library robot line follower + Lifter pada mata kuliah Eksperimen Robotika II serta Encoder Mobile Robot tahun 2023

Resources:
TB6612 SparkFun Library
AX12A Library
Keypad Library

Development environment specifics:
Developed on Arduino 2.2.1
******************************************************************************/

//  Sensor Array   Error Value
//  1 1 1 1 0           4
//  1 1 1 0 0           3
//  1 1 1 0 1           2
//  1 1 0 0 1           1
//  1 1 0 1 1           0
//  1 0 0 1 1          -1
//  1 0 1 1 1          -2
//  0 0 1 1 1          -3
//  0 1 1 1 1          -4
//
//  1 1 1 1 1           0 Robot found no line


#include "BLACKPINKBOT.h"
#include <Arduino.h>
#include <AX12A.h>

//Encoder

const int encoderPins[][2] = {{19, 5}, {18, 40}, {2, 38}, {3, 42}};
volatile long encoderCounts[4] = {0, 0, 0, 0};

//Lifter
#define DirectionPin (10u)
#define BaudRate (1000000ul)
#define ID (1u)

void servoAngkut(int dtime) {
  ax12a.moveSpeed(ID, 600, 400);
  delay(dtime);
}

void servoTaruh(int dtime) {
  ax12a.moveSpeed(ID, 200, 400);
  delay(dtime);
  motorDrivePID(0,0);
  delay(10);
}

void servoReset(int dtime){
  ax12a.moveSpeed(ID, 0, 400);
  delay(dtime);
}

// PID Control
const float KP = 10;
const float KI = 0;
const float KD = 4;

float error = 0, P = 0, I = 0, D = 0, PIDvalue = 0;
float previousError = 0;
int lastSpeedL, lastSpeedR;

int mode = 0;

// Line Sensor
const uint8_t sensorPins[5] = { 49, 47, 39, 43, 41 }; 
uint8_t sensorVal[5]  = { 0, 0, 0, 0, 0 };

// Define the keypad object
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[4] = {31, 21, 33, 35};
byte pin_column[4] = {17, 15, 16, 14};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, 4, 4);


# define speedRef 150
# define pwmAdjust 10

Motor frontLeftMotor = Motor(FRONT_LEFT_MOTOR_DIR_PIN1, FRONT_LEFT_MOTOR_DIR_PIN2, FRONT_LEFT_MOTOR_PWM_PIN, OFFSET_PIN, STBY_PIN1);
Motor frontRightMotor = Motor(FRONT_RIGHT_MOTOR_DIR_PIN1, FRONT_RIGHT_MOTOR_DIR_PIN2, FRONT_RIGHT_MOTOR_PWM_PIN, OFFSET_PIN, STBY_PIN1);
Motor rearLeftMotor = Motor(REAR_LEFT_MOTOR_DIR_PIN1, REAR_LEFT_MOTOR_DIR_PIN2, REAR_LEFT_MOTOR_PWM_PIN, OFFSET_PIN, STBY_PIN2);
Motor rearRightMotor = Motor(REAR_RIGHT_MOTOR_DIR_PIN1, REAR_RIGHT_MOTOR_DIR_PIN2, REAR_RIGHT_MOTOR_PWM_PIN, OFFSET_PIN, STBY_PIN2);

Motor::Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin)
{
  In1 = In1pin;
  In2 = In2pin;
  PWM = PWMpin;
  Standby = STBYpin;
  Offset = offset;
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(Standby, OUTPUT);
}

void Motor::drive(int speed)
{
  digitalWrite(Standby, HIGH);
  speed = speed * Offset;
  if (speed>=0) fwd(speed);
  else rev(-speed);
}
void Motor::drive(int speed, int duration)
{
  drive(speed);
  delay(duration);
}

void Motor::fwd(int speed)
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, LOW);
   analogWrite(PWM, speed);

}

void Motor::rev(int speed)
{
   digitalWrite(In1, LOW);
   digitalWrite(In2, HIGH);
   analogWrite(PWM, speed);
}

void Motor::brake()
{
   digitalWrite(In1, HIGH);
   digitalWrite(In2, HIGH);
   analogWrite(PWM,0);
}

void Motor::standby()
{
   digitalWrite(Standby, LOW);
}

void forward(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed)
{
	motor1.drive(speed);
	motor2.drive(speed);
  motor3.drive(speed);
  motor4.drive(speed);
}
void forward(Motor motor1, Motor motor2, Motor motor3, Motor motor4)
{
	motor1.drive(DEFAULTSPEED);
	motor2.drive(DEFAULTSPEED);
    motor3.drive(DEFAULTSPEED);
    motor4.drive(DEFAULTSPEED);
}

void back(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed)
{
	int temp = abs(speed);
	motor1.drive(-temp);
	motor2.drive(-temp);
    motor3.drive(-temp);
    motor4.drive(-temp);
}
void back(Motor motor1, Motor motor2, Motor motor3, Motor motor4)
{
	motor1.drive(-DEFAULTSPEED);
	motor2.drive(-DEFAULTSPEED);
    motor3.drive(-DEFAULTSPEED);
    motor4.drive(-DEFAULTSPEED);
}
void left(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed)
{
	int temp = abs(speed)/2;
	motor1.drive(-temp);motor2.drive(temp);
    motor3.drive(-temp);motor4.drive(temp);
}
void right(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed)
{
	int temp = abs(speed)/2;
    motor1.drive(temp);motor2.drive(-temp);
    motor3.drive(temp);motor4.drive(-temp);
}
void brake(Motor motor1, Motor motor2, Motor motor3, Motor motor4)
{
	motor1.brake();
	motor2.brake();
  motor3.brake();
  motor4.brake();
}


char flagdx= 0;

void dnext(){
    if(flagdx)motorDrivePID(0, 0);
    motorDrivePID(0,0);
    while (digitalRead(right_button)); buzzer(1, 80, 100);
    while (!digitalRead(right_button));
    delay(300);
}

void buzzer(int num, int ton, int toff)
{
    for (int i = 0; i < num ; i++)
    {
        digitalWrite(port_buzzer, HIGH);
        delay(ton);
        digitalWrite(port_buzzer, LOW);
        delay(toff);
    }
    
}

void eksbotInit(){
  // pinMode(redLED, OUTPUT);
  // pinMode(greenLED, OUTPUT);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 2; ++j) {
      pinMode(encoderPins[i][j], INPUT);
      // Choose either RISING or FALLING based on your encoder's specifications
      attachInterrupt(digitalPinToInterrupt(encoderPins[i][j]), handleEncoder, RISING);
    }
  }
  pinMode(blueLED, OUTPUT);
  pinMode(port_buzzer, OUTPUT);
  pinMode(sensorPins[0], INPUT);
  pinMode(sensorPins[1], INPUT);
  pinMode(sensorPins[2], INPUT);
  pinMode(sensorPins[3], INPUT);
  pinMode(sensorPins[4], INPUT);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(left_button, INPUT_PULLUP);
  ax12a.begin(BaudRate, DirectionPin, &Serial);
  ax12a.setEndless(ID, OFF);
  servoReset(2000);
  buzzer(3, 50, 50);
  dnext();
}

void motorDrivePID(int speedL, int speedR) {
  frontLeftMotor.drive(speedL); rearLeftMotor.drive(speedL);
  frontRightMotor.drive(speedR); rearRightMotor.drive(speedR);
}

void checkSensors() {
  sensorVal[0] = digitalRead(sensorPins[0]);
  sensorVal[1] = digitalRead(sensorPins[1]);
  sensorVal[2] = digitalRead(sensorPins[2]);
  sensorVal[3] = digitalRead(sensorPins[3]);
  sensorVal[4] = digitalRead(sensorPins[4]);
}

void readSensors() {
  sensorVal[0] = digitalRead(sensorPins[0]);
  sensorVal[1] = digitalRead(sensorPins[1]);
  sensorVal[2] = digitalRead(sensorPins[2]);
  sensorVal[3] = digitalRead(sensorPins[3]);
  sensorVal[4] = digitalRead(sensorPins[4]);
  
  if ((sensorVal[0] == 1) && (sensorVal[1] == 1) && (sensorVal[2] == 1) && (sensorVal[3] == 1) && (sensorVal[4] == 0)) {
    mode = FOLLOWING_LINE;
    error = 4;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 1) && (sensorVal[2] == 1) && (sensorVal[3] == 0) && (sensorVal[4] == 0)) {
    mode = FOLLOWING_LINE;
    error = 3;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 1) && (sensorVal[2] == 1) && (sensorVal[3] == 0) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = 2;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 1) && (sensorVal[2] == 0) && (sensorVal[3] == 0) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = 1;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 1) && (sensorVal[2] == 0) && (sensorVal[3] == 1) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = 0;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 0) && (sensorVal[2] == 0) && (sensorVal[3] == 1) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = -1;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 0) && (sensorVal[2] == 1) && (sensorVal[3] == 1) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = -2;
  }
  else if ((sensorVal[0] == 0) && (sensorVal[1] == 0) && (sensorVal[2] == 1) && (sensorVal[3] == 1) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = -3;
  }
  else if ((sensorVal[0] == 0) && (sensorVal[1] == 1) && (sensorVal[2] == 1) && (sensorVal[3] == 1) && (sensorVal[4] == 1)) {
    mode = FOLLOWING_LINE;
    error = -4;
  }
  else if ((sensorVal[0] == 1) && (sensorVal[1] == 1) && (sensorVal[2] == 1) && (sensorVal[3] == 1) && (sensorVal[4] == 1)) {
    mode = NO_LINE;
    error = 0;
  }
}

void calculatePID() {
  P = error;
  I += error;
  D = error - previousError;
  PIDvalue = (KP * P) + (KI * I) + (KD * D);
  previousError = error;
}

void motorPIDcontrol(int refSpeed=speedRef) {
  calculatePID();
  int speedL = refSpeed + (PIDvalue * pwmAdjust);
  int speedR = refSpeed - (PIDvalue * pwmAdjust);

  speedL = constrain(speedL, -refSpeed, refSpeed);
  speedR = constrain(speedR, -refSpeed, refSpeed);

  motorDrivePID(speedL, speedR);

  lastSpeedL = speedL;
  lastSpeedR = speedR;
  
  // Serial.print (PIDvalue);
  // Serial.print (" ==> Left, Right:  ");
  // Serial.print (speedL);
  // Serial.print ("   ");
  // Serial.println (speedR);
}

void line(int desiredMode, int desiredSpeed, int dbreaktime) {
  while (mode != desiredMode) {
    readSensors();
    switch (mode)
    {
      case NO_LINE:
        motorDrivePID(lastSpeedL, lastSpeedR);
        break;

      case FOLLOWING_LINE:
        motorPIDcontrol(desiredSpeed);
        break;
    }

    if (sensorVal[0] == 0 && sensorVal[4] == 0) {
      mode = FF;
    } else if (sensorVal[0] == 0 && sensorVal[1] == 0) {
      mode = FL;
    } else if (sensorVal[3] == 0 && sensorVal[4] == 0) {
      mode = FR;
    }

    if (mode == desiredMode) {
      motorDrivePID(150, 150);
      delay(200);

    if (dbreaktime < 0)       {motorDrivePID(150, 150);     delay(-15*dbreaktime);motorDrivePID(0, 0);   }
        else if(dbreaktime > 0)   {motorDrivePID(-150, -150);   delay(15*dbreaktime);motorDrivePID(0, 0);    }
    }
  }
  //buzzer(1, 25, 0);
}

void linefoll() {
  // Assuming readSensors, motorDrivePID, and motorPIDcontrol are defined somewhere
  readSensors();
  switch (mode) {
    case NO_LINE:
      motorDrivePID(lastSpeedL, lastSpeedR);
      break;

    case FOLLOWING_LINE:
      motorPIDcontrol();
      break;
  }

}

void autolinefollow(int duration, int dbreaktime) {
  unsigned long startTime = millis();
  
  // Assuming readSensors, motorDrivePID, and motorPIDcontrol are defined somewhere
  while (millis() - startTime < duration) {
    readSensors();
    
    switch (mode) {
      case NO_LINE:
        motorDrivePID(lastSpeedL, lastSpeedR);
        break;

      case FOLLOWING_LINE:
        motorPIDcontrol();
        break;
    }
      if (dbreaktime < 0) {
    motorDrivePID(150, 150);
    delay(-15 * dbreaktime);
    motorDrivePID(0, 0);
  } else if (dbreaktime > 0) {
    motorDrivePID(-150, -150);
    delay(15 * dbreaktime);
    motorDrivePID(0, 0);
  }
  }
  buzzer(1,40,0);
}

void turn(int action) {
  switch (action) {
    case TURN_LEFT:
      // motorDrivePID(150, 150);
      // delay(200);
      motorDrivePID(-150, 150);
      delay(700);
      // motorDrivePID(0, 0);
      // delay(1000);
      checkSensors();
      while(sensorVal[2] != 0) {
        motorDrivePID(-150, 150);
        checkSensors();
      }
      mode = FOLLOWING_LINE;
      break;
    case TURN_RIGHT:
      motorDrivePID(150, -150);
      delay(700);
      checkSensors();
      while(sensorVal[2] != 0) {
        motorDrivePID(150, -150);
        checkSensors();
      }
      mode = FOLLOWING_LINE;
      break;
    case GO_STRAIGHT:
      motorDrivePID(150, 150);
      delay(200);
      mode = FOLLOWING_LINE;
      break;
  }
}

void StopMotors()
{
  frontLeftMotor.drive(0); frontRightMotor.drive(0);
  rearLeftMotor.drive(0);  rearRightMotor.drive(0);
}

void findline(int speedL, int speedR, int dbreaktime) {
  int timeout = 0;
  while (timeout < 5000) {  // Timeout to prevent infinite loop
    readSensors();
    if (mode == FOLLOWING_LINE) {
      break;  // Exit the loop if the line is detected again
    }

    motorDrivePID(speedL, speedR);  // Move forward with the specified speeds
    timeout += 10;
    delay(10);
  }
    if (dbreaktime < 0)       {motorDrivePID(speedL, speedR);     delay(-15*dbreaktime);motorDrivePID(0, 0);   }
    else if(dbreaktime > 0)   {motorDrivePID(-speedL, -speedR);   delay(15*dbreaktime);motorDrivePID(0, 0);    }
  buzzer(1,30,0); // Stop the robot
}

void spinheading(int sudut){
  if(sudut > 0){
    motorDrivePID(150, -150);
    delay(14*sudut);
  }
  else if(sudut < 0){
    motorDrivePID(-150, 150);
    delay(abs(14*sudut));
  }
}

void linedelay(int speed, int dtime, int dbreaktime) {
  readSensors();
  if (mode != FOLLOWING_LINE) {
    motorDrivePID(speed, speed);  // Line following
    delay(dtime);
  }

  // Berhenti selama dbreaktime setelah line following
  if (dbreaktime < 0) {
    motorDrivePID(150, 150);
    delay(-15 * dbreaktime);
    motorDrivePID(0, 0);
  } else if (dbreaktime > 0) {
    motorDrivePID(-150, -150);
    delay(15 * dbreaktime);
    motorDrivePID(0, 0);
  }

  buzzer(1, 40, 0);  // Stop the robot
}

void move(int mspeed_FL, int mspeed_FR, int mspeed_RL, int mspeed_RR) {
  frontLeftMotor.drive(mspeed_FL); frontRightMotor.drive(mspeed_FR);
  rearLeftMotor.drive(mspeed_RL); rearRightMotor.drive(mspeed_RR);
}

void handleEncoder() {
  for (int i = 0; i < 4; ++i) {
    int pinAValue = digitalRead(encoderPins[i][0]);
    int pinBValue = digitalRead(encoderPins[i][1]);

    if (pinAValue == HIGH && pinBValue == LOW) {
      encoderCounts[i]++;
    } else if (pinAValue == LOW && pinBValue == HIGH) {
      encoderCounts[i]--;
    }
  }
}

bool allWheelsReachedTarget(float target) {
  long totalEncoderCount = 0;

  for (int i = 0; i < 4; ++i) {
    totalEncoderCount += encoderCounts[i];
  }

  return totalEncoderCount >= target;
}

// Encoder

#define PI 3.14159
const float wheelDiameter = 63.0; //in mm
const float wheelCircumference = (wheelDiameter * PI) / 10; //in cm

int CMtoSteps(float distance_CM, float encoderTicksPerRevolution) {
  float revolutions = distance_CM / wheelCircumference;
  float f_ticks = revolutions * encoderTicksPerRevolution;
  return static_cast<int>(f_ticks);
}

void EncoderConfig(int mode, int distanceCM, int mspeed, int encoderTicksPerRevolution) {
  int targetSteps = CMtoSteps(distanceCM, encoderTicksPerRevolution);

  while (!allWheelsReachedTarget(targetSteps)) {
    switch(mode) {
      case fwrd:
        move(mspeed, mspeed + 10, mspeed, mspeed + 10);
        break;
      case bwd:
        move(-mspeed, -(mspeed + 10), -mspeed, -(mspeed + 10));
        break;
      case r:
        move(mspeed, -(mspeed + 7), -mspeed, mspeed + 7);
        break;
      case l:
        move(-(mspeed), mspeed + 20, mspeed - 10, -(mspeed));
        break;
      case fwd_xr:
        move(mspeed, 0, 0, mspeed + 10);
        break;
      case fwd_xl:
        move(0, mspeed + 10, mspeed, 0);
        break;
      case bwd_xr:
        move(-mspeed, 0, 0, -(mspeed + 10));
        break;
      case bwd_xl:
        move(0, -(mspeed + 10), -mspeed, 0);
        break;
      case tr:
        move(mspeed, -mspeed, mspeed, -mspeed);
        break;
      case tl:
        move(-mspeed, mspeed, -mspeed, mspeed);
        break;
    }
    delay(10);
  }

  StopMotors();
  // Reset encoder counts
  for (int i = 0; i < 4; ++i) {
    encoderCounts[i] = 0;
  }
  delay(500);
}

void FWD(int distanceCM, int speed) {
  EncoderConfig(fwrd, distanceCM, speed, 825);
}

void BWD(int distanceCM, int speed) {
  EncoderConfig(bwd, distanceCM, speed, 825);
}

void R(int distanceCM, int speed) {
  EncoderConfig(r, distanceCM, speed, 920);
}

void L(int distanceCM, int speed) {
  EncoderConfig(l, distanceCM, speed, 920);
}

void FWD_XR(int distanceCM, int speed) {
  EncoderConfig(fwd_xr, distanceCM, speed, 1150);
}

void FWD_XL(int distanceCM, int speed) {
  EncoderConfig(fwd_xl, distanceCM, speed, 1150);
}

void BWD_XR(int distanceCM, int speed) {
  EncoderConfig(bwd_xr, distanceCM, speed, 1150);
}

void BWD_XL(int distanceCM, int speed) {
  EncoderConfig(bwd_xl, distanceCM, speed, 1150);
}

void TR(int distanceCM=25, int speed=200) {
  EncoderConfig(tr, distanceCM, speed, 825);
}

void TL(int distanceCM=25, int speed=200) {
  EncoderConfig(tl, distanceCM, speed, 825);
}

void lineIntersect(int n) {
  for (int i = 0; i < n; i++) {
    linedelay(150, 30, -5);
    line(FF, 150, -10);
  }
}