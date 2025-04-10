#include <VirtualWire.h>

#define x A3
#define y A2
#define z A1

char *data;

int x_val;
int y_val;
int z_val;

int x_val2;
int y_val2;
int z_val2;

void setup() 
{
  vw_set_tx_pin(12);
  vw_setup(2000);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);
  Serial.begin(9600);
  x_val2 = analogRead(x);
  y_val2 = analogRead(y);
  z_val2 = analogRead(z);
}

void loop()
{
  x_val = analogRead(x);
  y_val = analogRead(y);
  z_val = analogRead(z);

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
