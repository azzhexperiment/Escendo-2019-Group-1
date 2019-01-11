#include <Adafruit_NeoPixel.h>

#define switchNum 3

// Constructor: number of LEDs, pin number, LED type
Adafruit_NeoPixel pixel_0 = Adafruit_NeoPixel(1, 3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(1, 4, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel_2 = Adafruit_NeoPixel(1, 5, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel_3 = Adafruit_NeoPixel(1, 6, NEO_RGB + NEO_KHZ800);

int LDRpin[] = {A0, A1, A2, A3}; // Input array for LDR
int LDRvalue =  0;
int i = 0;

int switchState[switchNum], trigger[switchNum], gateState;

void setup() {
  pixel_0.begin();
  pixel_0.show();
  pixel_1.begin();
  pixel_1.show();
  pixel_2.begin();
  pixel_2.show();
  pixel_3.begin();
  pixel_3.show();
  Serial.begin(9600);
}

void loop() {
  flushSwitch();

  Serial.println("Lights flushed");

  for (i = 0; i < 3; i++) {
    if (switchState[i] == 1) {
      if (i == 0) {
        pixel_0.setPixelColor(0, pixel_0.Color(0, 255, 0));
        pixel_0.show();

        Serial.println("Switch 0 round 1 is RED!");
      }
      else if (i == 1) {
        pixel_1.setPixelColor(0, pixel_1.Color(0, 255, 0));
        pixel_1.show();

        Serial.println("Switch 1 round 1 is RED!");
      }
      else {
        pixel_2.setPixelColor(0, pixel_2.Color(0, 255, 0));
        pixel_2.show();

        Serial.println("Switch 2 round 1 is RED!");
      }

      triggerDetection(i);
      Serial.println("You should see me ONLY after trigger detection!");

      if (i == 0) {
        pixel_0.setPixelColor(0, pixel_0.Color(255, 0, 0));
        pixel_0.show();
        Serial.println("Switch 0 round 1 is GREEN!");
      }
      else if (i == 1) {
        pixel_1.setPixelColor(0, pixel_1.Color(255, 0, 0));
        pixel_1.show();
        Serial.println("Switch 1 round 1 is GREEN!");
      }
      else {
        pixel_2.setPixelColor(0, pixel_2.Color(255, 0, 0));
        pixel_2.show();
        Serial.println("Switch 2 round 1 is GREEN!");
      }
    }
  }

  pixel_3.setPixelColor(0, pixel_3.Color(0, 255, 0));
  pixel_3.show();
  
  openGate();
  
  triggerDetection(3);
  Serial.println("Trigger detection is functioning as designed!");

  flushSwitch();

  for (i = 0; i < 4; i++) {
    if (switchState[i] == 1) {
      if (i == 0) {
        pixel_0.setPixelColor(0, pixel_0.Color(0, 255, 0));
        pixel_0.show();

        Serial.println("Switch 0 round 2 is RED!");
      }
      else if (i == 1) {
        pixel_1.setPixelColor(0, pixel_1.Color(0, 255, 0));
        pixel_1.show();

        Serial.println("Switch 1 round 2 is RED!");
      }
      else if (i == 2) {
        pixel_2.setPixelColor(0, pixel_2.Color(0, 255, 0));
        pixel_2.show();

        Serial.println("Switch 2 round 2 is RED!");
      }
      else {
        pixel_3.setPixelColor(0, pixel_3.Color(0, 255, 0));
        pixel_3.show();

        Serial.println("Switch 3 round 2 is RED!");
      }

      triggerDetection(i);

      if (i == 0) {
        pixel_0.setPixelColor(0, pixel_0.Color(255, 0, 0));
        pixel_0.show();

        Serial.println("Switch 0 round 2 is GREEN!");
      }
      else if (i == 1) {
        pixel_1.setPixelColor(0, pixel_1.Color(255, 0, 0));
        pixel_1.show();

        Serial.println("Switch 1 round 2 is GREEN!");
      }
      else if (i == 2) {
        pixel_2.setPixelColor(0, pixel_2.Color(255, 0, 0));
        pixel_2.show();

        Serial.println("Switch 2 round 2 is GREEN!");
      }
      else {
        pixel_3.setPixelColor(0, pixel_3.Color(255, 0, 0));
        pixel_3.show();

        Serial.println("Switch 3 round 2 is GREEN!");
      }
    }
  }

  openGate();
}

//  Randomly resets the switches' states between ON and OFF
//  Switch 3 is ALWAYS ON
void flushSwitch() {
  for (i = 0; i < switchNum; i++) {
    switchState[i] = floor(random(0, 2));
    Serial.println(switchState[i]);
  }

  switchState[switchNum] = 1;

  for(i = 0; i <= switchNum; i++){
    trigger[i] = switchState[i];
  }
}

int triggerDetection(int i) {
  while (trigger[i] == 1) {
    LDRvalue = analogRead(LDRpin[i]); // read the value from the sensor

    Serial.println(LDRvalue);
    
    if (LDRvalue <= 5) {
      trigger[i] = 0;

      Serial.println("Overwritten!");
    }

    else {
      Serial.println("Stuck in loooooop!");
    }
  }
}

void openGate() {
  if (pixel_3.getPixelColor(16) == 1)
    Serial.println("GATE 2 IS NOW OPENED!");

  else
    Serial.println("GATE 1 IS NOW OPENED!");
}
