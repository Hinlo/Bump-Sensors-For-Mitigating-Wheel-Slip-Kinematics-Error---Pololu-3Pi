#include "Arduino.h"
// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _PID_H
#define _PID_H




// Class to contain generic PID algorithm.
class PID_c {
  public:

    // we need a set of global class variables here

    // update variables
    float previous_error;
    float prop_term; // proportional
    float int_term; // integral
    float diff_term; // differential
    float int_sum; // persistant integration of error
    float feedback_value; // store the latest feedback value

    // variables to store gain values
    float prop_gain;
    float int_gain;
    float diff_gain; 

    // need a variable to store our previous time stamp
    unsigned long pid_previous_ts;
  
    // Constructor, must exist.
    PID_c() {

    } 

    void initialise( float kp, float ki, float kd){ // call me in void setup. Reset the pid controller each time you use it.
      // set our gain values to those provided in setup.
      prop_gain = kp;
      int_gain = ki;
      diff_gain = kd;

      // set everything else to zero intially.
      previous_error = 0.0;
      prop_term = 0.0;
      int_term = 0.0;
      diff_term = 0.0;
      int_sum = 0.0;
      feedback_value = 0.0;

      // begin timing
      pid_previous_ts = millis();
    }


    void reset(){ // Required to handle any times where there is delay used or motors turned off - prevent integral term building up.
      // reset all these values
      previous_error = 0.0;
      
      // multiplies our demand to a measurable value
      prop_term = 0.0;
      int_term = 0.0;
      
      // counteracts any overshoot in speed changes (therefore usually negative)
      diff_term = 0.0;
      int_sum = 0.0;
      feedback_value = 0.0;
      pid_previous_ts = millis();
    }


    float update(float demand, float measurement){ // This function calculates and returns our feedback value.
      
      // declare required time values
      unsigned long pid_current_ts = millis(); // current time stamp, set at start of each update.
      unsigned long pid_dt; // differential in time

      // declare our error variables
      float error;
      float diff_error;

      // calculate the difference in time
      pid_dt = pid_current_ts - pid_previous_ts;
      // then turn this into a float for calcs later.
      float float_pid_dt = (float)pid_dt;

      // update previous time stamp for next call of update function
      pid_previous_ts = millis();

      // add a catch for the case where the difference in time is zero
      // this can happen if you set the update to run too frequently.
      // in this case, just return the previous value of feedback value:
      if(pid_previous_ts == 0){// this can happen if you call it in microsecond increments
        return feedback_value; // returning stops the function here.
      }

      // calculate our error value; the diff between what we have and what we want.
      error = demand - measurement; // CHECK, PAUL HAS THIS AS MEASUREMENT - DEMAND

      // using our error value we can calculate each of our p,i,d terms

      // p is just multiplying through by our proportional gain
      prop_term = prop_gain * error;

      // i term iterates over the sum
      // find the current sum by adding the integral of the error to all the previous:
      int_sum = int_sum + (error*float_pid_dt);
      // find the i term by multiplying this through by our integral gain
      int_term = int_gain * int_sum;

      // d term is the slope of the line - the difference in error divided by the difference in time
      // that is: de/dt, so:
      diff_error = (error - previous_error)/float_pid_dt;
      // we now reset previous error for next update call
      previous_error = error;
      // our d term is then our differential error multiplied by the differential gain:
      diff_term = diff_gain * diff_error;

      // our feedback value is simply the sum of the three terms!
      feedback_value = prop_term + int_term + diff_term;
      // this is what we return!
      return feedback_value;
    }
};



#endif
