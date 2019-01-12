#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define switchNum 4

// Constructor: number of LEDs, pin number, LED type
Adafruit_NeoPixel pixel_0 = Adafruit_NeoPixel(1, 3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(1, 4, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel_2 = Adafruit_NeoPixel(1, 5, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel_3 = Adafruit_NeoPixel(1, 6, NEO_RGB + NEO_KHZ800);

int LDRpin[] = {A0, A1, A2, A3}; // Input array for LDR
double LDRvalueMax = 0, LDRvalueMin = 0, LDRvalue = 0;
int switchState[switchNum], trigger[switchNum], i = 0;
int  gate1 = 0,  gate2 = 0;
int servo1 = 9, servo2 = 10;

Servo servogate1;
Servo servogate2;

void setup() {
  servogate1.attach(servo1);
  servogate2.attach(servo2);
  servogate1.write(0);
  servogate2.write(0);
  
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

  // Part 1
  flushSwitch();

  Serial.println("Lights flushed");

  for (i = 0; i < (switchNum - 1); i++) {
    Serial.print("This switchState: ");
    Serial.println(switchState[i]);
    if (switchState[i] == 1) {
      Serial.println("This is part 1");
      
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

  pixel_3.setPixelColor(0, pixel_3.Color(0, 255, 0)); // Set last switch to red
  pixel_3.show();

  openGate1();

  triggerDetection(3);
  Serial.println("Trigger detection for last switch is functioning as designed!");

  flushSwitch();

  pixel_3.setPixelColor(0, pixel_3.Color(0, 255, 255)); // Set last switch to magenta
  pixel_3.show();

  Serial.println("Ready for round 2???");

  // Part 2
  for (i = 0; i < switchNum; i++) {
    Serial.print("This switchState: ");
    Serial.println(switchState[i]);
    if (switchState[i] == 1) {

      Serial.println("This is part 2");

      if (i == 0) {
        pixel_0.setPixelColor(0, pixel_0.Color(0, 255, 0));
        pixel_0.show();
        Serial.println("Switch 0 round 2 is REEEED!");
      }
      else if (i == 1) {
        pixel_1.setPixelColor(0, pixel_1.Color(0, 255, 0));
        pixel_1.show();
        Serial.println("Switch 1 round 2 is REEEED!");
      }
      else if (i == 2) {
        pixel_2.setPixelColor(0, pixel_2.Color(0, 255, 0));
        pixel_2.show();
        Serial.println("Switch 2 round 2 is REEEED!");
      }
      else {
        pixel_3.setPixelColor(0, pixel_3.Color(0, 255, 0));
        pixel_3.show();
        Serial.println("Switch 3 round 2 is REEEED!");
      }

      triggerDetection(i);

      if (i == 0) {
        pixel_0.setPixelColor(0, pixel_0.Color(255, 0, 0));
        pixel_0.show();
        Serial.println("Switch 0 round 2 is GREEEEEN!");
      }
      else if (i == 1) {
        pixel_1.setPixelColor(0, pixel_1.Color(255, 0, 0));
        pixel_1.show();
        Serial.println("Switch 1 round 2 is GREEEEEN!");
      }
      else if (i == 2) {
        pixel_2.setPixelColor(0, pixel_2.Color(255, 0, 0));
        pixel_2.show();
        Serial.println("Switch 2 round 2 is GREEEEEN!");
      }
      else {
        pixel_3.setPixelColor(0, pixel_3.Color(255, 0, 0));
        pixel_3.show();
        Serial.println("Switch 3 round 2 is GREEEEEN!");

        openGate2();
      }
    }
  }

  while (1) {
    continue;
  }
}

// Resets the switches' states
void flushSwitch() {

  // Randomly resets the switch states between 0 and 1
  for (i = 0; i < (switchNum - 1); i++) {
    switchState[i] = floor(random(0, 2));
    Serial.println("This is switch ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(switchState[i]);
  }

  // Last switch is ALWAYS ON
  switchState[switchNum - 1] = 1;
    Serial.println("This is switch ");
    Serial.print(3);
    Serial.print(": ");
    Serial.println(switchState[3]);

// Set switchState as trigger state
  for(i = 0; i < (switchNum - 1); i++){
    trigger[i] = switchState[i];
    Serial.println("The new trigger ");
    Serial.print(i);
    Serial.print(" is: ");
    Serial.println(trigger[i]);
  }

  trigger[switchNum - 1] = 1;
  Serial.println("The new trigger 3 is: ");
  Serial.println(trigger[switchNum - 1]);
}

int triggerDetection(int i) {
  LDRvalueMax = analogRead(LDRpin[i]);  // Initialise LDRvalueMax
  LDRvalueMin = analogRead(LDRpin[i]);  // Initialise LDRvalueMin

  while (trigger[i] == 1) {
    LDRvalue = analogRead(LDRpin[i]); // read the value from the sensor

    // Update LDRvalueMax
    if (LDRvalueMax < LDRvalue) {
      LDRvalueMax = LDRvalue;

      Serial.println("Updated LDRvalueMax is: ");
      Serial.println(LDRvalueMax);
    }

    // Update LDRvalueMin
    if (LDRvalueMin > LDRvalue) {
      LDRvalueMin = LDRvalue;

      Serial.println("Updated LDRvalueMin is: ");
      Serial.println(LDRvalueMin);
    }

    Serial.println(LDRvalue);

    if ((LDRvalueMin / LDRvalueMax) < 0.05) {
      Serial.println("This is LDRvalueMin: ");
      Serial.print(LDRvalueMin);
      Serial.println();
      Serial.println("This is LDRvalueMax: ");      
      Serial.print(LDRvalueMax);

      trigger[i] = 0;

      Serial.println("This is relative value: ");
      Serial.print(LDRvalueMin / LDRvalueMax);
      Serial.println();  
      Serial.println("Overwritten!");
    }

    else {
      Serial.println("Stuck in loooooop!");
    }
  }
}

void openGate1() {
  servogate1.write(90);
  Serial.println("GATE 1 IS NOW OPENED!");
}

void openGate2() {
  servogate2.write(90);
  Serial.println("GATE 2 IS NOW OPENED!");
}
