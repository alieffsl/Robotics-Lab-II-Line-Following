#include "LINEFOLL_EKSBOT.h"
#include <util/atomic.h>
#include <AX12A.h>
#include <Arduino.h>

bool state = false;

void setup() {
  eksbotInit();
  Serial.begin(9600);
}

void loop()
{
  autolinefollow();
}