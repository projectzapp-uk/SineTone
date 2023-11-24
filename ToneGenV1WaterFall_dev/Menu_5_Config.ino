//Set defult waveform, Sine is default. 
void menu5(){
Serial.println("Menu 5");
int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,0,currentEncoderState);
enc1 = 0;
enc2 = 0;

delay(1000);
waveform1.frequency(enc1);



 while (entered == 5){
  displaymenu(5, selected);

  for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        
        //Encoder A
        if (index == 0){
           
          }
          //Waveform types Encoder B
           if (index == 1){
             
             enc2 = currentValue;
             Serial.println(enc2);

             if (enc2 == 1){
               waveform1.begin(WAVEFORM_SQUARE);
               
               Serial.println("Square");
             } else if (enc2 == 2){
               waveform1.begin(WAVEFORM_SAWTOOTH);
               
               
             } else if (enc2 == 3){
               waveform1.begin(WAVEFORM_TRIANGLE);
               

             } 
             
               else if (enc2 == 4){
               
               waveform1.begin(WAVEFORM_ARBITRARY);
               
               }
             
             else {
               waveform1.begin(WAVEFORM_SINE);
               
               Serial.println("sine");
               
             }
            }
        
        }
      }

    }
          BUTTONState = digitalRead(4);
          if (BUTTONState == LOW){
              entered = 0;
              menuId = 0;
              delay(1000);
              
                        
            }

  }


}
