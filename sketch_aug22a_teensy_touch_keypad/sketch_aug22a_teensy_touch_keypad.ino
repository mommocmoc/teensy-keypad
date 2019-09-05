//BUTTON
#include <RBD_Button.h>

//WaveTable
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "c4_samples.h"
//#include "Flute_100kbyte_samples.h"
// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable1;     //xy=150,341
AudioMixer4              mixer1;         //xy=369,338
AudioOutputAnalog        dac1;           //xy=547,339
AudioConnection          patchCord1(wavetable1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, dac1);
// GUItool: end automatically generated code

//Freq from C4 to C5
float freq[] = {523.25, 587.32, 659.25, 698.45, 783.99, 880.0, 987.76, 1046.5};
float vol = 0.7;


//mode indicator : 
// led on = synth mode 
// led off : keypad mode
bool ledState = false;
RBD::Button button(0);
int led = 13;

int pinNum = 8;
int touchReading[8] = {0,0,0,0,0,0,0,0};
int touchPin[8] = {23,22,19,18,17,16,15,1};
boolean isStarted[8] = {false, false, false, false, false, false, false, false};
int keys[] = {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8};

void setup() {
  //For Debuging
  //Serial.begin(9600);
  pinMode(led, OUTPUT);
  AudioMemory(20);
  wavetable1.setInstrument(c4);
//  wavetable1.setInstrument(Flute_100kbyte);
  wavetable1.amplitude(1);
  mixer1.gain(0,vol);
}

void loop() {
  // Touchpin Set Up : 22,19,18,17,16,1,0 (터치핀 셋팅 : 22,19,18,17,16,1,0 순서대로 0~7번째 핀)
  for(int i = 0 ; i < pinNum ; i++){
    touchReading[i] = touchRead(touchPin[i]);
  }
  
  //Touch Sensitivity. Lower Number => More Sensitive(터치민감도. 숫자가 낮을 수록 더 민감하게 작동한다.)
  int vel = 4000; 

  if(button.isReleased()){
    ledState = false;
    wavetable1.stop();
  for(int i = 0 ; i < pinNum ; i++){
    if(touchReading[i] > vel){
      
      isStarted[i] = !isStarted[i];
      delay(5);

      if(isStarted[i])
      {
        Keyboard.press(keys[i]);
//       checking  which pin is pressed
//        Serial.print("touch ");
//        Serial.print(i);
//        Serial.println(" pin!");
      }
      }else
      {
        Keyboard.release(keys[i]);
        isStarted[i] = !isStarted[i];
      }
  }
  }else if(button.isPressed()){
    ledState = true;
    //Synth Part Here
    for(int i = 0 ; i < pinNum ; i++){
    if(touchReading[i] > vel){
      
      isStarted[i] = !isStarted[i];
      delay(5);

      if(isStarted[i])
      {
        //play wave table
        wavetable1.playFrequency(freq[i]);
        wavetable1.amplitude(vol);
        delay(300);
        wavetable1.stop();
      }
      }else
      {
        //stop wave table
        isStarted[i] = !isStarted[i];
      }
    } 
  }
  wavetable1.amplitude(vol);
  //wavetable1.setFrequency(freq[0]);
  digitalWrite(led, ledState);
  delay(5);
}
