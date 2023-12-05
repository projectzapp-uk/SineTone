void readEncoder(){
 
int16_t currentValue;
bool up, down;

for (uint8_t index = 0; index < numEncoders; index++) {
  up = encoders[index].upClick();
  down = encoders[index].downClick();
  if (up || down) {
    currentValue = encoders[index];
      if (currentValue != prevEncoderValue[index]) {
        if (index == 0){
          Serial.println(currentValue);
          prevEncoderValue[index] = currentValue;
          encA = currentValue;
        
        }else {
          Serial.print("Channel B : ");
          Serial.println(currentValue);
          prevEncoderValue[index] = currentValue;
          encB = currentValue;

        }
    

      }
    }
  }
 }