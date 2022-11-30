# include "Arduino.h"
// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
# ifndef _FSM_H
# define _FSM_H
# define LED_PIN 13 
# define BUZZER_PIN 6

// Define frequency of updates for our linesensors, PID and motors.
# define KINEMATICS_UPDATE  100 // absolute minimum is 8 milliseconds here as that is about the max time the line sensor update function can take.
# define PID_UPDATE         20
# define MOTOR_UPDATE       30

// Classes to include, encoders and motors included within kinematics so don't need to include again explicitely.
# include "kinematics.h"
# include "pid.h"


Kinematics_c kinematics;

// two instances of PID class, one for each wheel
PID_c speed_pid_left; 
PID_c speed_pid_right;


// Class for our Finite State Machine
class FSM_c {
  public:

    // need these bad boys as whole class variables.
    unsigned long kinematics_ts = 0; 
    unsigned long motor_ts = 0;

    //**** PID variables ****
    // I use PID only for straight line control.
    unsigned long pid_ts = 0; // timestamp
    float average_left_speed; // low pass filter of speed, left
    float average_right_speed; // low pass filter of speed, right

    long count_left_last = count_wheel_left; // for difference in encoder counts, set initial values.
    long count_right_last = count_wheel_right;
    float demand = 0.3; // global demand speed variable, encoder counts per ms
    float pwm_left; // our fixed speed values.
    float pwm_right;
    //***********************
    

    // Constructor, must exist.
    FSM_c() {
    }

    // This function calls updates for: Linesensors, PID, and Robot State
    bool update(){

      // Update kinematics (has timing built in, we should refactor the motors and line sensors to contain their own timing too.)
      kinematics.update();

      // Record the time of this execution of loop for coming calucations ( _ts = "time-stamp" )
      unsigned long current_ts;
      current_ts = millis();

      // Run our line sensor update every 100ms (10hz). Tracking time for the line sensor (ls)
      unsigned long elapsed_t;





      // PID Update: calculating speed estimate
      elapsed_t = current_ts - pid_ts; // current time minus prevour time.
      if ( elapsed_t > PID_UPDATE ) { // run every 20 ms

        long diff_left_count;
        long diff_right_count;
        float left_speed;
        float right_speed;

        diff_left_count = count_wheel_left - count_left_last; // get the difference in counts
        count_left_last = count_wheel_left; // update the previous count to current.

        diff_right_count = count_wheel_right - count_right_last; // ditto
        count_right_last = count_wheel_right;

        left_speed = (float)diff_left_count/(float)elapsed_t; // difference in counts devided by elapsed time (counts per ms).
        right_speed = (float)diff_right_count/(float)elapsed_t; 

        // we find an average speed which we weight 70% compared to the current of 30%.
        average_left_speed = (0.7*average_left_speed) + (0.3*left_speed);
        average_right_speed = (0.7*average_right_speed) + (0.3*right_speed);

        pwm_left = speed_pid_left.update(demand, average_left_speed); 
        pwm_right = speed_pid_right.update(demand, average_right_speed);

        pid_ts = millis(); // update the timestam

        // Serial.print("average left speed: ");
        // Serial.println(average_left_speed);
        // Serial.print("average right speed: ");
        // Serial.println(average_right_speed);
        // Serial.print("demand: ");
        // Serial.println(demand);
      }

      // Robot State Update: check position, stop if you hit a certain distance.
      elapsed_t = current_ts - kinematics_ts;
      if( elapsed_t > KINEMATICS_UPDATE ) {

        // When moving forward in a straight line, distance travelled is just x position.
        Serial.print("Distance Travelled (cm): ");
        Serial.println(kinematics.X_pos/10);
        
        if (kinematics.X_pos/10 >= 30){
          // true means you've reached end position and should stop motors and stop running function.
          motors.setMotorPower(0, 0);
          return(true);
        }

        kinematics_ts = millis();

      }





      // Robot State Update: Update what the motors are doing.
      elapsed_t = current_ts - motor_ts;
      if( elapsed_t > MOTOR_UPDATE ) {

        motors.setMotorPower(pwm_left,pwm_right);
        digitalWrite(LED_PIN, false); // light off means not on the line.

        // Update the time stamp.
        motor_ts = millis();

      }

      // zero means haven't reached target yet, continue to run this function each loop.
      return(false);

    }




};



#endif