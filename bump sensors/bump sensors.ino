#include "bump.h"
#include "motors.h"

# define bump_sensor_update_time  50

unsigned long bumpSensor_ts = 0;

bumpSensor_c bumpSensor;         // creating an object of type bumpSensor
Motors_c motors;
int speed;

void setup() {


  bumpSensor.initialise();
  // Initialise motor GPIO
  motors.initialise();
  speed = 30;
  delay(5000); // give plotter time to load.
}

void loop() {

  unsigned long current_ts = millis();
  //unsigned long start_time = micros();

  unsigned long elapsed_time = current_ts - bumpSensor_ts;
  if (elapsed_time > bump_sensor_update_time){
      bumpSensor.chargeCapacitors();
      bumpSensor.bumpSensorRead();

      bumpSensor.displayReadings();

      // what you need is for the force guess to be just right so the robot outputs enought power to move but not so much that it accelerates away.
      if (bumpSensor.force_calc < 0.1){ //when not in contact
      speed = 24;
      }
      else if (bumpSensor.force_calc < 0.7){ //THE HIGHER THIS THRESHOLD, THE HEAVIER AN OBJECT CAN BE PUSHED
        speed += 1;
      }
      else{
        if (speed >= 0){
        speed -= 1;
        }
      }
      motors.setMotorPower(speed,speed);
      
      bumpSensor_ts = millis(); 
  }


  

}
