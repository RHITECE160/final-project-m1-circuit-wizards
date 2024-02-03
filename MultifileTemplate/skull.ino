void lightskull(){
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
    sendIR.write(&IRresults);
    Serial.println("Sending value back to Catrina...");
    delay(1000);

  }

}


/*
 * This function is called if a complete command was received, regardless if 
 *  it is a repeat (not impacted by includeRepeats setting).
 *  !!!!!!!!!!!!!!!!!!!!!!
 *  Function called in interrupt context - should be running as short as possible, so if 
 *  you require longer action, save the data (address + command) and handle it in the main loop.
 *  !!!!!!!!!!!!!!!!!!!!!
 */
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
    /*
     * Since we are in an interrupt context and do not want to miss the next interrupts 
     *  of the repeats coming soon, quickly save data and return to main loop
     */
    IRresults.address = aAddress;
    IRresults.command = aCommand;
    IRresults.isRepeat = isRepeat;
    // Let main function know that new data is available
    justWritten = true;
}