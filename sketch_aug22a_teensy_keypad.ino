int pinNum = 8;
int touchReading[8] = {0,0,0,0,0,0,0,0};
int touchPin[8] = {22,19,18,17,16,15,1,0};
boolean isStarted[8] = {false, false, false, false, false, false, false, false};
int keys[] = {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8};

void setup() {
  //For Debuging
  Serial.begin(9600);
}

void loop() {
  // Touchpin Set Up : 22,19,18,17,16,1,0 (터치핀 셋팅 : 22,19,18,17,16,1,0 순서대로 0~7번째 핀)
  for(int i = 0 ; i < pinNum ; i++){
    touchReading[i] = touchRead(touchPin[i]);
  }
  
  //Touch Sensitivity. Lower Number => More Sensitive(터치민감도. 숫자가 낮을 수록 더 민감하게 작동한다.)
  int vel = 4000; 

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
  delay(5);
}
