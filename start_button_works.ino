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

int mode = 0;         // 1 = Car Mode, 2 = Arm Mode
int pressCount = 0;
unsigned long lastPressTime = 0;

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

  digitalWrite(led1, HIGH); // Start in Car mode
  digitalWrite(led2, LOW);
}

void loop()
{
  // Handle button presses
  if (digitalRead(buttonPin) == LOW) {
    delay(50);  // debounce
    if (digitalRead(buttonPin) == LOW) {
      pressCount++;
      lastPressTime = millis();
      while (digitalRead(buttonPin) == LOW);  // wait until button is released
    }
  }

  // Check if enough time has passed to evaluate presses
  if (millis() - lastPressTime > 600 && pressCount > 0) {
    Serial.print("Press count:");
    Serial.println(pressCount);
    if (pressCount == 1) 
    {
      while (pressCount==1)
      {
        mode = 1; // Car mode
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        Serial.println("Mode: Car");
        if (mode == 1) 
        {
          // Only send gesture data in Car mode
          x_val = analogRead(x);
          y_val = analogRead(y);
          z_val = analogRead(z);

          // prints the value in the serial monitor
          Serial.print("X: ");
          Serial.println(x_val);
          Serial.print("Y: ");
          Serial.println(y_val);
          Serial.print("Z: ");
          Serial.println(z_val);

          int x_axis = x_val - x_val2;
          int y_axis = y_val - y_val2;
          int z_axis = z_val - z_val2;
          
          if(y_axis >= 25)
          {
            data="f";
            vw_send((uint8_t *)data, strlen(data));
            vw_wait_tx();
            delay(500);
            Serial.println("Forward");
          }
          else if(y_axis <= -25)
          {
            data="b";
            vw_send((uint8_t *)data, strlen(data));
            vw_wait_tx();
            delay(500);
            Serial.println("Backward");
          }
          else if(x_axis >= 25)
          {
            data="r";
            vw_send((uint8_t *)data, strlen(data));
            vw_wait_tx();
            delay(500);
            Serial.println("Right");
          }
          else if(x_axis <= -25)
          {
            data="l";
            vw_send((uint8_t *)data, strlen(data));
            vw_wait_tx();
            delay(500);
            Serial.println("Left");
          }
          else
          {
            data="s";
            vw_send((uint8_t *)data, strlen(data));
            vw_wait_tx();
            delay(500);
            Serial.println("Stop");
          }
          Serial.println();
        }
      }
    } else if (pressCount == 2) {
      mode = 2; // Arm mode
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      Serial.println("Mode: Arm");
    } else if (pressCount == 3) {
      mode = 1; // Back to car mode
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      Serial.println("Mode: Car");
    }
    pressCount = 0;
  }
}
