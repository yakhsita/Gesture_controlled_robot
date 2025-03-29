#define x A3
#define y A2
#define z A1

int x_val;
int y_val;
int z_val;

int x_val2;
int y_val2;
int z_val2;

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
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

  if(y_axis >= 20)
  {
    Serial.println("Forward");
  }
  else if(y_axis <= -20)
  {
    Serial.println("Backward");
  }
  else if(x_axis >= 20)
  {
    Serial.println("Right");
  }
  else if(x_axis <= -20)
  {
    Serial.println("Left");
  }
  else
  {
    Serial.println("Stop");
  }
  Serial.println();
  delay(1000);
}

