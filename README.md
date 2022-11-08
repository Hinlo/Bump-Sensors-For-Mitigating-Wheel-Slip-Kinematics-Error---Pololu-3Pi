# HeathRow: Robotic Systems Assessment 2
This repository contains the documentation and code created by Thomas Rowland and Finlo Heath in the second assessment of the robotic systems module of Bristol University's MSc Robotics. 

### Hypothesis
Our Hypothesis is as follows: <br>

**By utilising reinforcement learning alongside the native bump sensors on the pololu 3pi+, we will be able to teach the robot to push a small spherical object (a ball) to the boundary of a confined environment.** <br>

This has applications in areas such as factory floor work and automated delivery, where robots could be used to move objects to a desired location.

### Task Domain
The 3pi+ will use the bump sensors as the only environmental input. Reinforcement learning will be used to inform the 3pi+ on whether an input is desirable or undesirable. The 3pi+ will move toward a desirable sensory input, pushing the ball, or away from an undesirable sensory input, if it has not found or has lost the ball.

### Data & Results
Key data to collect will include:
- Video evidence of our reinforcement algorithm working. That is to say, robot performance improves clearly overy the course of each trial.
- The effectiveness of our algorithm can be shown quantitatively by comparing the time to push the object to the boundary using our algorithm and without the algorithm, using the same robot.
- We can measure time for which the bump sensors are triggered during the each trial. More time in contact with the ball would indicate the better performance as this would be positively reinforced. Fewer bumps over a shorter trial time is ideal as it indicates the most direct path to completion.
- Collecting this data would help us to understand:
  - how successful reinforcement learning is for providing a robot the ability to maintain contact with and push an object.
  - whether we can successfully implement the behaviour of the robot stopping as soon as it hits the boundary; this has clear safety implications in factory floors - stopping if you come into contact with a person or other boundary. 

### Method
Given our lack of experience in reinforcement learning, our initial method will be simple to ensure our project goals are achievable. We leave open the possibility of expanding this to an increasing complexity, if we progress quicker than expected. We will begin primarily with software development, activating the bump sensors and attempting to impliment very simple reinforcement learning. Once we have are ready, we will use the following experimental design: <br>

#### Primary Experiments
We will have a small circular environment (e.g 1m diameter) bounded by a cardboard wall. The robot will be placed in the environment in the same position each time. The ball will be placed in the environment in varying positions. <br>
The time to find the ball, push the ball to the boundary and the total contact time of the bump sensors will be measured, the robots behaviour recorded and analaysed. <br>
A shorter time to find the ball and reach the boundary with it will indicate better performance, as will a higher time for the ball being in contact with the bump sensors. If the robot is able to find the ball efficiently and deliver it gently to the boundary - without displacing it - that will indicate better performance as it is indicative of understanding it has reached the barrier and minimising collision force; an important safety feature for robots in production.

#### Further Experiments
If time and progress allows, the next stage of experimentation would be to investigate whether the robot can push the object through a maze to a finish point. This would test it's ability to minimise collision forces with boundaries it encounters, maintain contact with the object through changes in velocity and discern a finish point.

### Learning Achievements
Our main achievement will be the understanding, creation of and use of a simple reinforcement algorithm to develop a desired robot behaviour. We will also improve our understanding of expermental design and implimentation and utilise the bump sensors on the pololu 3pi+ which were not used in Robotic Systems Assessment 1. 

### Further Comments
It may be the case that the rolling of the ball makes it difficult to capture meaningful data as it is hard to maintain contact with the bump sensors of the robot. In this case, we could consider a heavier ball with greater inertia, or a light cube which will not roll but could still be pushed using little force.


## Useful Links
Reinforcement learning with Arduino using Q-learning - https://www.linkedin.com/pulse/reinforcement-learning-arduino-using-q-learning-franco-delgado?articleId=6557094223152246784



