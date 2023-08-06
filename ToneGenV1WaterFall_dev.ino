#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#define SSD1306_NO_SPLASH       
#include <Adafruit_SSD1306.h>  
#include "NewEncoder.h" 






// Audio Shiled Setup
AudioSynthWaveformSine   sine1;          //xy=519,342
AudioEffectEnvelope      envelopeA;      //xy=683,396
AudioOutputI2S           lineout;           //xy=867,333
AudioConnection          patchCord1(sine1, envelopeA);
AudioConnection          patchCord2(envelopeA, 0, lineout, 1);
AudioConnection          patchCord3(envelopeA, 0, lineout, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=666,488

//Set envelope variables  
int   attackParam;
int   decayParam;
float sustainParam;
int   releaseParam;
//Set Freq & Amplitude Variables
int freq1 = 0;
int freq2 = 0;
int amplitude = 0.8;      
// Variable to store the previous time value.
unsigned long prevTime = 0;   
// Variable to store bool tone on or off 
bool ToneOn = false;
bool contious = false;
//Encoder setup, two encoders
NewEncoder encoders[] = {
  { 3, 2, 0, 10, 0, FULL_PULSE },
  
  { 5, 6, 0, 10, 0, FULL_PULSE }
  
};
const uint8_t numEncoders = sizeof(encoders) / sizeof(encoders[0]);
int16_t prevEncoderValue[numEncoders];
int BUTTONState = 0; 

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
  
  //Set up Inital Audio settings
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  attackParam = 1800;
  decayParam = 400;
  sustainParam = 1.0;
  releaseParam = 2000;
  sine1.frequency(0);
  sine1.amplitude(0.8);
  envelopeA.delay(0);
  envelopeA.attack(attackParam);    // max 11880 mS
  envelopeA.hold(0);                // max 11880 mS
  envelopeA.decay(decayParam);      // max 11880 mS
  envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
  envelopeA.release(releaseParam);  // max 11880 mS
  AudioInterrupts();
 
  // Display Setup with title
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer and display the title
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Tone Generator");
  display.display();
  delay(2000);
  
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

 


}

void loop() {
 


    //Check for button pressed
    
  

    BUTTONState = digitalRead(1);
    while(BUTTONState == LOW){
      if (contious == false){
        envelopeA.noteOn();
        contious = true;
      }
      BUTTONState = digitalRead(1);
    }

 
     unsigned long currentTime = millis();  // Get the current time in milliseconds.
    //Check if 0.5 seconds have passed since the last change.
    if (currentTime - prevTime >= 2000) {
      if (ToneOn){
      envelopeA.noteOff();
      ToneOn = false;
      } else {
        envelopeA.noteOn();
        ToneOn = true;
      }
      prevTime = currentTime;  // Update the previous time to the current time.
      }

    
 
  //Get Encoder values and update Frequency of tone 
  int16_t currentValue;
  NewEncoder::EncoderState currentEncoderState;
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
           Serial.print("freq1: ");
           Serial.println(freq1);
           freq1 = currentValue;
           updatescreen(map(freq1,0,10,0,2000),  map(freq2,0,10,0,2000));
           changefreq(map(freq1,0,10,0,2000));

        }
        //Set freq2, could use an else here
        if (index == 1){
          Serial.println("freq2");
          freq2 = currentValue;
          updatescreen(map(freq1,0,10,0,2000), map(freq2,0,10,0,2000));

        }
        
        prevEncoderValue[index] = currentValue;
      } else {
        switch (currentEncoderState.currentClick) {
          case NewEncoder::UpClick:
            Serial.println("at upper limit.");
            break;

          case NewEncoder::DownClick:
            Serial.println("at lower limit.");
            break;

          default:
            break;
        }
      }
    }
  }
  
  





}


//Change Audio Frequency 
void changefreq(int fz){

  sine1.frequency(fz);

}

//Update the OLED screen
void updatescreen(int freqA, int freqB){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("frequency A: ");
  display.println(freqA, 1);
  display.print("frequency B: ");
  display.println(freqB, 1);
  display.display();
  delay(1000);


}