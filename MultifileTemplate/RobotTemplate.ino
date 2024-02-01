/*Final project code template
  A template for the final project code that uses multiple files
  for modularity. The compiler first loads the principal file 
  (the one with the same name as the folder) and then loads 
  the others in alphabetical order. Variables defined in an 
  earlier file will be visible to code in a file that is loaded 
  later, but not vice-versa. 

  Calls functions in files:
  AutonomousControl.ino
  RemoteControl.ino

  written for the MSP432401 board
  Adapted from code by Deborah Walters
  Author: Ian Morton
  Last revised: 1/29/2024

***** Hardware Connections: *****
     start button       P3.0
     
     playstation connections
     brown wire         P1.7 
     orange wire        P1.6 
     yellow wire        P2.3
     blue wire          P6.7
*/


// Define high-level state machine
enum RobotState {
  MANUAL,
  INITIALIZE,
  AUTONOMOUS
};


// Declare and initialize the current state variable
RobotState RobotCurrentState = INITIALIZE;

/* updateStateMachine function
  This function changes the high-level state based on user input. 
  
  For an example, a SPST button (using internal pullup resistor) is used
  to change state from INITIALIZE to MANUAL. The playstation circle 
  button is used to change the state from MANUAL to AUTONOMOUS.
*/
void updateStateMachine() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
        // go to Autonomous state when circle button pushed
        RobotCurrentState = MANUAL;
      }
      break;

    case MANUAL:
      if (ps2x.ButtonPressed(PSB_CIRCLE)) {
        // go to Autonomous state when circle button pushed
        RobotCurrentState = AUTONOMOUS;
      }
      break;

    case AUTONOMOUS:
      if (ps2x.ButtonPressed(PSB_SQUARE)) {
        // go to manual state when square button pushed
        RobotCurrentState = MANUAL;
        // reset autonomous state to start state for the next time
        AutoCurrentState = AUTO_TOWALL; 
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
      Serial.println("Initialzing");

      break;
    case AUTONOMOUS:
      // Perform actions for the autonomous state
      AutonomousControl();
      Serial.println("It is in autonomous mode");
      // Add any additional actions for the autonomous state
      break;

    case MANUAL:
      // Perform actions for the manual state
      RemoteControl();
      Serial.println("It is in Manual mode");
      // Add any additional actions for the manual state
      break;
  }
}
