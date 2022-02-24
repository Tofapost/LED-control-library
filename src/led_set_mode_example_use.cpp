#include <Arduino.h>
#include "led_set_mode.h"



void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);

}

//outputs pins---------------------------------------------------------
const int led_green_outPin = 5;   //green led is connectd to this Pin
const int led_red_outPin = 6;   //green led is connectd to this Pin

void loop() {
  // put your main code here, to run repeatedly:

//main loop example


  analogWrite(led_green_outPin, led_set_mode_f(led_on));

  analogWrite(led_red_outPin, led_set_mode_f(led_blink));

}
