//Config Screen

void menu5(){

    
    int encAstart = 0;
    
    
    NewEncoder::EncoderState currentEncoderState;
    encoders[0].newSettings(0,5,0,currentEncoderState);
    encoders[1].newSettings(0,5,0,currentEncoderState);
    delay(1000);
    char buf[12];
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    ssd1306_createMenu( &waveformmenu, waveFormMenuItems, sizeof(waveFormMenuItems) / sizeof(char *) );
    ssd1306_showMenu( &waveformmenu );
    encA = ssd1306_menuSelection(&waveformmenu);

    while (menuSelected == 5){

    readEncoder();
    Serial.println("encA ");
    Serial.println(encA);
    if (encA >ssd1306_menuSelection(&waveformmenu) && encA < 6  ){
      ssd1306_menuDown(&waveformmenu);
      ssd1306_updateMenu(&waveformmenu);
      encA = ssd1306_menuSelection(&waveformmenu);

      

    }
    if (encA < ssd1306_menuSelection(&waveformmenu) ){
      ssd1306_menuUp(&waveformmenu);
      ssd1306_updateMenu(&menu);
      encA = ssd1306_menuSelection(&menu);

    }



      BUTTONStateA = digitalRead(1);
        if (BUTTONStateA == LOW){

          menuSelected = 0;
          
        
          Serial.println("setting config  ");
          Serial.println(ssd1306_menuSelection(&waveformmenu));
          switch (ssd1306_menuSelection(&waveformmenu)) {
            case 1:
              wavetext = "Sine";
              waveform1.begin(WAVEFORM_SINE);
              break;
            case 2:
              wavetext = "Square";
              waveform1.begin(WAVEFORM_SQUARE);
              break;
            case 3:
              wavetext = "Triangle";
              waveform1.begin(WAVEFORM_TRIANGLE);
              break;
            case 4:
              wavetext = "Saw Tooth";
              waveform1.begin(WAVEFORM_SAWTOOTH);
              break;
            case 5:
              wavetext = "2b Custom";
              waveform1.begin(WAVEFORM_ARBITRARY);
              break;

          }
          delay(2000);
            
              
          }

    }

   
    

}

 





