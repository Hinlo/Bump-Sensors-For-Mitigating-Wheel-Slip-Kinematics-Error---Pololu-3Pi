#include "Arduino.h"
// this #ifndef stops this file
// from being included mored than
// once by the compiler. 

// ALL MEASUREMENTS IN mm AT THE MOMENT!!!


#ifndef _KINEMATICS_H
#define _KINEMATICS_H

# define POSITION_UPDATE 100 // how often we will update the position, testing will show if 100 milliseconds (0.1 seconds) is a sensible frequency.
# include "encoders.h"
# include "motors.h"
Motors_c motors;

// Class to track robot position.
class Kinematics_c {
  public:
    unsigned long kinematics_ts = 0; // for time stamping!
    
    // We need some global class variables to refer to, specifically, X_pos, Y_pos and theta (angle rotation)
    // all three must start at zero each time the class is initialised as we always want robot starting at origin of reference frame.
    // all three must be floats as they will not necessarily be whole numbers. max value of float is 3 x 10^38, should be big enough I think...
    float X_pos = 0.0;  // updated by calculating delta_X
    float Y_pos = 0.0;  // updated by calculating delta_Y
    float Theta = 0.0;  // updated by calculating delta_Theta
    float Theta_Home = 0.0; // angle robot must turn to in order to return to start in a straight line.
    volatile long previous_count_wheel_left = 0; // we require this for our change in count value, it starts at zero and is updated in updated function
    volatile long previous_count_wheel_right = 0; // we require this for our change in count value, it starts at zero and is updated in updated function





    // Constructor, must exist.
    Kinematics_c() {

    } 

    // Use this function to update
    // your kinematics
    void update() {

      // Record the time of this execution for coming calucations ( _ts = "time-stamp" )
      unsigned long current_ts;
      current_ts = millis();

      // Calculate elapsed time.
      unsigned long elapsed_t;
      elapsed_t = current_ts - kinematics_ts;



      if( elapsed_t > POSITION_UPDATE ) {
        // declaring my change in x, y, theta variables. this is in reference frame
        float delta_X;
        float delta_Y;
        float delta_Theta;
        
        // declaring my dimensional variables, fixed.
        float r = 16.0; // wheel radius mm.
        float l = 44.6; // dist from centre of robot to centre of wheel mm. Calculated in book.
        float counts_per_rev =  358.3; // counts per revolution of each wheel.
        float circumference = 100.5309649 + 8.3; // wheel circumference is 32pi mm. Extra 5.1 is correction of error from experimentation; corrects disparity in manufacturing.
        float dist_per_count =  circumference/counts_per_rev; // distance travelled per count.

        // now get change in counts since last update:
        long left_change = count_wheel_left - previous_count_wheel_left;
        long right_change = count_wheel_right - previous_count_wheel_right;     
        
        // now calculate the change in x position and theta in local frame (change in y local is always zero)
        // this is essentially the average of the change in counts times by distance per count.
        float delta_X_local = (0.5)*(left_change + right_change)*dist_per_count; // note, didn't like fraction co-efficient for float. Decimal better.// THIS MINUS MAKES FORWARD X AND Y POSITIVE.
        delta_Theta = (0.5)*(1/l)*(right_change - left_change)*dist_per_count; // local delta theta is same as reference delta theta as bot starts lined up with x ref as well as x local.

        // calculte our delta values -> eqns are in lab 6, kinematics section.
        delta_X = delta_X_local*cos(Theta);
        delta_Y = delta_X_local*sin(Theta);
        // we have delta theta already.

        // Update our refernce frame kinematics.
        X_pos = X_pos + delta_X;
        Y_pos = Y_pos + delta_Y;
        Theta = Theta + delta_Theta;
        
        // THIS WORKS!!
        // condition to prevent theta from exceeding +-180. WILL ONLY WORK IF ROBOT DOES NOT COMPLETE MORE THAN ONE FULL CIRCLE IN TIME OF POSITION UPDATE.
        if(abs(Theta*180/3.14159) >= 180){  // we want theta in this range for our full circle. see angles A4 page
          
          if(Theta > 0){
            Theta = Theta - 2*(3.14159); // left is 2pi -> degree equivalent: If theta reads 185, it should be 185 - 365 = -175           
          }
          else{
            Theta = Theta + 2*(3.14159); // left is 2pi -> degree equivalent: If theta reads -185, it should be (-185) + 360 = 175
          }
        }






        // printing our counts out - WORKING!!
        // Serial.println("Right Wheel stats: current, prev, difference ");
        // Serial.print(count_wheel_right);
        // Serial.print(", ");
        // Serial.print(previous_count_wheel_right);
        // Serial.print(", ");
        //  Serial.print(right_change);
        // Serial.print("\n");

        // Serial.println("Left Wheel stats: current, prev, difference ");
        // Serial.print(count_wheel_left);
        // Serial.print(", ");
        // Serial.print(previous_count_wheel_left);
        // Serial.print(", ");
        // Serial.print(left_change);
        // Serial.print("\n");



        // Serial.print("\n");
        // Serial.println("x position is: ");
        // Serial.print(X_pos);


        // Serial.print("\n");
        // Serial.println("y position is: ");
        // Serial.print(Y_pos);


        // Serial.print("\n");
        // Serial.println("angle from start is: ");
        // Serial.print(Theta); //


        // At the end of the update, set the previous counts for when the next update runs.
        previous_count_wheel_left = count_wheel_left;
        previous_count_wheel_right = count_wheel_right;
        // also update our timestamp at the end.
        kinematics_ts = millis();
    }
    }

};



#endif
