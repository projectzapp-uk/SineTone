void mainMenu(){

 displaymenu(entered, selected);
 //If main menu stay there until somthing is selected
  int16_t currentValue;
  NewEncoder::EncoderState currentEncoderState;
  //reset start value on encoder
  encoders[0].newSettings(0,10,0,currentEncoderState);
  encoders[1].newSettings(0,10,0,currentEncoderState);
  while (entered == 0){
  //We are in main Menu, use encoder A to select the submenu
    for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      // Serial.print("Encoder ");
      // Serial.print(index);
      // Serial.print(": ");
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {

        //Set Speed
        if (index == 0){
           menuId = currentValue;
           displaymenu(entered, currentValue);
          }
        }
      }
   }
          BUTTONState = digitalRead(1);
          if (BUTTONState == LOW){
              entered = menuId;
              envelopeA.noteOff();
               
            }
  }
}
