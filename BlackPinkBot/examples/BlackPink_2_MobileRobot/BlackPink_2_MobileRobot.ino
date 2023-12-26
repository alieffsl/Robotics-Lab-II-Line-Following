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

#include <BLACKPINKBOT.h>

void setup() {
  Serial.begin(9600);
  eksbotInit();
}

void loop() {
  char key = keypad.getKey();
  if (key) selectMode(key);
}

void selectMode(char key){
  Serial.println(key);

  switch(key){
    case '1':
      buzzer(1,50,0);
      FWD(30,150);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(100);
      BWD(30,200);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      TR(90);
      break;
    case '2':
      buzzer(1,50,0);
      FWD(60,200);
      L(60,150);
      BWD(60,200);
      TR(50);
      FWD(60,200);
      break;
    case '3':
      buzzer(1,50,0);
      break;
    case '4':
      buzzer(1,50,0);
      break;
    case '5':
      buzzer(1,50,0);
      break;
    case '6':
      buzzer(1,50,0);
      break;
    case '7':
      buzzer(1,50,0);
      break;
    case '8':
      buzzer(1,50,0);
      break;
    case '9':
      buzzer(1,50,0);
      break;
  }

}