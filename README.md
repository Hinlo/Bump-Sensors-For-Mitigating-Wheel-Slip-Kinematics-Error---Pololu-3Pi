# HeathRow: Robotic Systems Assessment 2
# Bump-Sensors-For-Mitigating-Wheel-Slip-Kinematics-Error---Pololu-3Pi
This repository contains the documentation and code created by Finlo Heath and Thomas Rowland in the second assessment of the robotic systems module of Bristol University's MSc Robotics. 

### Hypothesis
Our Hypothesis is as follows: <br>

**When starting to push an object, the bump sensors will reduce kinematic error by providing a sensory trigger to mitigate the effects of wheel-spin. This effect will be more significant when pushing a greater mass, as friction is proportional to object mass, so there is a larger opportunity for wheel-spin before it is overcome. Error mitigation will extend to impacts with stationary objects as well as starting the robot in stationary contact with them, reducing the error in real world distances travelled by the robot when tasked with pushing an object a defined distance.** <br>

This has applications in areas such as factory floor work and automated delivery, where robots could be used to move objects to a desired location.

### Task Domain
The 3pi+ will use the bump sensors as the only environmental input, estimating whether it is in contact with an object and whether the object has begun to move, overcoming it's static friction.


## Files

### Using Bump Sensors to Mitigate Wheel Spin Error in Pololu 3pi+ Robot Kinematics
This report details our study including the experimental method and results. 

### Experiments
This folder contains raw and processed data from our results. Track CAD designs and an image of the track annotated with the two experimental set up configurations.

### Bump Sensors
Contains the original bump sensor testing files for use with the Pololu robot in the Arduino IDE.

### Straight Line PID
Contains the straight line PID set to travel 30cm. For use with the Pololu robot in the Arduino IDE.

### bump sensors with PID
Contains the straight line PID set to travel 30cm where a new maximum measurement from the bump sensors will reset the kinematics to zero. For use with the Pololu robot in the Arduino IDE.

### Impact Detection Straight Line PID
Contains the straight line PID set to travel 30cm where a new PWM measurement above a set threshold will reset the kinematics to zero. For use with the Pololu robot in the Arduino IDE.






