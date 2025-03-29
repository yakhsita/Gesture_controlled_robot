/* Receiver code for Gesture_controlled_robot */

#include <VirtualWire.h>
#include <AFMotor.h>

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup()
{
    vw_set_rx_pin(11);
    vw_setup(2000);
    motor3.setSpeed(100);
    motor4.setSpeed(100);
    vw_rx_start();
    Serial.begin(9600);
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN; 
 
    if (vw_get_message(buf, &buflen))
    {
      if(buf[0]=='f')
      {  
       motor3.run(BACKWARD);
       motor4.run(FORWARD);
       Serial.println("Forward");
      }  
      else if(buf[0]=='b')
      {
       motor3.run(FORWARD);
       motor4.run(BACKWARD);
       Serial.println("Backward");
      }
      else if(buf[0]=='r')
      {
       motor3.run(BACKWARD);
       motor4.run(RELEASE);
       Serial.println("Left");
      }
      else if(buf[0]=='l')
      {
       motor3.run(RELEASE);
       motor4.run(FORWARD);
       Serial.println("Right");
      }
      else if(buf[0]=='s')            
      {
       motor3.run(RELEASE);
       motor4.run(RELEASE);
       Serial.println("Stop");
      }
    }
}
