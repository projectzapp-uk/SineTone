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


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=524,391
AudioInputI2S            i2s1;           //xy=528,249
AudioEffectEnvelope      envelopeA;      //xy=892,392
AudioMixer4              mixer1;         //xy=913,160
AudioMixer4              mixer2;         //xy=915,258
AudioOutputI2S           lineout;        //xy=1244,392
AudioConnection          patchCord1(waveform1, envelopeA);
AudioConnection          patchCord2(i2s1, 0, mixer1, 0);
AudioConnection          patchCord3(i2s1, 1, mixer2, 0);
AudioConnection          patchCord4(envelopeA, 0, mixer2, 3);
AudioConnection          patchCord5(envelopeA, 0, mixer1, 3);
AudioConnection          patchCord6(mixer1, 0, lineout, 0);
AudioConnection          patchCord7(mixer2, 0, lineout, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=875,484


//Set envelope variables  
int   attackParam;
int   decayParam;
float sustainParam;
int   releaseParam;
const int myInput = AUDIO_INPUT_LINEIN;


extern const int16_t myWaveform[256];
  
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
int BUTTONState2 = 0;
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
      // Serial.print("Encoder: ");
      // Serial.print(index);
      // Serial.println(" Failed to Start. Check pin assignments and available interrupts. Aborting.");
      while (1) {
        yield();
      }
    } else {
      encoders[index].getState(state);
      prevEncoderValue[index] = state.currentValue;
      // Serial.print("Encoder: ");
      // Serial.print(index);
      // Serial.print(" Successfully Started at value = ");
      // Serial.println(state.currentValue);
      
    }
  }
    // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);
  sgtl5000_1.inputSelect(myInput);
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
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8); 
  waveform1.frequency(0);
  waveform1.amplitude(0);
  //Default Sinewave
  waveform1.begin(WAVEFORM_SINE);
  
  
  //Adjust Mixer Set Audio Input to Zero and Tone to full
  mixer1.gain(0, 0);
  mixer1.gain(3, 1.0);
  mixer2.gain(0, 0);
  mixer2.gain(3, 1.0);
  //Set custom 2b wave form
  waveform1.arbitraryWaveform(myWaveform, 172.0);

}

void loop() {
  
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
    case 5:
      menu5();
      break;
      
  }

}










