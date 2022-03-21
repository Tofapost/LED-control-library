
// blink timer function
  unsigned long blink_timer_millis;   // last time blink changed on/off state
  unsigned long blink_interval = 750; // on/off time for indicator blink
  int blink_state;                    // what will be retunred
  int get_blink_state_f(){
  // name of the function and what is being passed in, in this case nothing (void)

    if (millis() - blink_timer_millis >= blink_interval)
    {
      // this is checking if the time past is higher than or equil to the interval specified
      blink_timer_millis = millis(); // re sets the timers starting value
      // if the light is off turn it on and vice-versa:
      if (blink_state == 0)
      {
        blink_state = 255;
      }
      else
      {
        blink_state = 0;
      }
    }

    return blink_state;
  }
