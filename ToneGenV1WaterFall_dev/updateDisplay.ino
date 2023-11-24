void displaymenu(int entered, int selected ) {


  const char *options[5] = {
    "",
    "WaterFall",
    "Continous",
    "Pulse",
    "Audio Input"
  };

  if (entered == 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
   
    
    for (int i = 1; i < 5; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(options[i]);
      }
    }
  } else if (entered == 1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Watefall"));
    display.setTextSize(1);
    display.print("Frequncy: ");
    display.println(enc1);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.print("Amplitude ");
    display.println(enc2);

   
    
  } else if (entered == 2) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Continious"));
    display.setTextSize(1);
    display.print("Frequncy: ");
    display.println(enc1);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.print("WaveForm: ");
    if (enc2 == 1){
      display.println("Square Wave");

    } else if (enc2 == 2){
      display.println("SawTooth");

    } else if (enc2 ==3){
      display.println("Triangle");
    } else if (enc2== 4){
      display.println("Custom 2b");

    }
    {
      display.println("Sine");
    }
    
  
  }
  else if (entered == 3) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Pulse"));
    display.setTextSize(1);
    display.print("Feel: ");
    display.println(enc1);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.print("Cycle: ");
    display.print(enc2);
  } 
    else if (entered == 4) {
     display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Audio Input"));
    display.setTextSize(1);
    display.print("Channel A: ");
    display.println(enc1);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.print("Channel B ");
    display.println(enc2);
 
  } 
    else if (entered == 5) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("WaveForm Default Conf"));
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.print("WaveForm: ");
    if (enc2 == 1){
      display.println("Square Wave");

    } else if (enc2 == 2){
      display.println("SawTooth");

    } else if (enc2 ==3){
      display.println("Triangle");
    } else if (enc2== 4){
      display.println("Custom 2b");

    }
    else if (enc2== 5){
      display.println("Sine");

    }
 
 

    
    else
    {
      display.println("");
    }
 
  } 

  display.display();
}