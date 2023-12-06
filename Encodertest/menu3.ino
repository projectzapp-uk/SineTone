//Continious
void menu3(){

    
    int encAstart = 0;
    int encBstart = 0;
    encA = 5;
    encB = 0;
    //Update Screen
    updateMenu3();
    //Reset Encoder
    NewEncoder::EncoderState currentEncoderState;
    encoders[0].newSettings(0,10,5,currentEncoderState);
    encoders[1].newSettings(0,10,0,currentEncoderState);
    delay(1000);
    //Base Audio
    freqTable(encA);
    waveform1.amplitude(0.8);
    envelopeA.noteOn();

    while (menuSelected == 3){

     readEncoder();
      if (encAstart != encA || encBstart != encB){
        updateMenu3();
        encAstart = encA;
        //Set the Frequency to map encoder values 0-10= 0-1K
        //waveform1.frequency(map(encA,0,10,0,1000));
        freqTable(encA);
        encBstart = encB;

      }


      //Encoder switches, go back to main menu for either button press
      BUTTONStateA = digitalRead(1);
      BUTTONStateB = digitalRead(4);
        if (BUTTONStateA == LOW ||BUTTONStateB == LOW ){
          envelopeA.noteOff();
          menuSelected = 0;
          delay(1000);
            
              
          }

    }

   
    

}