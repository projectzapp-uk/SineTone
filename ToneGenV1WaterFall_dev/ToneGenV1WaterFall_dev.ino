#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#define SSD1306_NO_SPLASH       
#include <Adafruit_SSD1306.h>  
#include "NewEncoder.h"

//Menu Setup
int selected = 0;
int entered = 0;
int menuId = 0;


//Audio Settings
int enc1 = 0;
int enc2 = 0.8; 


// Audio Shiled Setup
AudioSynthWaveform       waveform1;          //xy=519,342
AudioEffectEnvelope      envelopeA;      //xy=683,396
AudioOutputI2S           lineout;           //xy=867,333
AudioConnection          patchCord1(waveform1, envelopeA);
AudioConnection          patchCord2(envelopeA, 0, lineout, 1);
AudioConnection          patchCord3(envelopeA, 0, lineout, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=666,488





int current_waveform=0;


//Set envelope variables  
int   attackParam;
int   decayParam;
float sustainParam;
int   releaseParam;
  
// Variable to store bool tone on or off 
bool ToneOn = false;
bool contious = false;
 

//Encoder setup. Range 0-10
NewEncoder encoders[] = {
  { 2, 3, 0, 20, 0, FULL_PULSE },
  
  { 6, 5, 0, 20, 0, FULL_PULSE }
  
};
const uint8_t numEncoders = sizeof(encoders) / sizeof(encoders[0]);
int16_t prevEncoderValue[numEncoders];
int BUTTONState = 0; 
unsigned long prevTime = 0;  

//OLED Screen setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16



void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(1000); // Pause for 2 seconds

     //Setup Encoders
  NewEncoder::EncoderState state;
  for (uint8_t index = 0; index < numEncoders; index++) {
    if (!encoders[index].begin()) {
      Serial.print("Encoder: ");
      Serial.print(index);
      Serial.println(" Failed to Start. Check pin assignments and available interrupts. Aborting.");
      while (1) {
        yield();
      }
    } else {
      encoders[index].getState(state);
      prevEncoderValue[index] = state.currentValue;
      Serial.print("Encoder: ");
      Serial.print(index);
      Serial.print(" Successfully Started at value = ");
      Serial.println(state.currentValue);
      
    }
  }
    // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);
  attackParam = 1800;
  decayParam = 400;
  sustainParam = 1.0;
  releaseParam = 2000;
  envelopeA.delay(0);
  envelopeA.attack(attackParam);    // max 11880 mS
  envelopeA.hold(0);                // max 11880 mS
  envelopeA.decay(decayParam);      // max 11880 mS
  envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
  envelopeA.release(releaseParam);  // max 11880 mS
  AudioInterrupts();
  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8); // caution: very loud - use oscilloscope only!
  // configure both waveforms for 440 Hz and maximum amplitude
  waveform1.frequency(0);
  waveform1.amplitude(0);
  
  
  
  


}

void loop() {
  // put your main code here, to run repeatedly:
  switch (menuId){
    case 0:
      mainMenu();
      break;
    case 1:
      menu1();
      break;
    case 2:
      menu2();
      break;
    case 3:
      menu3();
      break;
    case 4:
      menu4();
      break;
      
  }

}

void mainMenu(){
 Serial.println("We are in Main Menu");
 displaymenu(entered, selected);
 //If main menu stay there until somthing is selected
  int16_t currentValue;
  NewEncoder::EncoderState currentEncoderState;
  //reset start value on encoder
  encoders[0].newSettings(0,10,0,currentEncoderState);
  encoders[1].newSettings(0,10,0,currentEncoderState);
  while (entered == 0){
  //We are in main Menu, use encoder A to select the submenu
    for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      Serial.print("Encoder ");
      Serial.print(index);
      Serial.print(": ");
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Speed
        if (index == 0){
           Serial.println("We are in Main Menu, entered is set to 1");
           Serial.println(currentValue);
           menuId = currentValue;
           displaymenu(entered, currentValue);
          }
        }
      }
   }
          BUTTONState = digitalRead(1);
          if (BUTTONState == LOW){
              entered = menuId;
              Serial.println("Entered Menu Value");
              Serial.println(menuId);
              envelopeA.noteOff();
              
               
            }
  }
}

