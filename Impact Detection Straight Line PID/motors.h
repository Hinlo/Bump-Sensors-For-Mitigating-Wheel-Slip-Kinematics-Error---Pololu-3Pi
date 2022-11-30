// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _MOTORS_H
#define _MOTORS_H
// Replace the ? with correct pin numbers
// https://www.pololu.com/docs/0J83/5.9
# define L_PWM_PIN 10
# define L_DIR_PIN 16
# define R_PWM_PIN 9
# define R_DIR_PIN 15

# define FWD LOW
# define REV HIGH


// Class to operate the motor(s).
class Motors_c {
  public:

    // Constructor, must exist.
    Motors_c() {

    } 

    // Use this function to 
    // initialise the pins and 
    // state of your motor(s).
    void initialise() {
      // Set all the motor pins as outputs.
      // There are 4 pins in total to set.
      pinMode(L_PWM_PIN,OUTPUT);
      pinMode(L_DIR_PIN,OUTPUT);
      pinMode(R_PWM_PIN,OUTPUT);
      pinMode(R_DIR_PIN,OUTPUT);
      // Set initial direction
      // set speed to 0
      digitalWrite(L_DIR_PIN, FWD);
      digitalWrite(R_DIR_PIN, FWD);
      analogWrite(L_PWM_PIN, 0);
      analogWrite(R_PWM_PIN, 0);

    }

    // Function to set motor power and direction.
    void setMotorPower( float left_pwm, float right_pwm) {
      // allowed value range, maximum absolute pwm of 75.
      if(abs(left_pwm) <= 75 && abs(right_pwm) <= 75){
        //Serial.println("PWM in allowed range");
        // Set initial Dir
        bool L_DIR = FWD;
        bool R_DIR = FWD;

        // Condition to correct direction as required.
        if(0 > left_pwm){
          L_DIR = REV;
        }
        if(0 > right_pwm){
          R_DIR = REV;
        }    
        // Use analogWrite() to set the power of the motors.
        analogWrite(L_PWM_PIN, abs(left_pwm));
        analogWrite(R_PWM_PIN, abs(right_pwm));

        // Use digitalwrite() to set the direction of the motors.
        digitalWrite(L_DIR_PIN, L_DIR);
        digitalWrite(R_DIR_PIN, R_DIR);

        
      }
      else {
        // If requested value outside allowed range, do not change motor values.
      }
    }

    
};
#endif