//void lightskull(){
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
//   if (irRX.decodeIR(&IRresults)) {
//     IRresults.command;
//     delay(100);
//   }
//   IRmsg.protocol = NEC;
//   IRmsg.address = 0xCE;
//   IRmsg.command = IRresults.command;
//   IRmsg.isRepeat = false;
//   Serial.print(IRmsg.address);
//   Serial.print("//");
//   Serial.println(IRmsg.command);
//   sendIR.write(&IRmsg);
//   delay(500);
  
//}

void lightskull(){
  
  IRresults.protocol = NEC;
  IRresults.address = 0xCE;   // address for the Catrina
  IRresults.command = 0xA0;  // place holder for Catrina's command
  IRresults.isRepeat = false;
  Serial.println("Trying to light");

   if (justWritten) {
        justWritten = false;
        Serial.print("Address=0x");
        Serial.print(IRresults.address, HEX);
        Serial.print(" Command=0x");
        Serial.print(IRresults.command, HEX);
        if (IRresults.isRepeat) {
            Serial.print(" - repeat");
        }
        Serial.println();

        // send data specified in IRmsg struct using NEC encoding
        //  size_t IRsender::write(IRData *aIRSendData, uint8_t aNumberOfRepeats = NO_REPEATS)
        //digitalWrite(redLEDpin, HIGH);
        sendIR.write(&IRresults);
        Serial.println("Sending value back to Catrina...");
        //digitalWrite(redLEDpin, LOW);
        delay(1000);

    }

}