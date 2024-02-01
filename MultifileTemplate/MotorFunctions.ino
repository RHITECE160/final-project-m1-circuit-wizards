/*
  MotorFunctions.ino - Arduino Sketch for Motor Control
  
  Description:
  This sketch provides functions for controlling a RLSK robot, allowing the
  motors to move forward and stop.

  Functions:
  1. void moveForward()
     - Activates the motor to move forward.

  2. void reverse()
    - Activates the motor to move backwards

  3. void stopMotor()
     - Stops the motor.
  
  4. void turnLeft()
    - Activates left motor at slow speed and right motor at fast speed, turns left
  
  5. void turnRight()
    - Activates right motor at slow speed and left motor at fast speed, turns right
  
  6. void spinLeft()
    - Activates right motor at slow speed, left motor at slow speed backwards, spins left
  
  7. void spinRight()
    - Activates left motor at slow speed, right motor at slow speed backwards, spins right
  
  8. servomovement_open()
    - Opens claw grip to 20 degrees
  
  9. servomovement_close()
    - Closes claw grip to 120 degrees



  Created by: Ian Morton, Tom Cai
  Date: 1/17/24
  Version: 1.0
*/

/* Moves robot forward: both motors forward same speed */
void forward() {
    enableMotor(BOTH_MOTORS);
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorSpeed(LEFT_MOTOR, 30);
    setMotorSpeed(RIGHT_MOTOR, 30);
}

void reverse() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(BOTH_MOTORS, fastSpeed);
}

/* Stops robot forward: both motors disabled */
void stop() {
    disableMotor(BOTH_MOTORS);
}

void turnLeft() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, fastSpeed);
  setMotorSpeed(LEFT_MOTOR, slowSpeed);
}

void turnRight() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, slowSpeed);
  setMotorSpeed(LEFT_MOTOR, fastSpeed);
}

void spinLeft() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, slowSpeed);
  setMotorSpeed(LEFT_MOTOR, slowSpeed);
}

void spinRight() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(RIGHT_MOTOR, slowSpeed);
  setMotorSpeed(LEFT_MOTOR, slowSpeed);
}

void servomovement_open(){ 
  myservo.write(20);              // tell servo to go to position in variable 'pos' 
}

void servomovement_close(){
  myservo.write(120);
}   
