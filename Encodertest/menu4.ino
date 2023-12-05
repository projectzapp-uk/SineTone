///Audio Threput


void menu4(){


    
    int encAstart = 0;
    int encBstart = 0;
    encA = 0;
    encB = 0;
    updateMenu4();
    NewEncoder::EncoderState currentEncoderState;
    encoders[0].newSettings(0,10,0,currentEncoderState);
    encoders[1].newSettings(0,10,0,currentEncoderState);
    delay(1000);

    while (menuSelected == 4){

      readEncoder();
      if (encAstart != encA || encBstart != encB){
        updateMenu4();
        encAstart = encA;
        encBstart = encB;

      }



      BUTTONStateA = digitalRead(1);
        if (BUTTONStateA == LOW){

          menuSelected = 0;
          delay(2000);
            
              
          }

    }

   
    

}