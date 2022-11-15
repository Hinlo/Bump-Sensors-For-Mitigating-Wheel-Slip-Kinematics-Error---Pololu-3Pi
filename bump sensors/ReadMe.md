# Read Me

This code contains a simple arduino file with bump sensors as the only environmental input. <br>
A (very bad) force estimate is made using the combined sensor readings. <br>
The motors increase the power to the wheels until a set push force is defined. <br>
If the set force is high enough, the robot will accelerate on impact to push the object. <br>

## Next Steps

We now need to change a few things:

- Rather than a set desired force, we need the desired force to vary once the object begins to move. Due to inertia, the force required to keep pushing an object is less
than the force to start pushing it.
- Of course, we could just use motor pwm to set a demand speed on the wheels, but the aim is to use the force from pushing and impact. Therefore, we need to implement a
proper force calculation which can provide us a mass estimate of the object, then set a desired push force based on the object mass that will push steadily, perhaps using
reinforcement from the bump sensors.



