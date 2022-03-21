
#include <led_set_mode.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
}

// outputs pins---------------------------------------------------------
const int led_green_outPin = 13; // green led is connectd to this Pin
const int led_red_outPin = 10; // green led is connectd to this Pin


void loop()
{
  // main loop example to run repeatedly:
  analogWrite(led_green_outPin, led_set_mode_f(led_blink));
  analogWrite(led_red_outPin, led_set_mode_f(led_glow));
}
