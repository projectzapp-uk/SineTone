void updateMenu1(){
  char buf[12];
  ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    
    ssd1306_printFixed(0,  8, "PULSE", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Cycle: ", STYLE_BOLD);
    ssd1306_printFixed(50, 24, itoa( encA, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(0, 32, "Feel: ", STYLE_BOLD);
    ssd1306_printFixed(50, 32, itoa( encB, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(0, 50, wavetext.c_str(), STYLE_BOLD);
}

void updateMenu2(){
  char buf[12];
  ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    
    ssd1306_printFixed(0,  8, "WATERFALL", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Freq: ", STYLE_BOLD);
    ssd1306_printFixed(70, 24, itoa( encA, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(0, 32, "Amplitude: ", STYLE_BOLD);
    ssd1306_printFixed(70, 32, itoa( encB, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(0, 50, wavetext.c_str(), STYLE_BOLD);
}

//Continuous Tone
void updateMenu3(){
  char buf[12];
  ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    ssd1306_printFixed(0,  8, "Continuous", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Freq: ", STYLE_BOLD);
    ssd1306_printFixed(60, 24, itoa( encA*100, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(90, 24, "Hz ", STYLE_BOLD);
    ssd1306_printFixed(0, 50, wavetext.c_str(), STYLE_BOLD);
}

void updateMenu4(){
  char buf[12];
  ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    
    ssd1306_printFixed(0,  8, "AUDIO INPUT", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Channel A: ", STYLE_BOLD);
    ssd1306_printFixed(60, 24, itoa( encA, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(0, 32, "Channel B: ", STYLE_BOLD);
    ssd1306_printFixed(60, 32, itoa( encB, buf, 10 ), STYLE_BOLD);
    ssd1306_printFixed(0, 50, wavetext.c_str(), STYLE_BOLD);

}




