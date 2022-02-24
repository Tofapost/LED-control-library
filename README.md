This library allows you to set LEDs to perform simple functions like blinking or glowing from your main code with an easy to use function.

It is non-blocking and allows you to simply set the mode of an LED and get back its current PWM state (0-255)

The function is passed: led_mode_t led_mode (variable type "led_mode_t" & the value "led_mode) this tell the function what you are wanting the LED to do.

It returns: led_state, the PWM value for that the LED pin should be set to at that point in time (static if on or off, changing if fade etc).

You can set the LED to the following states

led_off 
led_on 
led_blink 
led_glow 
led_fade_on 
led_fade_off

You can change the LED blink rate, glow rate, and fade on / off in the function code

Enjoy
