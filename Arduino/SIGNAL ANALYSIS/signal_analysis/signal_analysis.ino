#include <stdlib>
#include <cstdlib>
#include <cstring>

#define SIGNAL_PIN 6;

#define signal_bits 64;
#define sleep_length = 1

int signal[signal_bits]; //signal array
int signalVal;           //reading analog value of the signal
int i = 0;               //tracks position in signal array
const int handshake[16] = {1,0,1,0,0,1,0,1,1,0,1,1,1,0,0,0}; //handshake signal for initializing control
int buffer[16];
int timerStart;

int maxRead;
int b00_thresh;
int b01_thresh;
int b10_thresh;
int b11_thresh;

void setup(){
  pinMode(SIGNAL_PIN, INPUT);
}

void setMax(){
  timerStart = micros();
  maxRead = 0;
  while(micros() - timerStart < 1000000){
    if(analogRead(SIGNAL_PIN) > maxRead){
      maxRead = analogRead;
    }
  }
}
    
void readSignal(int &bit1, int &bit2){
  int timerStart = micros();
  
  signalVal = analogRead(SIGNAL_PIN);
  if(signalVal > b11_thresh){
    bit1 = 1;
    bit2 = 1;
  }
  else if (signalVal > b10_thresh){
    bit1 = 1;
    bit2 = 0;
  }
  
  else if (signalVal > b01_thresh){
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
  
void loop(){
  initialize_control_signal();
  
  read_control();
  
}
