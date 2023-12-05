//Pulse

void menu1(){

  int encAstart = 0;
  int encBstart = 0;
  encA = 0;
  encB = 5;
  //Audio Setup
  waveform1.frequency(encA);
  waveform1.amplitude(0.8);
  envelopeA.noteOn();
  attackParam = 10.5;
  decayParam = 0;
  sustainParam = 1.0;
  releaseParam = 300;
  int delaytime = 1000;
  int16_t currentValue;
  //Update Screen
  updateMenu1();

  //reset start value on encoder
  NewEncoder::EncoderState currentEncoderState;
  encoders[0].newSettings(0,10,0,currentEncoderState);
  encoders[1].newSettings(0,10,5,currentEncoderState);
  

    while (menuSelected == 1){
      //Audio
      envelopeA.delay(0);
      envelopeA.attack(attackParam);    
      envelopeA.hold(0);                
      envelopeA.decay(decayParam);      
      envelopeA.sustain(sustainParam);  
      envelopeA.release(releaseParam);
      unsigned long currentTime = millis();
      if (currentTime - prevTime >= delaytime) {
        envelopeA.noteOn();
        while (!envelopeA.isSustain()){
          //Do nothing
      } 
      
      envelopeA.noteOff();
      prevTime = currentTime;  
      }  

      readEncoder();
      
        if (encAstart != encA || encBstart != encB){
          updateMenu1();
          encAstart = encA;
          waveform1.frequency(map(encA,0,10,0,1000));
          encBstart = encB;
          delaytime = map(encB,0,10,200,2000);
        }
      //Check for both Button presses
      BUTTONStateA = digitalRead(1);
      BUTTONStateB = digitalRead(4);
        if (BUTTONStateA == LOW ||BUTTONStateB == LOW ){
          menuSelected = 0;
          envelopeA.noteOff();
          delay(2000);
          }
    }
}





