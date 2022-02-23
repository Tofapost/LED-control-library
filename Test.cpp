  //led function with multiple output options

/*

In my main loop I would like to be able to use something like the following and aplly different modes to any led pin
led pin to be changed = led mode it is set to
led_x = led_off
led_x = led_on
led_x = led_blink
led_x = led_fade
led_x = led_fade_on
led_x = led_fade_off

Data to be passed into the function :
led_mode

Data to come back out of the function :
led_state (the actual state of the output pin, on, off, pwm value)


*/

//main loop example

//outputs pins---------------------------------------------------------
const int led_green_outPin = 5;   //green led is connectd to this Pin
const int led_red_outPin = 6;   //green led is connectd to this Pin


void loop() {

  int led_green_state = led_mode_f (led_on);
  analogWrite(led_green_outPin, led_green_state);

  int led_red_state = led_mode_f (led_blink);
  analogWrite(led_red_outPin, led_red_state);

}

//led modes---------------------------------------------------
typedef enum {  //various modes that the led can be in
  led_off = 0,
  led_on,
  led_blink,
  led_fade,
  led_fade_on,
  led_fade_off,
} led_mode_t;


//led mode function
int led_mode_f(led_mode_t led_mode) { //name of the function and what is being passed in, in this case the led mode
  int led_state;

  // code to determin led state  

  if (led_mode == led_off) {
    led_state = 0;
  }
  return led_state;
  
   if (led_mode == led_on) {
    led_state = 255;
  }
  return led_state;

   if (led_mode == led_blink) {
    led_state = get_blink_state_f();
  }
  return led_state;

}



//blink timer function
unsigned long blink_timer_millis; //last time blink changed on/off state
int blink_interval = 750; // on/off time for indicator blink
int blink_state; //what will be retunred
//
int get_blink_state_f(void) { //name of the function and what is being passed in, in this case nothing (void)

  
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



//fade timer function
unsigned long fade_timer_millis; //last time fade changed on/off state
int fade_state; //what will be retunred
int fade_interval = 750; // on/off time for fade
int fade_steps = 10; // number of steps in the fade
int fade_step_millis = fade_interval / fade_steps; // the time between each step change
int fade_step_brightness = 255 / fade_steps; // The change in brightness at each step
bool fade_up = true; // fade direction up or down
//
int get_fade_state_f(void) { //name of the function and what is being passed in, in this case nothing (void)

  
  if (millis() - fade_timer_millis >= fade_step_millis) {
    // this is checking if the time past is higher than or equil to the step specified
    fade_timer_millis = millis(); // re sets the timers starting value

    if (fade_up == true){
      if (fade_state <= 255) {
      fade_state = fade_state + fade_step_brightness;
    }
    else fade_up = false;
    }

    if (fade_up == false){
      if (fade_state >= 0) {
      fade_state = fade_state - fade_step_brightness;
    }
    else fade_up = true;
    }

  }

return fade_state;
}
