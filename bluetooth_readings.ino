#include <VirtualWire.h>
#include <SoftwareSerial.h>
SoftwareSerial bt(9, 8); // RX, TX

#define x A3
#define y A2
#define z A1

char *data;
//char output[10];

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
  bt.begin(9600);
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
  bt.print(x_val); //send x value to MIT App
  bt.print(";");
  bt.print(y_val); //send y value to MIT App
  bt.print(";");
  bt.print(z_val); //send z value to MIT App
  bt.print(";");
  //Serial.print("      ");
  //Serial.println(output);
  Serial.print("Z: ");
  Serial.println(z_val);

  int x_axis = x_val - x_val2;
  int y_axis = y_val - y_val2;
  int z_axis = z_val - z_val2;
  
  if(y_axis >= 35)
  {
    data="f";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    //output={"F","o","r","w","a","r","d","\0"};
    Serial.println("Forward");
    //bt.print(data); //send Command to MIT App 
  }
  else if(y_axis <= -35)
  {
    data="b";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    //output={"B","a","c","k","w","a","r","d","\0"};
    Serial.println("Backward");
    //bt.print(data); //send Command to MIT App 
  }
  else if(x_axis >= 35)
  {
    data="r";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    //output={"R","i","g","h","t","\0"};
    Serial.println("Right");
    //bt.print(data); //send Command to MIT App 
  }
  else if(x_axis <= -35)
  {
    data="l";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    //output={"L","e","f","t","\0"}
    Serial.println("Left");
    //bt.print(data); //send Command to MIT App 
  }
  else
  {
    data="s";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    //output={"S","t","o","p","\0"}
    Serial.println("Stop");
    //bt.print(data); //send Command to MIT App 
  }
  Serial.println();
}
