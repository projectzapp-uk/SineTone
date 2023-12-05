#include "NewEncoder.h"
#include <Audio.h>
#include "ssd1306.h"
#include "nano_gfx.h"

int menuSelected = 0;
int encA = 0;
int encB = 0;
int waveForm = 0;
String wavetext = "Sine";

//Encoder setup. Range 0-10
NewEncoder encoders[] = {
  { 3, 2, 0, 20, 0, FULL_PULSE },
  
  { 6, 5, 0, 20, 0, FULL_PULSE }
  
};
const uint8_t numEncoders = sizeof(encoders) / sizeof(encoders[0]);
int16_t prevEncoderValue[numEncoders];
int BUTTONStateA = 0; 
int BUTTONStateB = 0;
//Audio Settings
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
bool ToneOn = false;
bool contious = false;
const int myInput = AUDIO_INPUT_LINEIN;
extern const int16_t myWaveform[256];
unsigned long prevTime = 0;




//Menu Setup
SAppMenu menu;
const char *menuItems[] =
{
    "   Awsome Tones   ",
    "Pulse",
    "WaterFall",
    "Continuous",
    "Audio Input",
    "Config"
};
SAppMenu waveformmenu;
const char *waveFormMenuItems[] =
{
    "   Wave Forms   ",
    "Sine",
    "Square",
    "Tringle",
    "Saw Tooth",
    "2b Custom"
    
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    /* Select the font to use with menu and all font functions */
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_128x64_i2c_init();
    ssd1306_clearScreen();
    ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
    ssd1306_showMenu( &menu );

  //Setup Audio
  AudioMemory(10);
  sgtl5000_1.inputSelect(myInput);
  attackParam = 1800;
  decayParam = 400;
  sustainParam = 1.0;
  releaseParam = 2000;
  envelopeA.delay(0);
  envelopeA.attack(attackParam);    
  envelopeA.hold(0);                
  envelopeA.decay(decayParam);      
  envelopeA.sustain(sustainParam);  // gain level from 0 to 1.0
  envelopeA.release(releaseParam);  
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
  //Set custom 2b wave formnet
  waveform1.arbitraryWaveform(myWaveform, 172.0);
 

  
  NewEncoder::EncoderState state;
  for (uint8_t index = 0; index < numEncoders; index++) {
    if (!encoders[index].begin()) {

      while (1) {
        yield();
      }
    } else {
      encoders[index].getState(state);

      
    }
  }

}

 


void loop() {
 

 switch (menuSelected){
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
