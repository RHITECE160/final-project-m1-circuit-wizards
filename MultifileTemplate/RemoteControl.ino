/*
  RemoteControl.ino - Arduino Sketch for Remote Control of the RLSK robot
  
  Description:
  This sketch provides functions for controlling an RLSK robot using a
  playstation controller for input. A few actions are programed for an 
  example. 

  Button map:
  PAD UP button moves both motors forward
  CROSS button stops motors

  Created by: Your Name
  Date: Current Date
  Version: 1.0
*/

void RemoteControl() {
 // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Operate the robot in remote control mode
  if (CurrentRemoteMode == 0) {
    //Serial.println("Running remote control with the Playstation Controller");
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
    //Serial.println("Reverse");
    reverse(); // move L3 down so it will reverse
  } else if (ps2x.Analog(PSS_LY)<60) {
    Serial.println("Forward");
    forward(); // move L3 up so it will forward
  } else if (ps2x.Analog(PSS_RX)>180){
    //Serial.println("Turn Right");
    turnRight();// move R3 to right so it will turn right
  } else if (ps2x.Analog(PSS_RX)<60){
    //Serial.println("Turn Left");
    turnLeft(); // move L3 to left so it will turn left
  } else if (ps2x.Button(PSB_PAD_RIGHT)){
    //Serial.println("Spin Right");
    spinRight(); // press pad right so it will spin right
  } else if (ps2x.Button(PSB_PAD_LEFT)){
    //Serial.println("Spin Left");
    spinLeft(); // press pad left so it will spin left
  } else if (ps2x.Button(PSB_CROSS)){
    CurrentRemoteMode = IR_REMOTE; // press cross so it will change remote mode
  } else if (ps2x.Button(PSB_L3)){
    servomovement_open(); // press L3 so the servo will function
  } else if (ps2x.Button(PSB_R3)){
    servomovement_close(); // press L3 so the servo will function
  } else if (ps2x.Button(PSB_R1)) {
    stop();
    digitalWrite(IR_LED, HIGH);
    delay(1000);
    digitalWrite(IR_LED,LOW);
  } else if (ps2x.Button(PSB_L1)) {
    goldCandles();
  } else if (ps2x.Button(PSB_L2)) {
    lightskull();
  } else {
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
         
