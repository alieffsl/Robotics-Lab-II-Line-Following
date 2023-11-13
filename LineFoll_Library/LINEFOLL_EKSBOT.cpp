//*************************************************************************************
// Eksbot II 2023
// ----------------------------- 
//
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
//
//  line :
//     FRONT   --> stop when sensors 1 and 5 pass the line after sensors 1 and 5 detect the line in the crosstime
//     LEFT    --> stop when sensors 1 and 2 pass the line after sensors 1 and 2 detect the line in the crosstime
//     RIGHT   --> stop when sensors 4 and 5 pass the line after sensors 4 and 5 detect the line in the crosstime
//
//  turn :
//     FORWARD  --> Continue moving straight after meeting the specified mode condition.
//     LEFT     --> Turn the robot left after meeting the specified mode condition.
//     RIGHT    --> Turn the robot right after meeting the specified mode condition.
//
// Usage:
//   line(desiredMode);
//   turn(action);
//   Ex:
//     line(FRONT);
//     turn(LEFT);
//
//*************************************************************************************

#include "LINEFOLL_EKSBOT.h"
#include <Arduino.h>


// PID Control
const float KP = 6;
const float KI = 0;
const float KD = 0;

float error = 0, P = 0, I = 0, D = 0, PIDvalue = 0;
float previousError = 0;
int lastSpeedL, lastSpeedR;

int mode = 0;

// Line Sensor
const uint8_t sensorPins[5] = { 41, 43, 39, 47, 49 };
uint8_t sensorVal[5]  = { 0, 0, 0, 0, 0 };
const int startButtonPin = 25;

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


void eksbotInit(){
  pinMode(startButtonPin, INPUT_PULLUP);
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void toggleRobot(bool state) {
  if (digitalRead(startButtonPin) == LOW) {
    state = !state;
    delay(100);
    while (digitalRead(startButtonPin) == LOW) {}
  }
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

void motorPIDcontrol() {
  calculatePID();
  int speedL = speedRef + (PIDvalue * pwmAdjust);
  int speedR = speedRef - (PIDvalue * pwmAdjust);

  speedL = constrain(speedL, -speedRef, speedRef);
  speedR = constrain(speedR, -speedRef, speedRef);

  motorDrivePID(speedL, speedR);

  lastSpeedL = speedL;
  lastSpeedR = speedR;
  
  // Serial.print (PIDvalue);
  // Serial.print (" ==> Left, Right:  ");
  // Serial.print (speedL);
  // Serial.print ("   ");
  // Serial.println (speedR);
}

void line(int desiredMode) {
  while (mode != desiredMode) {
    readSensors();
    switch (mode)
    {
      case NO_LINE:
        motorDrivePID(lastSpeedL, lastSpeedR);
        break;

      case FOLLOWING_LINE:
        motorPIDcontrol();
        break;
    }

    if (sensorVal[0] == 0 && sensorVal[4] == 0) {
      mode = FRONT;
    } else if (sensorVal[0] == 0 && sensorVal[1] == 0) {
      mode = LEFT;
    } else if (sensorVal[3] == 0 && sensorVal[4] == 0) {
      mode = RIGHT;
    }

    if (mode == desiredMode) {
      motorDrivePID(0, 0);
      delay(100);
      return;
      break;
    }
  }
}

void autolinefollow() {
  readSensors();
  switch (mode)
  {
    case NO_LINE:
      motorDrivePID(lastSpeedL, lastSpeedR);
      break;

    case FOLLOWING_LINE:
      motorPIDcontrol();
      break;
  }
}

void turn(int action) {
  switch (action) {
    case LEFT:
      checkSensors();
      motorDrivePID(150, 150);
      delay(400);
      motorDrivePID(-150, 150);
      delay(400);
      while(sensorVal[2] != 0) {
        motorDrivePID(-150, 150);
        checkSensors();
      }
      mode = FOLLOWING_LINE;
      break;
    case RIGHT:
      checkSensors();
      motorDrivePID(150, 150);
      delay(400);
      motorDrivePID(150, -150);
      delay(400);
      while(sensorVal[2] != 0) {
        motorDrivePID(150, -150);
        checkSensors();
      }
      mode = FOLLOWING_LINE;
      break;
    case FORWARD:
      motorDrivePID(150, 150);
      delay(400);
      mode = FOLLOWING_LINE;
      break;
  }
}

void turnLeft(int speed, int dtime)
{
  int temp = abs(speed);
  frontLeftMotor.drive(-temp); frontRightMotor.drive(temp);
  rearLeftMotor.drive(-temp);  rearRightMotor.drive(temp);
  delay(dtime);
}

void turnRight(int speed, int dtime)
{
  int temp = abs(speed);
  frontLeftMotor.drive(temp); frontRightMotor.drive(-temp);
  rearLeftMotor.drive(temp);  rearRightMotor.drive(-temp);
  delay(dtime);
}

void stopRobot(int dtime)
{
  frontLeftMotor.brake(); frontRightMotor.brake();
  rearLeftMotor.brake();  rearRightMotor.brake();
  delay(dtime);
}

void goForward(int speed, int dtime)
{
  int temp = abs(speed);
  frontLeftMotor.drive(temp); frontRightMotor.drive(temp);
  rearLeftMotor.drive(temp);  rearRightMotor.drive(temp);
  delay(dtime);
}

void goBackward(int speed, int dtime)
{
  int temp = abs(speed);
  frontLeftMotor.drive(-temp); frontRightMotor.drive(-temp);
  rearLeftMotor.drive(-temp);  rearRightMotor.drive(-temp);
  delay(dtime);
}

void stop_end(bool state){
    motorDrivePID(0,0);
    state = !state;
    while(1);
}

