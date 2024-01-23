/*A multifile project code template
  A template for the Milestone 1 project code that uses multiple files
  for modularity. The compiler first loads the principal file 
  (the one with the same name as the folder) and then loads 
  the others in alphabetical order. Variables defined in an 
  earlier file will be visible to code in a file that is loaded 
  later, but not vice-versa. 

  Calls functions in files:
  MotorFunctions.ino

  written for the MSP432401 board
  Author: Chengyang Ye; Ian Morton; Tom Cai
  Last revised: 1/21/2024

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
#include <TinyIRremote.h>

// Define pin numbers for the button on the PlayStation controller
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define IR_RCV_PIN      33
IRreceiver irRX(IR_RCV_PIN);
IRData IRresults;
// Create an instance of the playstation controller object
PS2X ps2x;
// Define remote mode either playstation controller or IR remote controller

Servo myservo;
int pos=0;
enum RemoteMode {
  PLAYSTATION,
  IR_REMOTE,
};

// Declare and initialize the current state variable
RemoteMode CurrentRemoteMode = PLAYSTATION;

// Tuning Parameters
const uint16_t slowSpeed = 15;
const uint16_t fastSpeed = 30;

void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... ");
  setupRSLK();
  myservo.attach(SRV_0);
// attaches the servo on Port 1, pin 5 to the servo object

  // Run setup code

    // using the playstation controller
    Serial.println("Using playstation controller, make sure it is paired first ");

    // Initialize PlayStation controller
    delayMicroseconds(500 * 1000);  //added delay to give wireless ps2 module some time to startup, before configuring it
    // declare variables for playstation control
    bool pressures = false;
    bool rumble = false;
    int error = 1;

    while (error) {
      error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

      if (error == 0)
        Serial.println("Found Controller, configured successful ");

      else if (error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

      else if (error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

      else if (error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
      delayMicroseconds(1000 * 1000);
    }
     //use the IR control mode
    Serial.begin(57600);
    delay(500); // To be able to connect Serial monitor after reset or power up 
    Serial.println(F("START " __FILE__ " from " __DATE__));
    if (irRX.initIRReceiver()) {
        Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_RCV_PIN)));
    } else {
        Serial.println("Initialization of IR receiver failed!");
        while (1) {;}
    }
    // enable receive feedback and specify LED pin number (defaults to LED_BUILTIN)
    enableRXLEDFeedback(BLUE_LED);
  

}

void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode
  if (CurrentRemoteMode == 0) {
    Serial.println("Running remote control with the Playstation Controller");
    RemoteControlPlaystation();
    // run using the ps2 controller
  } else if (CurrentRemoteMode == 1) {
    Serial.println("Running remote control with the IR Controller");
    if (irRX.decodeIR(&IRresults)) {
    movementIR();
    }
    //  run using the IR controller 
  }
}


  /* RemoteControlPlaystation() function
  This function uses a playstation controller and the PLSK libraray with
  an RLSK robot using to implement remote controller. 
  
  A few actions are programed for an example. 

  Button control map:
  PAD UP button moves both motors forward
  CROSS button stops motors
  */

  void RemoteControlPlaystation() {
    // put your code here to run in remote control mode

    // Example of receive and decode remote control command
    // the forward() and stop() functions should be independent of
    // the control methods
    if (ps2x.Analog(PSS_LY)>180) {
      Serial.println("Reverse");
      reverse(); // move L3 down so it will reverse
    } else if (ps2x.Analog(PSS_LY)<60) {
      Serial.println("Forward");
      forward(); // move L3 up so it will forward
    } else if (ps2x.Analog(PSS_RX)>180){
      Serial.println("Turn Right");
      turnRight();// move R3 to right so it will turn right
    } else if (ps2x.Analog(PSS_RX)<60){
      Serial.println("Turn Left");
      turnLeft(); // move L3 to left so it will turn left
    } else if (ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("Spin Right");
      spinRight(); // press pad right so it will spin right
    } else if (ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("Spin Left");
      spinLeft(); // press pad left so it will spin left
    } else if (ps2x.Button(PSB_CROSS)){
      CurrentRemoteMode = IR_REMOTE; // press cross so it will change remote mode
    } else if (ps2x.Button(PSB_L3)){
      servomovement_open(); // press L3 so the servo will function
    } else if (ps2x.Button(PSB_R3)){
      servomovement_close(); // press L3 so the servo will function
    } else{
    stop();
    }
  }

  void movementIR() {                        // takes action based on IR code received
  switch (IRresults.command) {
    case 0x45:
      //Serial.println("POWER");
      CurrentRemoteMode = PLAYSTATION;
      break;
    case 0x46:
      //Serial.println("VOL+");
      spinRight();// press VOL+ so it will spin right
      break;
    case 0x47:
      //Serial.println("FUNC");
      servomovement_open();
      break;
    case 0x44:
      //Serial.println("LEFT");
      turnLeft();
      break;
    case 0x40:
      servomovement_open();
      //Serial.println("PLAY");
      break;
    case 0x43:
      //Serial.println("RIGHT");
      turnRight();
      break;
    case 0x9:
      //Serial.println("UP");
      forward();
      break;
    case 0x15:
      //Serial.println("VOL-");
      spinLeft();
      break;
    case 0x7:
     // Serial.println("DOWN");
      reverse();
      break;
    case 0x16:
      //Serial.println("0");
      break;
    case 0x19:
     // Serial.println("EQ");
      break;
    case 0xD:
     // Serial.println("ST");
     stop();
      break;
    case 0xC:
     // Serial.println("1");
      servomovement_close();
      break;
    case 0x18:
      //Serial.println("2");
      break;
    case 0x5E:
      //Serial.println("3");
      break;
    case 0x8:
      //Serial.println("4");
      break;
    case 0x1C:
      //Serial.println("5");
      break;
    case 0x5A:
     // Serial.println("6");
      break;
    case 0x42:
      //Serial.println("7");
      break;
    case 0x52:
      //Serial.println("8");
      break;
    case 0x4A:
     // Serial.println("9");
      break;
    default:
     // Serial.println("other button");
      break;
  }
}

void servomovement_open(){ 
    myservo.write(160);              // tell servo to go to position in variable 'pos' 
}

void servomovement_close(){
  myservo.write(45);
}            

