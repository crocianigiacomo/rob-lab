# rob-lab

Robot: J4SP3R

Algorithm

The algorithm used for both the line-following task and the tournament is the same. It works as follows:

It initializes all the variables and sensors, namely the CNY70 and GP2D12.

The robot waits to detect an object at a distance of a few centimeters or less using the obstacle detection sensors (we place a hand in front of one or both sensors).

The robot waits until it no longer detects an object at a distance of a few centimeters or less using the obstacle detection sensors (we remove the hand).

The robot starts the movement of the wheels.

It checks the right ground sensor:
a. If it does not detect the black line, the program continues normally.
b. If it detects the line, it stops the wheel on the side of the detecting sensor:
i. The robot waits until it no longer detects the line.
ii. The robot continues turning for 0.2 seconds.
iii. The robot reactivates the stopped wheel, continuing in a straight path.

It performs the same procedure as in step 5 but with the opposite sensor.

It checks whether the right obstacle sensor detects something at a closer distance than the predefined threshold:
a. If it detects nothing, the robot returns to step 5.
b. If it detects something:
i. The robot continues moving for a certain amount of time.
ii. The robot stops the wheel motors.
iii. The robot activates the stepper motor in the direction of the detected object and repeatedly returns to the initial position.

It performs the same action as in the previous step but with the opposite sensor.

Sensor Assembly

The line sensors are mounted so that the line remains between them at a distance of about half a centimeter. The other sensors are mounted on the top, facing forward and angled outward from the robot at approximately 45 degrees. These and all other parts have been secured with screws.

Results Analysis

I would say that the result obtained in the maze was flawless, since the sensors are perfectly calibrated and the robot’s turning radius exactly matches that of the smallest curve.

On the other hand, in the duel it would have been a good idea to stop the robot just before the straw touched the balloon and make a contact attempt. Then move a bit further in the direction of the balloon and attempt contact again, repeating this process until reaching the balloon. This would have prevented the very poor performance our robot experienced due to the miscalculated distance: instead of the needle making contact with the opponent robot, it was the straw that did so.
