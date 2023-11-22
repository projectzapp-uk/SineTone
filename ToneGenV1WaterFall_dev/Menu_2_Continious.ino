//Menu two Continous.  Diffrent wave form options
void menu2(){
Serial.println("Menu 2");
int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,0,currentEncoderState);
enc1 = 0;
enc2 = 0;

delay(1000);
waveform1.frequency(enc1);
waveform1.amplitude(0.8);

envelopeA.noteOn();

 while (entered == 2){
  displaymenu(2, selected);

  for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        
        //Set Speed
        if (index == 0){
           int mappedVal = map(currentValue,0,20,0,2000);
           enc1 = mappedVal;
           waveform1.frequency(enc1);
          }
          //Waveform types
           if (index == 1){
             
             enc2 = currentValue;

             if (enc2 == 1){
               waveform1.begin(WAVEFORM_SQUARE);
               
               Serial.println("Square");
             } else if (enc2 == 2){
               waveform1.begin(WAVEFORM_SAWTOOTH);
               
             } else if (enc2 == 3){
               waveform1.begin(WAVEFORM_TRIANGLE);
               
             } else {
               waveform1.begin(WAVEFORM_SINE);
               
             }
            }
        
        }
      }

    }
          BUTTONState = digitalRead(1);
          if (BUTTONState == LOW){
              entered = 0;
              menuId = 0;
              delay(1000);
              envelopeA.noteOff();
                        
            }

  }


}
