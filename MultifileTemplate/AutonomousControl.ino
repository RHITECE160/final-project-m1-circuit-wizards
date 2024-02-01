/*
  AutonomousControl.ino - Arduino Sketch for Autonomous Control of the RLSK robot
  
  Description:
  This sketch provides functions for autonomous action of an RLSK robot. A state
  machine is used for autonomous control. A few actions have been programed as
  an example. 

  The robot moves forward for a time (defined by movementDuration). Then 
  transitions to a number of other states. After reaching the final state, 
  the higher-level state is switched to IDLE to await the next instruction.

  State Machine description:
  The robot moves forward until it detects a wall, then stops when there is a wall within 130mm. Spins right
  for 1130ms then goes forward for 1700ms. Moves into linefollowing state, follows line until wall detected
  within 70mm, then stops and opens the grip. Moves into Idle mode, finishes function allowing switch to manual mode.


  Created by: Ian Morton, Chengyang Ye
  Date: Current Date
  Version: 1.0
*/

// Define lower-level state machine for AUTONOMOUS mode
enum AutoState {
  AUTO_TOWALL,
  AUTO_LINEFOLLOW,
  IDLE
};

AutoState AutoCurrentState = AUTO_TOWALL;

uint16_t distValue; 
uint16_t distMM; 
float distIN;
float light = analogRead(A5);

void AutonomousControl() {
  // put your code here to run in Autonomous control mode

  Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE) {
    switch (AutoCurrentState) {
      case AUTO_TOWALL:
        //move forward then update sensor
        forward();  
        LaserSensor();
        // Check if the movement duration has passed
        if (distMM < 130) {
          stop();// Record the time when the forward state started
          spinRight();
          delay(1130);
          forward();
          delay(1700);
          AutoCurrentState = AUTO_LINEFOLLOW;
        }
        
        break;

      case AUTO_LINEFOLLOW:
         
        // Add state instructions here
        Serial.println("Linefollowing");
        LaserSensor();
        linefollowing();
         if (distMM < 70) {
            Serial.println("Time to stop");
            stop();
            myservo.write(30);
            AutoCurrentState = IDLE;
        }
        break;

      

      default:
        // Handle unknown state, if needed
        break;
    }
  }
  // The code will exit the while loop when IDLE state is reached

  // Add IDLE state instructions here

}

void judgeautotype(){
  if (light > 250 || getLinePosition() != 0) {
    AutoCurrentState = AUTO_LINEFOLLOW;
  } else {
    AutoCurrentState = AUTO_TOWALL;
  }
}

uint8_t SensorPos = 1; // sets the sensor pin used

void LaserSensor() {
  //reads the distance as 14bit integer
  distValue = readSharpDist(SensorPos);

  //reads the distance in millimeters
  distMM = readSharpDistMM(SensorPos);

  //reads the distance in inches
  distIN = readSharpDistIN(SensorPos);

  Serial.println(distMM);
}

