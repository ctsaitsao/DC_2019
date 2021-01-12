# Design Competition 2019, Team TOTEM
### Team members: Christopher Tsai, Haolin Nie, Juan Solera, Alejandro Alfaro
Course-wide project for DSGN 360: Design Competition, Northwestern University, Spring 2019.

## Introduction & Rules
Design Competition (DC) is an annual competition hosted by Northwestern's McCormick School of Engineering during spring quarter. It consists of student teams building autonomous or semi-autonomous robots that complete a task. The official rules for the 2019 competition were:

*"The arena is divided into two 6' x 6' squares, with a barrier between them to block the view of the driver. Teams place their robot in the opposing square, and their four tokens in their own square.*

*The team that first removes all of their opponents tokens wins. If after 3 minutes neither team has removed all of the tokens, points are awarded for the tokens that have been removed: 4 points for the smallest down to 1 for the largest. The team with the most points wins. In the event of a tie, the round is run again. In the event of three ties, the winner is decided by coin toss.*

*A removed token has been pushed off or ejected from the 6' square.*

*Your robot must fit in a 10" cube at the beginning of the round. The robot may be remote controlled by a driver using Bluetooth-classic and a computer program. Data may be streamed in either direction. The robot can be fully autonomous, semi autonomous, or fully remote controlled."*

Below is an image of the arena. Barriers must be placed in the purple squares and robots can be placed at any location.

![](media/arena.png)

The tokens were wooden cubes covered with reflective tape. They contained a cylindrical hole through their vertical axis.

![](media/token.jpeg)

## Overall Strategy
Take advantage of the holes in every token by using a cleaning brush to drag the block around. The brush would be attached to an arm that rotated up and down using a servo. The arm would also provide enough downward force to cause the block to move by friction between it and the brush hairs. Cut the hairs at an angle (mimicking a wedge) to increase the frictional force between them and the blocks.

![](media/strategy.gif)

Sense the position of the robot in respect to the map (using a GPS-like feature) as well as the blocks' positions.

## Design
![](media/robot.jpg)

### Mechanical Design
The body of the robot was made out of laser-cut acrylic. It was purely structural and designed to support breadboards and wiring, and was essentially two “shelves”. The body also consisted of an arm that held the weapon at the end. 

The weapon was a brush whose spokes would grab the token’s hole and drag the token out of the field. The brush was connected to a servo that would move the weapon down if there was a token to grab it, and up to release it or so that the brush itself would not drag on the floor. 

The robot had two wheels which spun in response to servos, and one wheel as a third point of contact to establish stability. The wheels each had a servo so that there would be differential drive, so moving forward and backward the wheels were spinning in the same direction, but to move left and right they would spin opposite each other. These wheels had an axis connecting them together and were part of the body. 

The main voltage source of the robot was a 12V battery, a 3D-printed battery holder was used to secure it.

### Locomotion
Robot moved using a differential drive mechanism, commanded by the WASD keys on a computer and communicating with the computer using a bluetooth module. It was not autonomous, and instead was driven by team members following the live-updated location and object detection information provided by the robot. Each direction (forward, backward, left, right) had two options: fast or slow. Fast was mostly for actual movement within the field, and slow was for scanning the field for tokens or obstacles, or when the robot was nearing the edge to drop an obstacle.

### Electronics
An ESP32 microcontroller was used to communicate with the sensors and motors.
