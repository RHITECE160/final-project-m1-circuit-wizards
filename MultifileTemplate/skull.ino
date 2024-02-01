void lightskull(){
  // if (irRX.initIRReceiver()) {
  //   Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_RCV_PIN)));
  // } else {
  //   Serial.println("Initialization of IR receiver failed!");
  //   while (1) { ; }
  // }
  // if (sendIR.initIRSender()) {
  //   Serial.println(F("Ready to transmit NEC IR signals on pin " STR(IR_TRX_PIN)));
  // } else {
  //   Serial.println("Initialization of IR transmitter failed!");
  //   while (1) { ; }
  // }
  if (irRX.decodeIR(&IRresults)) {
    IRresults.command;
    delay(100);
  }
  IRmsg.protocol = NEC;
  IRmsg.address = 0xCE;
  IRmsg.command = IRresults.command;
  IRmsg.isRepeat = false;
  Serial.print(IRmsg.address);
  Serial.print("//");
  Serial.println(IRmsg.command);
  sendIR.write(&IRmsg);
  delay(500);
  
}