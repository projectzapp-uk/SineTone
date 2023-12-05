 void readEncoder(){
 

int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,0,currentEncoderState);
enc1 = 0;
enc2 = 0;


  for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Volume on Channel A and B 0-10 = 0-100% = 0-1.0 MixGain
        if (index == 0){
          //Channel A
           

          }
        if (index ==1){
          //Channe B

          }
         }
      }
    }
  //Exist Buttons and Zero Mixer on Audio and reset to Waveform. 
    BUTTONState = digitalRead(1);
      if (BUTTONState == LOW){
       
    
            }
    BUTTONState = digitalRead(4);
      if (BUTTONState == LOW){
        
    
            }



 }