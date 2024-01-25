/*Final project code template
  A template for the final project code that uses multiple files
  for modularity. The compiler first loads the principal file 
  (the one with the same name as the folder) and then loads 
  the others in alphabetical order. Variables defined in an 
  earlier file will be visible to code in a file that is loaded 
  later, but not vice-versa. 

  Calls functions in files:
  AutonomousControl.ino
  MotorFunctions.ino
  RemoteControl.ino

  written for the MSP432401 board
  Author: Deborah Walter
  Last revised: 11/28/2023

***** Hardware Connections: *****
     start button       P3.0
     
     playstation connections
     brown wire         P1.7 
     orange wire        P1.6 
     yellow wire        P2.3
     blue wire          P6.7
*/

// Load libraries used
#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"

// Define high-level state machine
enum RobotState {
  INITIALIZE,
  MANUAL,
  AUTONOMOUS
};

// Define lower-level state machine for AUTONOMOUS mode
enum AutoState {
  START,
  AUTO_ACTION1,
  AUTO_ACTION2,
  AUTO_ACTION3,
  AUTO_ACTION4,
  IDLE
};

// Declare and initialize the current state variable
RobotState RobotCurrentState = INITIALIZE;
AutoState AutoCurrentState = START;

/* updateStateMachine function
  This function changes the high-level state based on user input. 
  
  For an example, a SPST button (using internal pullup resistor) is used
  to change state from INITIALIZE to MANUAL. The playstation circle 
  button is used to change the state from MANUAL to AUTONOMOUS.
*/
void updateStateMachine() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      if (digitalRead(START_BUTTON) == 0) {
        Serial.print("start button has been pressed going to manual");
        //go to Manual state when start button pushed
        RobotCurrentState = MANUAL;
      }
      break;

    case MANUAL:
      Serial.print("in manual state........");
      if (ps2x.Button(PSB_CIRCLE)) {
        // go to Autonomous state when circle button pushed
        RobotCurrentState = AUTONOMOUS;
      }
      break;

    case AUTONOMOUS:
      Serial.print("in autonomous state........");
      if (ps2x.Button(PSB_SQUARE)) {
        // go to manual state when square button pushed
        RobotCurrentState = MANUAL;
        // reset autonomous state to start state for the next time
        AutoCurrentState = START; 
      }

      break;
  }
}

/* executeStateActions function
  This function executes the proper actions for each state. 
  
  For an example, two functions are called, RemoteControl and 
  AutonomousControl. These functions are located in their respective
  files to make the code easier to read and modify.
*/
void executeStateActions() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      // Perform actions for the initialize state
      Serial.println("Initializing...");
      // Add any additional actions for the initialize state
      break;

    case AUTONOMOUS:
      // Perform actions for the autonomous state
      Serial.println("Autonomous Mode");
      AutonomousControl();
      // Add any additional actions for the autonomous state
      break;

    case MANUAL:
      // Perform actions for the manual state
      Serial.println("Manual Mode");
      RemoteControl();
      // Add any additional actions for the manual state
      break;
  }
}
