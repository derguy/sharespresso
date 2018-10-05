#include "buzzer.h";

#ifdef ESP32
  int channel = 0;
  int resolution = 8;
  int freq = 2000;

  void tone(uint8_t _pin, unsigned int frequency, unsigned long duration) {
    ledcWriteTone(channel, frequency);
  }
  void noTone(uint8_t _pin) {
    ledcWriteTone(channel, 0);
  }
#endif

Buzzer::Buzzer() {
#ifdef ESP32
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(BUZPIN, 0);
#endif
  noTone(BUZPIN);
}

void Buzzer::beep(byte number){
  int duration = 200;
  switch (number) {
  case 1: // positive feedback
    tone(BUZPIN,1500,duration);
    delay(duration);
    break;
  case 2: // negative feedback
    tone(BUZPIN,500,duration);
    delay(duration);
    break;     
  case 3:  // action stopped (e.g. registering) double beep
    tone(BUZPIN,1000,duration);
    delay(duration);
    tone(BUZPIN,1500,duration);
    delay(duration);    
    break; 
  case 4:  // alarm (for whatever)
    for (int a = 0; a < 3; a++){
      for (int i = 2300; i > 600; i-=50){
        tone(BUZPIN,i,20);
        delay(18);
      }     
      for (int i = 600; i < 2300; i+=50){
        tone(BUZPIN,i,20);
        delay(18);
      }
    }  
  }
  noTone(BUZPIN);
}

