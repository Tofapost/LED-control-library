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

void loop() {
{
    int led_green_state = led_mode_f (led_on);
    digitalWrite(led_green_outPin, led_green_state);
  }

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
    led_state = 1;
  }
  return led_state;

   if (led_mode == led_blink) {
    led_state = get_blink_state_f();
  }
  return led_state;

}



//blink timer function
unsigned long blink_timer_millis; //last time flasher changed on/off state
int blink_interval = 750; // on/off time for indicator flasher (1 to 2 Hz is acceptable)
//
int get_blink_state_f(void) { //name of the function and what is being passed in, in this case nothing (void)
  int blink_state; //what will be retunred
  
  if (millis() - blink_timer_millis >= blink_interval) {
    // this is checking if the time past is higher than or equil to the interval specified
    blink_timer_millis = millis(); // re sets the timers starting value
    // if the light is off turn it on and vice-versa:
    if (blink_state == 0) {
      blink_state = 1;
    } else {
      blink_state = 0;
    }
  }

return blink_state;
}