/* This code is used to drive a 12V automotie IO box which takes user input from switches on handle bars or steering wheel and translates these to high power outputs.
    The inputs are all 20V tolarnt, with an drain to GND trigger on the input pin.
    The outputs will be switched via MOSFEST rated for a maximum of 20V, 10A for all lights, 30A for starter.
    The IO box will also has various safetly feature to prevent damage.
    - Short ciruit protection on all outputs
    - Over current protection on all outputs
    - 20V tolarant inputs
    For expansion, the IO box also has a LIN bus port this will be wired into the MCU vial serial TX/RX
    Curent sensing on all outputs to check for blow bulbs.
    Progamabe input butttons to change from a swithc to a push button fuction.

    LED
*/
// Global variables
int flasher_state;
unsigned long flasher_short_millis;
int flasher_short_interval = 3000;


// Include these functions
int check_button_f(int inPin, int in_type); //returns in_state
int get_flashing_state(void);


//input pins----------------------------------------------------------
const int left_inPin = 2;   //left turn switch is connectd to this Pin
const int right_inPin = 3;  //right turn switch is connectd to this Pin


//outputs pins---------------------------------------------------------
const int left_outPin = 5;   //left turn light is connectd to this Pin
const int right_outPin = 6;  //right turn light is connectd this Pin


//input type---------------------------------------------------
typedef enum {  //various types of inputs, buttons etc
  button_latching = 0,
  button_momentary,
  anolog,
} input_type_t;

input_type_t left_in_type = button_momentary;
input_type_t right_in_type = button_momentary;


//input states---------------------------------------------------
typedef enum {  //various states that an input can be in
  input_off = 0,
  input_on,
  input_short,
  input_long,
  input_value,
} input_state_t;

input_state_t left_in_state = input_off;
input_state_t right_in_state = input_off;
input_state_t in_state = input_off;


//outputs states---------------------------------------------------------
// stores the state of the output pins
typedef enum {          //various states that an output can be in      //
  output_off = 0,       //
  output_on,        // typedef enum (Type define enumeration) creates a new type of variable that has the states listed avalible
  output_flashing_long,  //continues to flash only stoping when button is pressed
  output_flashing_short, //only flashes for a set amount of time eg. 3 seconds
                        //
} output_state_t;       //

output_state_t left_out_state = output_off;
output_state_t right_out_state = output_off;


//_____________________________________________________________________________________
void setup() {  // setup code runs once
  //_____________________________________________________________________________________

  //inputs, setup pins to input---------------------------------------------------------
  pinMode(left_inPin, INPUT_PULLUP);
  pinMode(right_inPin, INPUT_PULLUP);

  //outputs, setup pins to output---------------------------------------------------------
  pinMode(left_outPin, OUTPUT);
  pinMode(right_outPin, OUTPUT);

  //output defualt state at start up
  digitalWrite(left_outPin, LOW);
  digitalWrite(right_outPin, LOW);
}

//_____________________________________________________________________________________
void loop() {
  //_____________________________________________________________________________________

  flasher_state = get_flashing_state_f();

  // ----------------left indicator ----------------
  left_in_state = check_button_short_long_f (left_inPin, left_in_type);  //read HW pin with Debounce //returns in_state

  // Short flash - turn on the indicator for a short period
  if (left_in_state == input_short && left_out_state == output_off) {
        flasher_short_millis = millis();
        left_out_state = output_flashing_short; // this line just updates what state the output is in to determin what change is needed to when a press is detected. 
       digitalWrite(left_outPin, flasher_state);
  }
    
  // turn off indicator if it has been flashing for long enough. 
  if (left_out_state == output_flashing_short && millis() - flasher_short_millis > flasher_short_interval ) {
        left_out_state = output_off;
       digitalWrite(left_outPin, output_off);
  }

  // turn on the indicator perminently with long button press
  if (left_in_state == input_long) {
    left_out_state = output_flashing_long;
    digitalWrite(left_outPin, flasher_state);
  }

  // turn off the indicator with button press
  if (left_in_state == input_short && left_out_state != output_off) {
    left_out_state = output_off;
    digitalWrite(left_outPin, output_off);
  }

  
  // ----------------right indicator ----------------
  right_in_state = check_button_short_long_f (right_inPin, right_in_type);  //read HW pin with Debounce //returns in_state

  // turn on the indicator for a short period
  if (right_in_state == input_short && right_out_state == output_off) {
        flasher_short_millis = millis();
        right_out_state = output_flashing_short; // this line just updates what state the output is in to determin what change is needed to when a press is detected. 
       digitalWrite(right_outPin, flasher_state);
  }

  // turn off indicator if it has been flashing for long enough. 
  if (right_out_state == output_flashing_short && millis() - flasher_short_millis > flasher_short_interval ) {
        right_out_state = output_off;
       digitalWrite(right_outPin, output_off);
  }

  // turn on the indicator perminently with long button press
  if (right_in_state == input_long) {
    right_out_state = output_flashing_long;
    digitalWrite(right_outPin, flasher_state);
  }

  // turn off the indicator with button press
  if (right_in_state == input_short && right_out_state != output_off) {
    right_out_state = output_off;
    digitalWrite(right_outPin, output_off);
  }

}
