/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.
  
    Demonstrates the use of Oscil to play a wavetable.
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.

    Edited by Chris Ball 20/09/2017
*/

//#include <ADC.h>  // Teensy 3.1 uncomment this line and install http://github.com/pedvide/ADC
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please

int pot0,pot1,pot2,pot3;
int frequency1,frequency2,distortion,volume;

void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
}


void updateControl(){
  // put changing controls in here
  pot0=mozziAnalogRead(A0);
  pot1=mozziAnalogRead(A1);
  pot2=mozziAnalogRead(A2);
  pot3=mozziAnalogRead(A3);
  frequency1=pot0+50;
  frequency2=pot1+50;
  distortion=pot2;
  volume=map(pot3, 0, 1023, 0, 255);  
  aSin1.setFreq(frequency1);
  aSin2.setFreq(frequency2);
}


int updateAudio(){
  return (volume+distortion)*((aSin1.next()+aSin2.next())>>1)>>8;
}


void loop(){
  audioHook(); // required here
}



