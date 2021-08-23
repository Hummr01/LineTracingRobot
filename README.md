### Program Execution

To flash the programm to the Arduino ATMEGA328 use following commands:

Change directory in to LineTracingRobot directory.

`cd /LineTracingRobot`

Execute make

`make`

That flashes the software on the ATMEGA328.

If you want just the main.hex you can do that by just compile the c code with:

`make compile`


**Create Documentation**

Change directory in to LineTracingRobot directory

`cd /LineTracingRobot`

Execute make

`make documentation`


## Known Buggs

Sadly I failed to get the robot move perfectly so a few bugs I did not managed to fix before deadline

-Robot just can do left turns what works fine if the track is just a square and the direction he should go is **against** the clock


-Counting rounds is unreliable because of the randomness of light and the sensors I guess, additional my implementation is bit hacky but the best solution I came up with so far


-Turning right just works sometime could not figure out the reason for that either one rotor is stronger than the other or I dont know :(


