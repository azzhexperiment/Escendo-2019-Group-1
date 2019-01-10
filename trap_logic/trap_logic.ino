#define 

int switchState, trigger, gateState;

void setup() {

}

void loop() {
  flushSwitch();

  for (i = 0; i < 3; i++) {
    if (switchState[i] == 1) {
      redLight[i];
      triggerDetection();
      greenLight[i];
    }
  }

  openGate();
  
  redLight[3];
  while (trigger[3] == 1) {
    continue();
  }

  flushSwitch();

  for (i = 0; i < 4; i++) {
    if (switchState[i] == 1) {
      redLight[i];
      greenLight[i];
    }
  }

  openGate();
}

//  Randomly resets the switches' states between ON and OFF
//  Switch 4 is ALWAYS ON
void flushSwitch() {
  switchState[3] = {
    floor(random(0, 2)),
    floor(random(0, 2)),
    floor(random(0, 2)),
    1
  }

  trigger[] = switchStatus[];
}

void triggerDetection(i) {
  do {
    if (TRIGGERED) {
      trigger[i] = 0;
    }
  }
  while (trigger[i] == 1)
}

void openGate() {
  if (LED[3] == 1) {
    openGate[1];
  }

  else {
    openGate[0];
  }
}
