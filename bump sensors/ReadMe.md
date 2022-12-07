# Read Me

This code contains a simple arduino file with bump sensors as the only environmental input. <br>
A force estimate is made using the combined sensor readings. <br>
If the set force is high enough, the robot will accelerate to push the object. <br>

## Next Steps

We now need to change a few things:
- Rather than a set desired force, we measure the force as the object begins to move. Due to static vs kinetic friction, the force required to keep pushing an object is less than the force to start pushing it.
- use bump sensors and force calc to estimate when motion started and mitigate wheel-slip before motion occurs.



## Observations

Force on the bump sensors is now being calculated rather than guessed. Working is in notebook. 
- model bump sensors as a spring. Therefore, F = -kx.
- So long as discharge time is proportional to bump sensor displacement, F = -ct, where c is a new constant, t is average discharge time of the two sensors.
- How can we verify x is prop to t? It appears to be on the graph.
- We can figure out c experimentally by using a known mass that is barely pushed.
- Force on the mass will be equal and opp (N3), therefore = F.
- find t_thresh by subtracking average background reading from average reading when sensors only just fully pushed in.
- find F_thresh by putting the robot upright and adding mass until bump sensors only just fully pushed in. 
- t_thresh = 9.6 x 10<sup>-4</sup>s, F_thresh = 1.609N
- constant, c = F_thresh/t_thresh = 1700 kgms<sup>-3</sup>.


