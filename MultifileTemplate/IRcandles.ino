void candleSetup() {
  delay(500);  // To be able to connect Serial monitor after reset or power up
  Serial.println(F("START " __FILE__ " from " __DATE__));
  /*
     * Must be called to initialize and set up IR transmit pin.
     *  bool IRsender::initIRSender( )
     */
  if (sendIR.initIRSender()) {
    Serial.println(F("Ready to transmit NEC IR signals on pin " STR(IR_TRX_PIN)));
  } else {
    Serial.println("Initialization of IR transmitter failed!");
    while (1) { ; }
  }
  delay(200);
  // enable transmit feedback and specify LED pin number (defaults to LED_BUILTIN)
  enableTXLEDFeedback(GREEN_LED);
  
  IRresults.protocol = NEC;
  IRresults.address = 0xCE;   // address for the Catrina
  IRresults.command = 0xA0;  // place holder for Catrina's command
  IRresults.isRepeat = false;
}

void goldCandles() {
  IRmsg.protocol = NEC;
  IRmsg.address = 0xEE;
  IRmsg.command = 0xA0;
  IRmsg.isRepeat = false;
  sendIR.write(&IRmsg);
  Serial.println("IR signal sent");
}