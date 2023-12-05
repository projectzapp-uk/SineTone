void mainMenu(){
  encA = ssd1306_menuSelection(&menu);
  ssd1306_clearScreen();
  ssd1306_showMenu( &menu );
  NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
  encoders[0].newSettings(0,5,encA,currentEncoderState);
  encoders[1].newSettings(0,5,encB,currentEncoderState);
  while (menuSelected == 0){
    
    Serial.println(ssd1306_menuSelection(&menu));
    readEncoder();
    // Serial.println("encA ");
    // Serial.println(encA);
    if (encA >ssd1306_menuSelection(&menu) && encA < 6  ){
      ssd1306_menuDown(&menu);
      ssd1306_updateMenu(&menu);
      encA = ssd1306_menuSelection(&menu);
      
      

    }
    if (encA < ssd1306_menuSelection(&menu) ){
      ssd1306_menuUp(&menu);
      ssd1306_updateMenu(&menu);
      encA = ssd1306_menuSelection(&menu);

    }
     BUTTONStateA = digitalRead(1);
          if (BUTTONStateA == LOW){

            menuSelected = encA;
              
               
            }
        //Enter config via encoder push button B
      BUTTONStateB = digitalRead(4);
      if (BUTTONStateB == LOW){
         
          
            
        }
    
    delay(100);




  }
  


}