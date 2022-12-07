#include "Arduino.h"
#ifndef _bump_H_
#define _bump_H_

# define Left_BUMP 4        // Left bump sensor read pin
# define Right_BUMP 5       // Right bump sensor read pin
# define EMIT_PIN 11     // Shared light sensor / Bump sensor EMIT pin

# define NumberOfSensors 2       // Number of sensors in use

class bumpSensor_c {
  public:

  int bumpPin[NumberOfSensors];          
  float bumpReading[NumberOfSensors];
  float force_calc;
  // float force_guess;

  bumpSensor_c (){        //    Default Constructor
  bumpPin[0] = Left_BUMP;     // Initialise element 0 to left bumper pin
  bumpPin[1] = Right_BUMP;    // Initialise element 1 to right bumper pin
  }




  void initialise(){
    //Emit pins
    pinMode(EMIT_PIN, OUTPUT);            // Shared EMIT pin set to output
    digitalWrite(EMIT_PIN, LOW);         // EMIT pin set to LOW to enable the bump sensors
  

    //Sensor read pins
    pinMode(Left_BUMP, INPUT);          //Left bump sensor pin to input
    pinMode(Right_BUMP, INPUT);         //Right bump sensor pin to input
 
  }


  void bumpSensorRead (){
      int which;                                        //which sensor

    unsigned long start_time;                         //Record the start time.
    start_time = micros();

    int remaining = NumberOfSensors;

    unsigned long end_time_Bump[NumberOfSensors];       // and empty array to store the end time of the sensor reading

    for (int i = 0; i < NumberOfSensors; i++){          // initialises the array to zero
      end_time_Bump[i] = 0;
    }
    while( remaining > 0 ) {                                   // While we still have sensors to read.

      for( which = 0; which < NumberOfSensors; which++ ) {     // Loops between sensors

          if( digitalRead( bumpPin[ which ] ) == LOW ) {        // If digitalRead() returns LOW, it means this sensor has completed and is below the voltage threshold

            if( end_time_Bump[ which ] == 0 ) {              // Check if this sensor has had a previous value of elapsed time stored

              end_time_Bump[which] = micros();              // The time since program started to the sensor to get below threshold
              
              remaining = remaining - 1;                    // cycles down until there are none left remaining
            } // end of if == 0
          } // end of if( digitalRead() )

      } // end of for() looping through each sensor.
    } // end of while( remaining > 0 )
    
      for (which = 0; which < NumberOfSensors; which++){          
      unsigned long elapsed_time;                                         // New long to store the time difference
      elapsed_time = end_time_Bump[which] - start_time;                   // Elapsed time = the end time of the reading - the start time of the reading
      bumpReading[which] = (float)elapsed_time;                           // stores the calculated elapsed time in the bumpReading array as a float
      // Serial.print("\nbumpReading(i) =");
      // Serial.print(bumpReading[which]);

      } //end of for(which = 0; which < NumberOfSensors; which++)

  } // end of bumpSensorRead;



  void chargeCapacitors(){
    
    int which;                                            //Which sensor we are currently looking at
    
    for( which = 0; which < NumberOfSensors; which++ ){

      pinMode( bumpPin[which], OUTPUT );                               
      digitalWrite( bumpPin[which], HIGH );                 // temporarily to output and HIGH to charge capacitors
    }
    
    delayMicroseconds(10);                                // Tiny delay for capacitor to charge.
    for( which = 0; which < NumberOfSensors; which++ ){   //  Turn input pin back to an input
      pinMode( bumpPin[which], INPUT );

    }

  }

  float calculateForce(){       // Cycles through the array filled with the sensor readings


      float bump_average = ((bumpReading[0] + bumpReading[1])/2) * pow(10, -6) - 6.4*pow(10, -4); // take average and convert to seconds from microseconds. and calibrate to zero by subtracting the average background reading.
      // Serial.println(bumpReading[1]);
      // model bump sensors as a spring. Therefore, F = -kx.
      // So long as discharge time is proportional to bump sensor displacement,
      // F = -ct, where c is a new constant, t is average discharge time of the two sensors.
      // How can we verify x is prop to t? It appears to be on the graph.
      // We can figure out c experimentally by using a known mass that is barely pushed.
      // Force on the mass will be equal and opp (N3), therefore = F.

      // calculation notes in report.
      float experimental_coefficient = 1700; // kgms^-3
      force_calc =  experimental_coefficient * bump_average;




      return(force_calc);
  }     

  

}; //End of class

#endif  _bump_H_

