//Convert the encoder vlaues to match the Frequency.  These are mapped from a 2b


void freqTable(int a){

  switch (a){
    case 0:
      waveform1.frequency(75);
      break;
    case 1:
      waveform1.frequency(83);
      break;
    case 2:
      waveform1.frequency(93);
      break;
    case 3:
      waveform1.frequency(105);
      break;
    case 4:
      waveform1.frequency(122);
      break;
     case 5:
      waveform1.frequency(144);
      break; 
    case 6:
      waveform1.frequency(176);
      break;
    case 7:
      waveform1.frequency(227);
      break;
    case 8:
      waveform1.frequency(320);
      break;
    case 9:
      waveform1.frequency(541);
      break;
     case 10:
      waveform1.frequency(1500);
      break; 
 }


}