//*************************************************************************************
// Eksbot II 2023
// M.Alief Faisal Hakim (162112233026)
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
//  1 1 1 1 1        0 Robot found no line: turn 180o 
//  0 0 0 0 0        0 Robot found continuous line : STOPPED
//
//  mode :
//     MODE_FF   --> stop when sensors 1 and 5 pass the line after sensors 1 and 5 detect the line in the crosstime
//     MODE_FL   --> stop when sensors 1 and 2 pass the line after sensors 1 and 2 detect the line in the crosstime
//     MODE_FR   --> stop when sensors 4 and 5 pass the line after sensors 4 and 5 detect the line in the crosstime
//
//  action :
//     TURN_LEFT    --> Turn the robot left after meeting the specified mode condition.
//     TURN_RIGHT   --> Turn the robot right after meeting the specified mode condition.
//     GO_STRAIGHT  --> Continue moving straight after meeting the specified mode condition.
//
// Usage:
//   line(mode, action);
//   Ex:
//     line(MODE_FF, TURN_LEFT);
//
//*************************************************************************************

#include <util/atomic.h>
#include <SparkFun_TB6612.h>
#include <AX12A.h>

// Line Sensor
uint8_t sensorPins[5] = { 41, 43, 39, 47, 49 };
uint8_t sensorVal[5]  = { 0, 0, 0, 0, 0 };
const int startButtonPin = 25;
bool isRobotStarted = false;

//Motor
Motor fl = Motor(4, 36, 8, 1, 9);
Motor fr = Motor(32, 30, 10, 1, 9);
Motor rl = Motor(26, 28, 11, 1, 12);
Motor rr = Motor(22, 24, 13, 1, 12);

int motorDrivePID(int speedL, int speedR) {
  fl.drive(speedL);fr.drive(speedR);
  rl.drive(speedL);rr.drive(speedR);
}

int mode = 0;

# define STOPPED 0
# define FOLLOWING_LINE 1
# define NO_LINE 2
# define MODE_FF 3
# define MODE_FL 4
# define MODE_FR 5

// Actions
# define TURN_LEFT 1
# define TURN_RIGHT 2
# define GO_STRAIGHT 3

float Kp = 1;
float Ki = 0;
float Kd = 0;

float error = 0, P = 0, I = 0, D = 0, PIDvalue = 0;
float previousError = 0;

const int speedRef = 150;
const int adj = 10;
signed char intersection;


void setup()
{
  pinMode(startButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}


void loop()
{ 
  if (!isRobotStarted && digitalRead(startButtonPin) == LOW) {
    isRobotStarted = true;
    delay(100);
    while (digitalRead(startButtonPin) == LOW) {}
  }

  if (!isRobotStarted) {
    return;
  }
  // Add your code here
  line(MODE_FF, GO_STRAIGHT);
  line(MODE_FR, TURN_RIGHT);
}


void line(int desiredMode, int action) {
  while (mode != desiredMode) {
    readSensors();
    switch (mode)
    {
      case NO_LINE:
        motorDrivePID(100, -100);
        previousError = error;
        break;

      case FOLLOWING_LINE:
        calculatePID();
        motorPIDcontrol();
        break;
    }

    if (sensorVal[0] == 0 && sensorVal[4] == 0) {
      mode = MODE_FF;
    } else if (sensorVal[0] == 0 && sensorVal[1] == 0) {
      mode = MODE_FL;
    } else if (sensorVal[3] == 0 && sensorVal[4] == 0) {
      mode = MODE_FR;
    }

    if (mode == desiredMode) {
      motorDrivePID(-50, -50);
      delay(100);
      
      switch (action) {
        case TURN_LEFT:
          motorDrivePID(0, 150);
          delay(1000);
          mode = FOLLOWING_LINE;
          break;
        case TURN_RIGHT:
          motorDrivePID(150, 0);
          delay(1000);
          mode = FOLLOWING_LINE;
          break;
        case GO_STRAIGHT:
          motorDrivePID(150, 150);
          delay(1000);
          mode = FOLLOWING_LINE;
          break;
      }
    }
  }
}

void readSensors()
{
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
  else if ((sensorVal[0] == 0) && (sensorVal[1] == 0) && (sensorVal[2] == 0) && (sensorVal[3] == 0) && (sensorVal[4] == 0)) {
    mode = STOPPED;
    error = 0;
  }
}


void calculatePID()
{
  P = error;
  I += error;
  D = error - previousError;
  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;
}

void motorPIDcontrol()
{

  int speedL = speedRef + (PIDvalue * adj);
  int speedR = speedRef - (PIDvalue * adj);

  // The motor speed should not exceed the max PWM value
  constrain(speedL, -speedRef, speedRef);
  constrain(speedR, -speedRef, speedRef);

  motorDrivePID(speedL, speedR);

  // Serial.print (PIDvalue);
  // Serial.print (" ==> Left, Right:  ");
  // Serial.print (speedL);
  // Serial.print ("   ");
  // Serial.println (speedR);
}
