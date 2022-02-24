#include "led_set_mode.h"

/* This function is design to take care of LED handling so that you can manage LED's in a simple way in your the main loop.
    *It is non-blocking and allows you to simply set the mode of an LED and get back its current PWM state (0-255) 
 * 
 * It takes in a led_mode_t and returns the PWM value to be used for your analogWrite on an LED pin.
 * 
 * It is passed: led_mode_t led_mode, the mode you would like the LED to be in.
 * 
 * It returns: led_state, the PWM value for the LED.
 */


//led modes---------------------------------------------------
/* these are declared in the .h file

typedef enum {  //various modes that the led can be in
  led_off = 0,
  led_on,
  led_blink,
  led_glow,
  led_fade_on,
  led_fade_off,
} led_mode_t;

*/

//led mode function
int led_state;
int led_set_mode_f(led_mode_t led_mode) { //name of the function and what is being passed in, in this case the led mode

  // code to determin led state  


switch (led_mode) {
  case led_off:
    led_state = 0;
    break;
  case led_on:
    led_state = 255;
    break;
  case led_blink:
    led_state = get_blink_state_f();
    break;
  case led_glow:
    led_state = get_glow_state_f();
    break;
    case led_fade_on:
    led_state = get_fade_on_state_f();
    break;
    case led_fade_off:
    led_state = get_fade_off_state_f();
    break;
}

return led_state;


// other sub-functins needed

//blink timer function
unsigned long blink_timer_millis; //last time blink changed on/off state
int blink_interval = 750; // on/off time for indicator blink
int blink_state; //what will be retunred
int get_blink_state_f(); { //name of the function and what is being passed in, in this case nothing (void)

  
  if (millis() - blink_timer_millis >= blink_interval) {
    // this is checking if the time past is higher than or equil to the interval specified
    blink_timer_millis = millis(); // re sets the timers starting value
    // if the light is off turn it on and vice-versa:
    if (blink_state == 0) {
      blink_state = 255;
    } else {
      blink_state = 0;
    }
  }

return blink_state;
}


//glow timer function
unsigned long glow_timer_millis; //last time glow changed on/off state

int glow_interval = 750; // on/off time for glow
int glow_steps = 10; // number of steps in the glow
int glow_step_millis = glow_interval / glow_steps; // the time between each step change
int glow_step_brightness = 255 / glow_steps; // The change in brightness at each step
bool glow_up = true; // glow direction up or down
int glow_state; //what will be retunred
int get_glow_state_f(); { //name of the function and what is being passed in, in this case nothing (void)

  
  if (millis() - glow_timer_millis >= glow_step_millis) {
    // this is checking if the time past is higher than or equil to the step specified
    glow_timer_millis = millis(); // re sets the timers starting value

    if (glow_up == true){
      if (glow_state <= 255) {
      glow_state = glow_state + glow_step_brightness;
    }
    else glow_up = false;
    }

    if (glow_up == false){
      if (glow_state >= 0) {
      glow_state = glow_state - glow_step_brightness;
    }
    else glow_up = true;
    }

  }

return glow_state;
}

//fade functions


int fade_interval = 750; // on/off time for fade
int fade_steps = 10; // number of steps in the fade
int fade_step_millis = fade_interval / fade_steps; // the time between each step change
int fade_step_brightness = 255 / fade_steps; // The change in brightness at each step

unsigned long fade_on_timer_millis; //last time fade_on changed on/off state
int fade_on_state; //what will be retunred
int get_fade_on_state_f(); { //name of the function and what is being passed in, in this case nothing (void)
  
  if (millis() - fade_on_timer_millis >= fade_step_millis) {
    // this is checking if the time past is higher than or equil to the step specified
    fade_on_timer_millis = millis(); // re sets the timers starting value
   
    if (fade_on_state <= 255) {
      fade_on_state = fade_on_state + fade_step_brightness;
    }
    else fade_on_state = 255;
    }
      return fade_on_state;
  }

unsigned long fade_off_timer_millis; //last time fade_on changed on/off state
int fade_off_state; //what will be retunred
int get_fade_off_state_f(); { //name of the function and what is being passed in, in this case nothing (void)

  
  if (millis() - fade_off_timer_millis >= fade_step_millis) {
    // this is checking if the time past is higher than or equil to the step specified
    fade_off_timer_millis = millis(); // re sets the timers starting value
   
    if (fade_off_state >= 0) {
      fade_off_state = fade_off_state + fade_step_brightness;
    }
    else fade_off_state = 0;
    }
      return fade_off_state;
  }


}