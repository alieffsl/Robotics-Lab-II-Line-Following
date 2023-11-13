//*************************************************************************************
// Eksbot II 2023
// ----------------------------- 
//  line: line(mode);
//     FRONT   --> stop when sensors 1 and 5 pass the line after sensors 1 and 5 detect the line in the crosstime
//     LEFT    --> stop when sensors 1 and 2 pass the line after sensors 1 and 2 detect the line in the crosstime
//     RIGHT   --> stop when sensors 4 and 5 pass the line after sensors 4 and 5 detect the line in the crosstime
//
//  turn: turn(direction);
//     FORWARD  --> Continue moving straight after meeting the specified mode condition.
//     LEFT     --> Turn the robot left after meeting the specified mode condition.
//     RIGHT    --> Turn the robot right after meeting the specified mode condition.
//
//  turnLeft(speed, dtime);
//  turnRight(speed, dtime);
//  stopRobot(dtime);
//  goForward(speed, dtime);
//  goBackward(speed, dtime);
//
//*************************************************************************************

#include "LINEFOLL_EKSBOT.h"
#include <util/atomic.h>
#include <AX12A.h>
#include <Arduino.h>

bool state = false;

void setup() {
  eksbotInit();
  Serial.begin(9600);
}

void loop() {
  toggleRobot(state);

  if (state) {
  // put your main code here:
  //--------------------------------
    line(FRONT);
    turn(LEFT);
    goForward(150, 1000);

  //--------------------------------
    stop_end(state);
  //--------------------------------
  }

}