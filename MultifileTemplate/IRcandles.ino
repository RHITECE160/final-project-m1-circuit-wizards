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

}

void goldCandles() {
  if (ps2x.Button(PSB_START)){
  IRmsg.protocol = NEC;
  IRmsg.address = 0xEE;
  IRmsg.command = 0xA0;
  IRmsg.isRepeat = false;
  sendIR.write(&IRmsg);
  Serial.print('.');
  delay(1000);
  }
}