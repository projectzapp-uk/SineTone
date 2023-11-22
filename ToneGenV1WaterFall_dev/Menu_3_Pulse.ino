//Pulse Menu
void menu3(){


delay(2000);
enc1 = 0;
enc2 = 50;
waveform1.frequency(enc1);
waveform1.amplitude(0.8);
envelopeA.noteOn();
attackParam = 10.5;
decayParam = 0;
sustainParam = 1.0;
releaseParam = 300;
int delaytime = 1000;
int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,5,currentEncoderState);

 //If main menu stay there until somthing is selected
  while (entered == 3){
  envelopeA.delay(0);
  envelopeA.attack(attackParam);    // max 11880 mS
  envelopeA.hold(0);                // max 11880 mS
  envelopeA.decay(decayParam);      // max 11880 mS
  envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
  envelopeA.release(releaseParam);  // max 11880 mS

    //waferfall. 
  unsigned long currentTime = millis();  // Get the current time in milliseconds.
  //Check if 0.5 seconds have passed since the last change.
  if (currentTime - prevTime >= delaytime) {
     
    envelopeA.noteOn();
     while (!envelopeA.isSustain()){
       
     } 
     envelopeA.noteOff();
   
    prevTime = currentTime;  // Update the previous time to the current time.
    }
  
  //We are in main Menu, use encoder A to select the submenu
  displaymenu(3, selected);
  


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
           Serial.println(mappedVal);


          }
          if (index ==1){
            enc2 = map(currentValue,0,10,0,100);
            delaytime = map(enc2,0,100,200,2000);

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
