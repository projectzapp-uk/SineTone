//Audio Inputs Last Menu Item
void menu4(){

delay(2000);
//Set the mixer to set all gains to Zero.
mixer1.gain(0, 0);
mixer1.gain(3, 0);
mixer2.gain(0, 0);
mixer2.gain(3, 0);
int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,0,currentEncoderState);
enc1 = 0;
enc2 = 0;
  while (entered == 4){
  
  displaymenu(4, selected);

  for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Volume on Channel A and B 0-10 = 0-100% = 0-1.0 MixGain
        if (index == 0){
           float mixvolume = currentValue*0.1;
           mixer1.gain(0, mixvolume);
           enc1 = currentValue*10;

          }
        if (index ==1){
          float mixvolume = currentValue*0.1;
          mixer2.gain(0, mixvolume/10);
          enc2 = currentValue*10;

          }
         }
      }
    }
  //Exist Buttons and Zero Mixer on Audio and reset to Waveform. 
    BUTTONState = digitalRead(1);
      if (BUTTONState == LOW){
        entered = 0;
        menuId = 0;
        //Adjust Mixer Set Audio Input to Zero and Tone to full
        mixer1.gain(0, 0);
        mixer1.gain(3, 1.0);
        mixer2.gain(0, 0);
        mixer2.gain(3, 1.0);
        Serial.println("Entered Menu Value");
        Serial.println(menuId);
        delay(1000);
                  
            }

  }


}