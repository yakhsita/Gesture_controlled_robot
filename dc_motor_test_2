#include <AFMotor.h>

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {

  motor3.setSpeed(200);
  motor4.setSpeed(200);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}

void loop() {
  
  // FORWARD
  motor3.run(BACKWARD);
  motor4.run(FORWARD);

  delay(4000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(200);
  
  // BACKWARD
  motor3.run(FORWARD);
  motor4.run(BACKWARD);

  delay(4000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(200);

  // RIGHT
  motor3.run(BACKWARD);
  motor4.run(RELEASE);
  
  delay(4000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(200);
  
  // LEFT
  motor3.run(RELEASE);
  motor4.run(FORWARD);

  delay(4000);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(200);
 
}
