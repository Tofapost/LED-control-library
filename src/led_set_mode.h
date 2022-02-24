#include <Arduino.h>
#ifndef led_set_mode
#define led_set_mode


//led modes---------------------------------------------------
typedef enum {  //various modes that the led can be in
  led_off = 0,
  led_on,
  led_blink,
  led_glow,
  led_fade_on,
  led_fade_off,
} led_mode_t;


int led_set_mode_f(led_mode_t led_mode);
int get_blink_state_f();
int get_glow_state_f();
int get_fade_on_state_f();
int get_fade_off_state_f();

#endif