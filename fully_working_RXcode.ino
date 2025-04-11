#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <VirtualWire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // Default I2C addr: 0x40

// Servo pulse range
#define SERVO_MIN 150  // Min pulse length out of 4096
#define SERVO_MAX 600  // Max pulse length out of 4096

// Current positions
int shoulderPos = 375;
int elbowPos = 375;
int clawPos = 375;

void setup() {
  Serial.begin(9600);

  // Setup PWM driver
  pwm.begin();
  pwm.setPWMFreq(50);  // Standard servo freq

  // Setup VirtualWire
  vw_set_rx_pin(11);
  vw_setup(2000);
  vw_rx_start();

  Serial.println("Robotic Arm Test Ready");
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    char command = buf[0];
    Serial.print("Received: "); Serial.println(command);

    switch (command) {
      case 'u':  // Shoulder Up
        shoulderPos = constrain(shoulderPos + 15, SERVO_MIN, SERVO_MAX);
        pwm.setPWM(1, 0, shoulderPos);
        Serial.println("Shoulder Up");
        break;
      case 'd':  // Shoulder Down
        shoulderPos = constrain(shoulderPos - 15, SERVO_MIN, SERVO_MAX);
        pwm.setPWM(1, 0, shoulderPos);
        Serial.println("Shoulder Down");
        break;
      case 'e':  // Elbow Extend
        elbowPos = constrain(elbowPos + 15, SERVO_MIN, SERVO_MAX);
        pwm.setPWM(2, 0, elbowPos);
        Serial.println("Elbow Extend");
        break;
      case 'c':  // Elbow Contract
        elbowPos = constrain(elbowPos - 15, SERVO_MIN, SERVO_MAX);
        pwm.setPWM(2, 0, elbowPos);
        Serial.println("Elbow Contract");
        break;
      case 'g':  // Gripper Close
        clawPos = constrain(clawPos + 15, SERVO_MIN, SERVO_MAX);
        pwm.setPWM(3, 0, clawPos);
        Serial.println("Gripper Close");
        break;
      case 'o':  // Gripper Open
        clawPos = constrain(clawPos - 15, SERVO_MIN, SERVO_MAX);
        pwm.setPWM(3, 0, clawPos);
        Serial.println("Gripper Open");
        break;
      case 'x':  // Neutral / No action
        Serial.println("Neutral");
        break;
      default:
        Serial.println("Unknown command");
    }
  }
}
