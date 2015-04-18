#include <stdlib>
#include <cstdlib>
#include <cstring>

#include "GamepadState.h"

#define SIGNAL_PIN 0
#define b00thresh 0
#define b01thresh 171
#define b10thresh 511
#define b11thresh 846
#define signal_bits 64
#define sleep_length 1
#define LED_PIN 13

int signal[signal_bits]; //signal array
int signalVal;           //reading analog value of the signal
int i = 0;               //tracks position in signal array
const int handshake[16] = {1,0,1,0,0,1,0,1,1,0,1,1,1,0,0,0}; //handshake signal for initializing control
int buffer[16];

int timerStart;



void setup(){
  pinMode(LED_PIN, OUTPUT);
}

void readSignal(int &bit1, int &bit2){
  
  timerStart = micros();
  
  signalVal = analogRead(SIGNAL_PIN);
  if(signalVal > b11thresh){
    bit1 = 1;
    bit2 = 1;
  }
  else if (signalVal > b10thresh){
    bit1 = 1;
    bit2 = 0;
  }
  
  else if (signalVal > b01thresh){
    bit1 = 0;
    bit2 = 1;
  }
  
  else{
    bit1 = 0;
    bit2 = 0;
  }
  
  while(micros() - timerStart < 1250){};
}

void initialize_control_signal(){
  
  while(memcmp(buffer, handshake, 16) != 0){
  //shift buffer array to the left two bits
  for (int k = 0; k < 2; k++){
    for (int j = 0; j < 16; j++){
     buffer[j] = buffer[j + 1];
    }
  }
 
 readSignal(buffer[14], buffer[15]); 
  }
}

void read_control(){
  for (int j = 0; j < signal_bits; j += 2){
    readSignal(signal[j], signal[j+ 1]);
  }
}
  
void loop(){
  initialize_control_signal();
  
  digitalWrite(LED_PIN, HIGH);
  
}