// WaterFall Patturn
void menu1(){
Serial.println("Main One");
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
      Serial.print("Encoder ");
      Serial.print(index);
      Serial.print(": ");
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Speed
        if (index == 0){
           Serial.println("Menu 1: Freq");
           Serial.println(currentValue);
           menuId = currentValue;
           int mappedVal = map(currentValue,0,20,0,2000);
           enc1 = mappedVal;
           waveform1.frequency(mappedVal);
           
           Serial.println(mappedVal);

          }
        if (index ==1){
          Serial.println("Menu 1: AMP");
          float mappedVal = map(currentValue,0,10,0,100);
          Serial.print("curent");
          Serial.println(currentValue);
          Serial.println(mappedVal);
          enc2 = mappedVal;
          Serial.println(enc2);
          delaytime = map(enc2,0,100,0,4000);
          attackParam = map(enc2,0,100,0,3600);
          decayParam = map(enc2,0,100,0,800);
          releaseParam = map(enc2,0,100,0,4000);
          envelopeA.attack(attackParam);    // max 11880 mS
          envelopeA.decay(decayParam);      // max 11880 mS
          envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
          envelopeA.release(releaseParam);  // max 11880 mS

          Serial.print("attack : ");
          Serial.println(attackParam);
          Serial.print("decayParam : ");
          Serial.println(decayParam);
          Serial.print("releaseParam : ");
          Serial.println(releaseParam);
          Serial.print("delaytime : ");
          Serial.print(delaytime);
          }
         }
      }
    }
          BUTTONState = digitalRead(1);
          if (BUTTONState == LOW){
              entered = 0;
              menuId = 0;
              envelopeA.noteOff();
              Serial.println("Entered Menu Value");
              Serial.println(menuId);
              delay(1000);
            }
  }
}



//Menu two Continous.  Diffrent wave form options
void menu2(){
Serial.println("Menu 2");
int16_t currentValue;
NewEncoder::EncoderState currentEncoderState;
//reset start value on encoder
encoders[0].newSettings(0,10,0,currentEncoderState);
encoders[1].newSettings(0,10,0,currentEncoderState);
enc1 = 0;
enc2 = 0;

delay(1000);
 //Audio
Serial.println("Update Audio values: ");
Serial.print(enc1);
Serial.print("  ");
Serial.print(enc2);
waveform1.frequency(enc1);
waveform1.amplitude(0.8);

envelopeA.noteOn();

 while (entered == 2){
  displaymenu(2, selected);

  for (uint8_t index = 0; index < numEncoders; index++) {
    if (encoders[index].getState(currentEncoderState)) {
      Serial.print("Encoder ");
      Serial.print(index);
      Serial.print(": ");
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Speed
        if (index == 0){
           int mappedVal = map(currentValue,0,20,0,2000);
           enc1 = mappedVal;
           waveform1.frequency(enc1);
          }
          //Waveform types
           if (index == 1){
             Serial.println(currentValue);
             enc2 = currentValue;
             if (enc2 == 1){
               waveform1.begin(WAVEFORM_SQUARE);
               
               Serial.println("Square");
             } else if (enc2 == 2){
               waveform1.begin(WAVEFORM_SAWTOOTH);
               Serial.println("Sawtooth");
             } else if (enc2 == 3){
               waveform1.begin(WAVEFORM_TRIANGLE);
               Serial.println("Triangle");
             } else {
               waveform1.begin(WAVEFORM_SINE);
               Serial.println("SINE");
             }
            }
        
        }
      }

    }
          BUTTONState = digitalRead(1);
          if (BUTTONState == LOW){
              entered = 0;
              menuId = 0;
              Serial.println("Entered Menu Value");
              
              Serial.println(menuId);
              delay(1000);
              envelopeA.noteOff();
                        
            }

  }


}


void menu3(){

Serial.println("Main One");
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
      Serial.print("Encoder ");
      Serial.print(index);
      Serial.print(": ");
      currentValue = currentEncoderState.currentValue;
      if (currentValue != prevEncoderValue[index]) {
        Serial.println(currentValue);
        //Set Speed
        if (index == 0){
           Serial.println("Menu 1: Freq");
           Serial.println(currentValue);
           menuId = currentValue;
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
              Serial.println("Entered Menu Value");
              Serial.println(menuId);
              delay(1000);
              envelopeA.noteOff();
                        
            }

  }


}


void menu4(){

Serial.println("Main One");
delay(2000);

waveform1.frequency(enc1);
waveform1.amplitude(0.8);
envelopeA.noteOn();



 //If main menu stay there until somthing is selected
  while (entered == 4){
  //We are in main Menu, use encoder A to select the submenu
  displaymenu(4, selected);
  
    BUTTONState = digitalRead(1);
      if (BUTTONState == LOW){
        entered = 0;
        menuId = 0;
        Serial.println("Entered Menu Value");
        Serial.println(menuId);
        delay(1000);
        
                        
            }

  }


}
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
    display.setCursor(20, 0);
   
    
    for (int i = 0; i < 5; i++) {
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
    } else {
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
 
  } 

  display.display();
}

