void lightcandles(){
   if (irRX.decodeIR(&IRresults)) {//If the command is issued by the robot itself, it will not be printed
    Serial1.print("A=0x");
    Serial1.print(IRresults.address, HEX);
    Serial1.print(" C=0x");
    Serial1.print(IRresults.command, HEX);
    Serial1.print(" is repeat: ");
    Serial1.print(IRresults.isRepeat ? "TRUE" : "FALSE");
    Serial1.println();
  }
  //Check the skull value and decide to emit different signals.
  if (skull) {
    //Signal to light up skull
    IRmsg.protocol = NEC;
    IRmsg.address = 0xCE;
    IRmsg.command = IRresults.command;
    IRmsg.isRepeat = false;//Set signal value
    sendIR.write(&IRmsg);//send signal
  } else {
    //Signal to light candles
    IRmsg.protocol = NEC;
    IRmsg.address = 0xEE;
    IRmsg.command = 160;
    IRmsg.isRepeat = false;//Set signal value
    sendIR.write(&IRmsg);//send signal
  }
}