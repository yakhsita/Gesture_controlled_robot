#include <VirtualWire.h>

#define x A3 
#define y A2
#define z A1

#define buttonPin 2
#define led1 8   // Blue - Car mode
#define led2 9   // Red - Arm mode

char *data;
int x_val, y_val, z_val;
int x_val2, y_val2, z_val2;

int mode = 1;         
int pressCount = 0;
unsigned long lastPressTime = 0;
unsigned long lastGestureTime = 0;
const unsigned long gestureInterval = 500;

void setup() 
{
  vw_set_tx_pin(12);
  vw_setup(2000);

  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.begin(9600);

  x_val2 = analogRead(x);
  y_val2 = analogRead(y);
  z_val2 = analogRead(z);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
}

void handleButtonPress() {
  static bool buttonWasPressed = false;

  if (digitalRead(buttonPin) == LOW) {
    if (!buttonWasPressed) {
      delay(50); // debounce
      if (digitalRead(buttonPin) == LOW) {
        pressCount++;
        lastPressTime = millis();
        buttonWasPressed = true;
        Serial.println("Button Press Detected");
      }
    }
  } else {
    buttonWasPressed = false;
  }

  if (millis() - lastPressTime > 600 && pressCount > 0) {
    Serial.print("Press count: ");
    Serial.println(pressCount);

    if (pressCount == 1) {
      mode = 1; // Car mode
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      Serial.println("Mode: Car");
    } else if (pressCount == 2) {
      mode = 2; // Arm mode
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      Serial.println("Mode: Arm");
    } else if (pressCount == 3) {
      mode = 3; // Back to car mode
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      Serial.println("Mode: Grip");
    } else if (pressCount == 4) {
      mode = 1; // Back to car mode
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      Serial.println("Mode: Car");
    }

    pressCount = 0;
  }
}

void handleCarMode() {
  if (millis() - lastGestureTime < gestureInterval) return;
  lastGestureTime = millis();

  x_val = analogRead(x);
  y_val = analogRead(y);
  z_val = analogRead(z);

  int x_axis = x_val - x_val2;
  int y_axis = y_val - y_val2;
  int z_axis = z_val - z_val2;

  Serial.print("X: "); Serial.println(x_val);
  Serial.print("Y: "); Serial.println(y_val);
  Serial.print("Z: "); Serial.println(z_val);

  if (y_axis >= 25) {
    data = "f";
    Serial.println("Forward");
  } else if (y_axis <= -25) {
    data = "b";
    Serial.println("Backward");
  } else if (x_axis >= 25) {
    data = "r";
    Serial.println("Right");
  } else if (x_axis <= -25) {
    data = "l";
    Serial.println("Left");
  } else {
    data = "s";
    Serial.println("Stop");
  }

  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
}

void handleArmMode() {
  if (millis() - lastGestureTime < gestureInterval) return;
  lastGestureTime = millis();

  x_val = analogRead(x);
  y_val = analogRead(y);
  z_val = analogRead(z);

  int x_axis = x_val - x_val2;
  int y_axis = y_val - y_val2;
  int z_axis = z_val - z_val2;

  Serial.print("X: "); Serial.println(x_val);
  Serial.print("Y: "); Serial.println(y_val);
  Serial.print("Z: "); Serial.println(z_val);

  if (y_axis >= 30) {
    data = "u";  // Shoulder Up
    Serial.println("Shoulder Up");
  } else if (y_axis <= -40) {
    data = "d";  // Shoulder Down
    Serial.println("Shoulder Down");
  } else if (x_axis >= 40) {
    data = "e";  // Elbow Extend
    Serial.println("Elbow Extend");
  } else if (x_axis <= -40) {
    data = "c";  // Elbow Contract
    Serial.println("Elbow Contract");
  } else if (z_axis >= 40) {
    data = "g";  // Gripper Close
    Serial.println("Gripper Close");
  } else if (z_axis <= -40) {
    data = "o";  // Gripper Open
    Serial.println("Gripper Open");
  } else {
    data = "x";  // No action
    Serial.println("Neutral");
  }

  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
}

void handleGripMode() {
  if (millis() - lastGestureTime < gestureInterval) return;
  lastGestureTime = millis();

  data = "g";  // Gripper Close
  Serial.println("Gripper Close");


  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
}

void loop()
{
  handleButtonPress();

  if (mode == 1) {
    handleCarMode();
  } else if (mode == 2) {
    handleArmMode();
  } else if (mode == 3) {
    handleGripMode();
  }
  // You can later add arm mode logic here
}
