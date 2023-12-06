//Watefall

void menu2(){

    
    int encAstart = 0;
    int encBstart = 0;
    encA = 5;
    encB = 5;
    updateMenu2();
    NewEncoder::EncoderState currentEncoderState;
    encoders[0].newSettings(0,10,5,currentEncoderState);
    encoders[1].newSettings(0,10,5,currentEncoderState);
    //audio Settings
    waveform1.frequency(encA);
    waveform1.amplitude(0.8);
    int delaytime = map(encB,0,10,0,4000);
    attackParam = map(encB,0,10,0,3600);
    decayParam = map(encB,0,10,0,800);
    releaseParam = map(encB,0,10,0,4000);
    envelopeA.attack(attackParam);   
    envelopeA.decay(decayParam);      
    envelopeA.sustain(sustainParam);  
    envelopeA.release(releaseParam);  
    
    delay(100);

    while (menuSelected == 2){

      unsigned long currentTime = millis();
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

      readEncoder();
        if (encAstart != encA || encBstart != encB){
          updateMenu2();
          encAstart = encA;
          //waveform1.frequency(map(encA,0,10,0,1000));
          freqTable(encA);
          encBstart = encB;
          
          delaytime = map(map(encB,0,10,0,100),0,100,0,4000);
          attackParam = map(map(encB,0,10,0,100),0,100,0,3600);
          decayParam = map(map(encB,0,10,0,100),0,100,0,800);
          releaseParam = map(map(encB,0,10,0,100),0,100,0,4000);
          envelopeA.attack(attackParam);    // max 11880 mS
          envelopeA.decay(decayParam);      // max 11880 mS
          envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
          envelopeA.release(releaseParam);  // max 11880 mS

        }



      BUTTONStateA = digitalRead(1);
      BUTTONStateB = digitalRead(4);
        if (BUTTONStateA == LOW ||BUTTONStateB == LOW ){
          envelopeA.noteOff();
          menuSelected = 0;
          delay(2000);
            
              
          }

    }

   
    

}