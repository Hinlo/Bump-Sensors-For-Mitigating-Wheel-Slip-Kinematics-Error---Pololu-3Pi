# define LED_PIN 13  // Pin to activate the orange LED
# define BUZZER_PIN 6 // Pin to activate the buzzer
// Define our states 
# define STATE_INITIAL 0
# define STATE_JOIN_LINE 1
# define STATE_ON_LINE 2        
# define STATE_LOST_LINE 3
# define STATE_RETURN_TO_START 4 
# define STATE_HOME 5     

// Our FSM and Kinematics classes call the remaining classes so don't need to be called again here.
# include "fsm.h"
FSM_c fsm;

// boolean returned by update function, have you reached desired distance yet?
bool reached_desired_distance = false;

void setup() {
  // put your setup code here, to run once
  // Start Serial, send debug text
  Serial.begin(9600);
  delay(2000);
  Serial.println("***RESET***");

  // Set LED and buzzer pin as an output
  pinMode( LED_PIN, OUTPUT );
  pinMode(BUZZER_PIN, OUTPUT);



  // initialise encoders before motors.
  setupEncoder0(); 
  setupEncoder1();

  // Initialise motor GPIO
  motors.initialise();



  // pid set up
  // setup k_proportional, k_integral , k_differential - these are the system gains used to manipulate the error signal e_line.
  speed_pid_left.initialise(100, 0.5, -100);
  speed_pid_right.initialise(100, 0.5, -100);

  // reset PID before you use it.
  speed_pid_left.reset();
  speed_pid_right.reset();
}

void loop(){ 
  
  // Only continue to update state while you haven't reached desired distance.
  if (reached_desired_distance == false){
  reached_desired_distance = fsm.update();
  }

}






