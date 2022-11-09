#include "bump.h"

# define bump_sensor_update_time  50

unsigned long bumpSensor_ts = 0;

bumpSensor bumpSensor;         // creating an object of type bumpSensor



void setup() {


bumpSensor.initialise();
  

}

void loop() {

  unsigned long current_ts = millis();
  //unsigned long start_time = micros();

  unsigned long elapsed_time = current_ts - bumpSensor_ts;
  if (elapsed_time > bump_sensor_update_time){
      bumpSensor.chargeCapacitors();
      bumpSensor.bumpSensorRead();

      bumpSensor.displayReadings();

      
      bumpSensor_ts = millis(); 

  }

}
