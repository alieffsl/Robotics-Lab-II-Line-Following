/******************************************************************************
 * M. Alief Faisal Hakim @ TRKB UNAIR
 * -------------------------------------
 * Servo: servoAngkut(dtime), servoTaruh(dtime), servoReset(dtime)
 * Motor: motorDrivePID(speedL, speedR), move(speedFL, speedFR, speedRL, speedRR),
 *        StopMotors();
 *
 * Line Following Functions:
 *   - autolinefollow(duration, dbreaktime);
 *   - line(desiredMode, desiredSpeed, dbreaktime);
 *   - turn(action);
 *   - findline(speedL, speedR, dbreaktime);
 *   - dnext();
 *   - spinheading(sudut);
 *   - linedelay(speed, dtime, dbreaktime);
 *   - linefoll();
 *   - lineIntersect(n);
 *
 * Encoder Functions:
 *   - FWD(distanceCM, speed);
 *   - BWD(distanceCM, speed);
 *   - R(distanceCM, speed);
 *   - L(distanceCM, speed);
 *   - FWD_XR(distanceCM, speed);
 *   - FWD_XL(distanceCM, speed);
 *   - BWD_XR(distanceCM, speed);
 *   - BWD_XL(distanceCM, speed);
 *   - TR(distanceCM=25, speed=200);
 *   - TL(distanceCM=25, speed=200);
 ******************************************************************************/

#include "BLACKPINKBOT.h"

void setup() {
  Serial.begin(9600);
  eksbotInit();
}

void loop() {
  char key = keypad.getKey();
  if (key) selectMode(key);
}

void selectMode(char key) {
  Serial.println(key);

  switch (key) {
    case '1':
      // Perform action for '1'
      break;

    case '2':
      // Perform action for '2'
      break;

    case '3':
      // Perform action for '3'
      break;

    case '4':
      // Perform action for '4'
      break;

    case '5':
      // Perform action for '5'
      break;

    case '6':
      // Perform action for '6'
      break;

    case '7':
      // Perform action for '7'
      break;

    case '8':
      // Perform action for '8'
      break;

    case '9':
      // Perform action for '9'
      break;

    default:
      // Handle invalid input
      break;
  }
}
