// WaterFall Patturn
void menu1(){

int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,5,currentEncoderState);
delay(1000);
//Reset Veriables, enc1 = freq, enc2 = Delay
enc1 = 0;
enc2 = 50;
waveform1.frequency(enc1);
waveform1.amplitude(0.8);
int delaytime = map(enc2,0,100,0,4000);
attackParam = map(enc2,0,100,0,3600);
decayParam = map(enc2,0,100,0,800);
releaseParam = map(enc2,0,100,0,4000);
envelopeA.attack(attackParam);    // max 11880 mS
envelopeA.decay(decayParam);      // max 11880 mS
envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
envelopeA.release(releaseParam);  // max 11880 mS

  while (entered == 1){
  //Set time loop. defult is 50% at 2000ms

  //waferfall. 
  unsigned long currentTime = millis();  // Get the current time in milliseconds.
  //Check if 0.5 seconds have passed since the last change.
  if (currentTime - prevTime >= delaytime) {
    if (ToneOn){
    envelopeA.noteOff();
    ToneOn = false;
    } else {
      envelopeA.noteOn();
      ToneOn = true;
    }
    prevTime = currentTime;  // Update the previous time to the current time.
    }


  displaymenu(1, selected);
  
  //encoders[0].newSettings(0,10,0,currentEncoderState);
  for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {

      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Speed
        if (index == 0){

           int mappedVal = map(currentValue,0,20,0,2000);
           enc1 = mappedVal;
           waveform1.frequency(mappedVal);


          }
        if (index ==1){
          Serial.println("Menu 1: AMP");
          float mappedVal = map(currentValue,0,10,0,100);
          // Serial.print("curent");
          // Serial.println(currentValue);
          // Serial.println(mappedVal);
          enc2 = mappedVal;
          delaytime = map(enc2,0,100,0,4000);
          attackParam = map(enc2,0,100,0,3600);
          decayParam = map(enc2,0,100,0,800);
          releaseParam = map(enc2,0,100,0,4000);
          envelopeA.attack(attackParam);    // max 11880 mS
          envelopeA.decay(decayParam);      // max 11880 mS
          envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
          envelopeA.release(releaseParam);  // max 11880 mS

          }
         }
      }
    }
          BUTTONState = digitalRead(1);
          if (BUTTONState == LOW){
              entered = 0;
              menuId = 0;
              envelopeA.noteOff();
              delay(1000);
            }
  }
}
